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
//#419 end

 //----------------------------------------------------------------------

void World::set_perspective(const bool isPerspective){
	perspective = isPerspective;
}


void World::set_sample_number(const double number){
	sample_number = number;
}

void World::set_diffuse(Vector3D ld, float kd_, float dif_){
	light_dir = ld;
	kd = kd_; 	
	dif_illum = dif_;
}


// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		Image(NULL),
		perspective(false)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {

	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	delete_objects();
}



void
World::clamp_to_color(RGBAPixel& raw_color) const {
	if (raw_color.red > 255.0)		raw_color.red = 255.0;
	if (raw_color.green > 255.0)		raw_color.green = 255.0;
	if (raw_color.blue > 255.0)		raw_color.blue = 255.0;
	
}



//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis
// I removed the const here to initialize the Image variable;
void
World::render_scene(void) {

	RGBAPixel	pixel_color;
	Ray			ray;
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.psize;
	float		zw		= 100.0;			// hardwired in (z origin of ray)

	Image = new PNG( hres + 1, vres + 1); // not sure if we need to + 1

	//if not perspective, then orthographic
	if ( !perspective)
	{
		ray.d = Vector3D(0, 0, -1);
		for (int r = 0; r < vres; r++)			// up
			for (int c = 0; c <= hres; c++) {	// across
				pixel_color = black;
				for (int p = 0; p < sample_number; ++p)
					for (int q = 0; q < sample_number; ++q){
						double x = s * (c - 0.5 * hres + (q+0.5)/sample_number);
						double y = s * (r - 0.5 * vres + (p+0.5)/sample_number);
						ray.o = Point3D(x,y,zw);
						pixel_color = pixel_color + tracer_ptr->trace_ray(ray);						//
					}
								
				pixel_color = pixel_color/(sample_number*sample_number);
				*( (*Image)(c,vres-r-1) ) = pixel_color;	
			}

	}
	else{
		ray.o = Point3D(0.0,0.0,zw*2);
		for (int r = 0; r < vres; r++)			// up
			for (int c = 0; c <= hres; c++) {	// across
				pixel_color = black;
				for (int p = 0; p < sample_number; ++p)
					for (int q = 0; q < sample_number; ++q){
						double x = s * (c - 0.5 * hres + (q+0.5)/sample_number);
						double y = s * (r - 0.5 * vres + (p+0.5)/sample_number);
						ray.d = Point3D(x,y,-zw);
						pixel_color = pixel_color + tracer_ptr->trace_ray(ray);						//
					}
							
				pixel_color = pixel_color/(sample_number*sample_number);
				*( (*Image)(c,vres-r-1) ) = pixel_color;
			}



	}

}

// ----------------------------------------------------------------------------- hit_bare_bones_objects
//Note all the phong shading occurs in here
ShadeRec
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this);
	double		t;
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++){
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.color			= objects[j]->get_color();
		
			double factor = std::max(sr.normal * light_dir,0.0)*kd*dif_illum;
			sr.color = sr.color*factor;
			clamp_to_color(sr.color);

		}
	}

	return (sr);//This is not very efficient...copying all the staff. Definitely replace it with a pointer later
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty

void
World::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase (objects.begin(), objects.end());
}

// ------------------------------------------------------------------ add_object
void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}


// ------------------------------------------------------------------ build function!
void
World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1);

	tracer_ptr = new MultipleObjects(this);

	background_color = RGBAPixel(black);

	// use access functions to set centre and radius

	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, 0, 0);
	sphere_ptr->set_radius(40);
	sphere_ptr->set_color(255, 0, 0);  // red
	add_object(sphere_ptr);

	// // // use constructor to set centre and radius

	sphere_ptr = new Sphere(Point3D(0, 40, -50), 30);
	sphere_ptr->set_color(255, 255, 0);	// yellow
	add_object(sphere_ptr);

	//Add a Triangle
	Triangle* tri_ptr = new Triangle(Point3D(10, 10, 70),Point3D(90, 0, 70),Point3D(0, 90, 70));	
	tri_ptr->set_color(0,0,255);	//blue
	add_object(tri_ptr);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 0, 1));
	plane_ptr->set_color(0, 76, 0);	// dark green
	add_object(plane_ptr);
}





// pixel_color = tracer_ptr->trace_ray(ray);

