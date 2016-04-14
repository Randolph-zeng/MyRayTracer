/*
 * World.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */
#include <stdio.h>
#include <algorithm>  
#include "World.h"

//#419 begin# type = 1 # SRC = http://www.raytracegroundup.com/downloads.html
#include "Constants.h" // with a minor change in ragapixel.h
#include "Matrix.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"
#include "PointLight.h"
#include "Material.h"
#include "Matte.h"
#include "Emissive.h" 
#include "AreaLighting.h"
#include "AreaLight.h"
#include "Sampler.h" 
#include "MultiJittered.h"
#include "Reflective.h"
#include "PerfectSpecular.h" 
//#419 end
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void World::set_sample_number(const int number){
	sample_number = number;
}

// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new Ambient),
		plane_ptr(NULL),
		max_depth(1)	
{}


void World::set_diffuse(float kd_, float dif_){

	kd = kd_; 	
	dif_illum = dif_;
}




//------------------------------------------------------------------ destructor

World::~World(void) {

	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	if (ambient_ptr)
	{
		delete ambient_ptr;
		ambient_ptr = NULL;
	}


	delete_objects();
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty

void
World::delete_objects(void) {
	// int num_objects = objects.size();

	// for (int j = 0; j < num_objects; j++) {
	// 	delete objects[j];
	// 	objects[j] = NULL;
	// }

	// int num_lights = lights.size();
	// for (int i = 0; i < num_lights; ++i){
	// 	delete lights[i];
	// 	lights[i] = NULL;
	// }

	// objects.erase (objects.begin(), objects.end());
	// lights.erase (lights.begin(), lights.end());	
}

// ------------------------------------------------------------------ add_object
void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

void 
World::add_light(Light * light_ptr){
	lights.push_back(light_ptr);
}



//will make this better clamp later
void
World::clamp_to_color(RGBAPixel& raw_color) const {
	if (raw_color.red > 255.0)		raw_color.red = 255.0;
	if (raw_color.green > 255.0)		raw_color.green = 255.0;
	if (raw_color.blue > 255.0)		raw_color.blue = 255.0;
	
}

// ----------------------------------------------------------------------------- hit_objects
ShadeRec
World::hit_objects(Ray& ray) {
	ShadeRec	sr(*this);

	IntersectionInfo I;
    bool hit = bvh->getIntersection(ray, &I, false,&sr);

	//add plane detection
	bool hit_plane = false;
    if (plane_ptr)
    {
    	float tmin = 1000000;
    	ShadeRec temp = ShadeRec(sr);//avoid changing the normal of sr
    	if (plane_ptr->hit(ray, tmin,temp) && tmin < I.t){
    		hit_plane = true;
    		sr.t = tmin;
    		sr.hit_point = ray.o+ tmin*ray.d;
    		sr.material_ptr = plane_ptr->get_material();
    		sr.hit_an_object = true;
    		sr.normal = temp.normal;
			sr.local_hit_point = temp.local_hit_point;
    	}
	 		 
    }


	if (hit&& !hit_plane )
	{
		sr.t = I.t;
		sr.hit_point = ray.o+sr.t*ray.d;
		sr.material_ptr = I.object->get_material();
		sr.hit_an_object = true;
	}


	return (sr);
}


// ------------------------------------------------------------------ build function!
void
World::build(void) {
	//set viewplane
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	max_depth = 3;

	//set tracer
	//tracer_ptr = new Whitted(this);
	tracer_ptr = new AreaLighting(this);

	//set Pinhole
	pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(-50,-50, 100);
	pinhole_ptr->set_lookat(10,10,-30);   
	pinhole_ptr->set_view_distance(300);	
	pinhole_ptr->compute_uvw(); 	

	//set ambient 
	ambient_ptr = new Ambient();
	//ambient_ptr->scale_radiance(1.0);


	//set area light
	Emissive * emissive_ptr = new Emissive();
	emissive_ptr->scale_radiance(256);
	emissive_ptr->set_ce(255,255,255);

	//set sampler_ptr
	Sampler * sampler_ptr = new MultiJittered(100);
	sampler_ptr->map_samples_to_sphere();

	//set emissive sphere_light
	Sphere * sphere_light = new Sphere(Point3D(0,0,20),15);
	sphere_light->set_material(emissive_ptr); 
	sphere_light->set_sampler(sampler_ptr);
	add_object(sphere_light);
	
	//set area light
	AreaLight* area_light_ptr = new AreaLight();
	area_light_ptr->set_object(sphere_light);
	add_light(area_light_ptr);


	//set bg color
	background_color = RGBAPixel(black);

	//set material

	// Matte* matte_ptr1 = new Matte;
	// matte_ptr1->set_ka(0.25);	
	// matte_ptr1->set_kd(0.65);
	// matte_ptr1->set_ks(0.3);
	// matte_ptr1->set_exp(15);		
	// matte_ptr1->set_cd(RGBAPixel(255,0.0,0.0));
	
	Reflective * reflective_ptr = new Reflective();
	reflective_ptr->set_ka(0.25);	
	reflective_ptr->set_kd(0.65);
	reflective_ptr->set_ks(0.3);
	reflective_ptr->set_cd(RGBAPixel(200,200,0));//yellow light
	reflective_ptr->set_exp(15);		
	reflective_ptr->set_kr(0.75);		
	reflective_ptr->set_cr(RGBAPixel(255,255,255));		



	//testing the bvh 	
	int number = 1;
	for (int i = 0; i < number; ++i)
	{	

		Sphere* sphere_ptr = new Sphere(Point3D(5,5,-25), 10);

		sphere_ptr->set_material(reflective_ptr);	// yellow
		add_object(sphere_ptr);

		sphere_ptr = new Sphere(Point3D(-15,-15,-25), 15);

	reflective_ptr = new Reflective();
	reflective_ptr->set_ka(0.25);	
	reflective_ptr->set_kd(0.65);
	reflective_ptr->set_ks(0.3);
	reflective_ptr->set_cd(RGBAPixel(0,255,0));//yellow light
	reflective_ptr->set_exp(15);		
	reflective_ptr->set_kr(0.75);		
	reflective_ptr->set_cr(RGBAPixel(255,255,255));	

		sphere_ptr->set_material(reflective_ptr);	// yellow
		add_object(sphere_ptr);

	}

	// Sphere* sphere_ptr = new Sphere(Point3D(-30,-30,-30), 30);
	// sphere_ptr->set_material(matte_ptr1);	// yellow
	// add_object(sphere_ptr);
	 
	//BVH added here
	bvh = new BVH(&objects);

	//add plane
	plane_ptr = new Plane(Point3D(0,0,-30), Normal(0,0,1));
		Matte* matte_ptr1 = new Matte;
		matte_ptr1->set_cd(RGBAPixel(255,0,0));
		matte_ptr1->set_ka(0.25);	
		matte_ptr1->set_kd(0.65);
		matte_ptr1->set_ks(0.3);
		matte_ptr1->set_exp(15);
	plane_ptr->set_material(matte_ptr1);

}

	//set point light
	// PointLight * pl_ptr = new PointLight(Vector3D(100,50,150),RGBAPixel(255,255,255),3.0);
	// add_light(pl_ptr);


	//read triangles
	
	// vector<Point3D> All_Points;
	// FILE * file = fopen("cow.obj", "r");
	// if( file == NULL ){
	//      printf("Impossible to open the file !\n");
	//      return;
	//  } 
	// while( true ){

	// 	char lineHeader[128];
	// 	// read the first word of the line
	// 	int res = fscanf(file, "%s", lineHeader);
	// 	if (res == EOF)
	// 		break;
	// 	if ( strcmp( lineHeader, "v" ) == 0 ){
	//      	Point3D point;
	//      	fscanf(file, "%lf %lf %lf\n", &point.x, &point.y, &point.z );
	//      	All_Points.push_back(point*70);
	//     }
	// 	if ( strcmp( lineHeader, "f" ) == 0 ){
	//      	int ver1,ver2,ver3;
	//      	fscanf(file, "%d %d %d\n", &ver1,&ver2, &ver3);
	// 		Triangle* tri_ptr = new Triangle(All_Points.at(ver1-1),All_Points.at(ver2-1),All_Points.at(ver3-1));	
	// 		tri_ptr->set_material(matte_ptr1);	//blue
	// 		add_object(tri_ptr);	     	 
	//     }

	// }	
	// cout << "Read file completed!!" << endl;





	// ShadeRec	sr(*this);

	// IntersectionInfo I;
 	// bool hit = bvh->getIntersection(ray, &I, false,&sr);

	// if (hit)
	// {
	// 	sr.t = I.t;
	// 	sr.hit_point = ray.o+sr.t*ray.d;
	// 	sr.material_ptr = I.object->get_material();
	// 	sr.hit_an_object = true;
	// }


	// return (sr);