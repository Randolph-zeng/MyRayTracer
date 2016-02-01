/*
 * World.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

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

// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		Image(NULL)

{}



//------------------------------------------------------------------ destructor

World::~World(void) {

	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	delete_objects();
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

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across
			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			//display_pixel(r, c, pixel_color);
			*( (*Image)(c,vres-r-1) ) = pixel_color;
		}

}

// ----------------------------------------------------------------------------- hit_bare_bones_objects

ShadeRec
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this);
	double		t;
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.color			= objects[j]->get_color();
		}

	return (sr);
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
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(255, 0, 0);  // red
	add_object(sphere_ptr);

	// // use constructor to set centre and radius

	// sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	// sphere_ptr->set_color(255, 255, 0);	// yellow
	// add_object(sphere_ptr);

	//Add a Triangle
	// Triangle* tri_ptr = new Triangle(Point3D(-20, -30, 0),Point3D(0, 90, 70),Point3D(90, 0, 70));	
	// tri_ptr->set_color(0,0,255);	//blue
	// add_object(tri_ptr);

	// Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	// plane_ptr->set_color(0, 76, 0);	// dark green
	// add_object(plane_ptr);
}






// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function

//
//void
//World::display_pixel(const int row, const int column, const RGBAPixel& raw_color) const {
//	RGBAPixel mapped_color;
//
//	if (vp.show_out_of_gamut)
//		mapped_color = clamp_to_color(raw_color);
//	else
//		mapped_color = max_to_one(raw_color);
//
//	if (vp.gamma != 1.0)
//		mapped_color = mapped_color.powc(vp.inv_gamma);
//
//   //have to start from max y coordinate to convert to screen coordinates
//   int x = column;
//   int y = vp.vres - row - 1;
//
//   paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
//                             (int)(mapped_color.g * 255),
//                             (int)(mapped_color.b * 255));
//}
//


//------------------------------------------------------------------ clamp
//This function is not needed, in RGBAPixel, the rgb values are bounded by u8int;
//RGBAPixel
//World::max_to_one(const RGBAPixel& c) const  {
//	float max_value = max(c.red, max(c.green, c.blue));
//
//	if (max_value > 255)
//		return (c / max_value);
//	else
//		return (c);
//}
//

// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one
//
//RGBAPixel
//World::clamp_to_color(const RGBAPixel& raw_color) const {
//	RGBAPixel c(raw_color);
//
//	if (raw_color.red > 1.0 || raw_color.green > 1.0 || raw_color.blue > 1.0) {
//		c.red = 1.0; c.green = 0.0; c.blue = 0.0;
//	}
//
//	return (c);
//}




