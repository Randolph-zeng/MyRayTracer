/*
 * World.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#ifndef WORLD_H_
#define WORLD_H_

//# 419begin # type = 3 # src = raytracegroundup.com
#include <vector>
#include "Ray.h"
#include "MultipleObjects.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "ViewPlane.h"
#include "GeometricObject.h"
//# 419end

//# 419begin # type = 1 # src = http://zarb.org/~gc/html/libpng.html && Chase Geigle from CS225
#include "rgbapixel.h" // now color ranges from 0 to 255
#include "png.h"



using namespace std;//we are using vector class


class World {
public:
	ViewPlane vp;
	RGBAPixel background_color;
	Tracer* tracer_ptr;
	Sphere sphere;
	vector<GeometricObject*> objects;

	PNG * Image;


	World();
	virtual ~World();

	void
	add_object(GeometricObject* object_ptr);

	void
	build(void);

	void
	render_scene(void);

	// RGBAPixel
	// max_to_one(const RGBAPixel& c) const;

	void
	clamp_to_color( RGBAPixel& c) const;

	void
	display_pixel(const int row, const int column, const RGBAPixel& pixel_color) const;

	ShadeRec
	hit_bare_bones_objects(const Ray& ray);

	void
	delete_objects(void);

	void set_perspective(const bool isPerspective);

	void set_sample_number(const double number);

	void set_diffuse(Vector3D ld, float kd_, float dif_);


	//void set_camera(const double x,const double y,const double z);


private:
	bool perspective;
	double x;
	double y;
	double z;
	double sample_number;// note that I am using the simplest multi-jittered method here,
						//did not enforce n-rook property and also did not shuffle
	Vector3D light_dir;
	float 	 kd; 		//reflectivity
	float	 dif_illum;	//diffuse light luminosity


};



// inline void World::set_camera(const double x,const double y,const double z){}


#endif /* WORLD_H_ */
