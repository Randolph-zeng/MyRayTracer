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
		ambient_ptr(new Ambient)	
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




// ----------------------------------------------------------------------------- hit_bare_bones_objects
//Note all the phong shading occurs in here
ShadeRec
World::hit_objects(Ray& ray) {
	ShadeRec	sr(*this);

	IntersectionInfo I;
    bool hit = bvh->getIntersection(ray, &I, false,&sr);

	if (hit)
	{
		sr.t = I.t;
		sr.hit_point = ray.o+sr.t*ray.d;
		sr.material_ptr = I.object->get_material();
		sr.hit_an_object = true;
	}

	return (sr);//This is not very efficient...copying all the staff. Definitely replace it with a pointer later
}



// ------------------------------------------------------------------ build function!
void
World::build(void) {
	//set viewplane
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);

	//set tracer
	tracer_ptr = new Whitted(this);

	//set Pinhole
	pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(0,0,0);   
	pinhole_ptr->set_view_distance(850);	
	pinhole_ptr->compute_uvw(); 	

	//set ambient 
	ambient_ptr = new Ambient();
	//ambient_ptr->scale_radiance(1.0);

	//set point light
	PointLight * pl_ptr = new PointLight(Vector3D(100,50,150),RGBAPixel(255,255,255),3.0);
	add_light(pl_ptr);



	//set bg color
	background_color = RGBAPixel(black);

	//set material

	// Matte* matte_ptr1 = new Matte;
	// matte_ptr1->set_ka(0.25);	
	// matte_ptr1->set_kd(0.65);
	// matte_ptr1->set_ks(0.3);
	// matte_ptr1->set_exp(15);		
	// matte_ptr1->set_cd(RGBAPixel(255,0.0,0.0));
	
	//testing the bvh 	
	int number = 100;
	for (int i = 0; i < number; ++i)
	{
		Sphere* sphere_ptr = new Sphere(Point3D(rand()%100-50, rand()%100-50, rand()%100-50), 5);
		Matte* matte_ptr1 = new Matte;
		matte_ptr1->set_cd(RGBAPixel(rand()%200+55,rand()%200+55,rand()%200+55));
		matte_ptr1->set_ka(0.25);	
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_ks(0.3);
	matte_ptr1->set_exp(15);
		sphere_ptr->set_material(matte_ptr1);	// yellow
		add_object(sphere_ptr);
	}

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

	// Sphere* sphere_ptr = new Sphere(Point3D(-30,-30,-30), 30);
	// sphere_ptr->set_material(matte_ptr1);	// yellow
	// add_object(sphere_ptr);
	
	//BVH added here
	bvh = new BVH(&objects);

}


