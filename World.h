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
#include "Whitted.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "ViewPlane.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Ambient.h"
#include "PointLight.h" 
#include "Camera.h" 
#include "Pinhole.h"

//# 419end

//# 419begin # type = 1 # src = http://zarb.org/~gc/html/libpng.html && Chase Geigle from CS225
#include "rgbapixel.h" // now color ranges from 0 to 255
#include "png.h"
//#419 begin# type = 1 # SRC = https://github.com/brandonpelfrey/Fast-BVH
#include "BVH.h"
#include "BBox.h" 
//#419 end

using namespace std;//we are using vector class
class Pinhole;
class Material;
class Matte;
class World {
public:
	ViewPlane vp;
	RGBAPixel background_color;
	Tracer* tracer_ptr;
	vector<GeometricObject*> objects;
	vector<Light*> lights;				
	Light * ambient_ptr;				//ambient pointer, we only need one
	int sample_number;
	Pinhole * pinhole_ptr;
	BVH* bvh;

	World();
	virtual ~World();

	void
	add_object(GeometricObject* object_ptr);

	void add_light(Light * light_ptr);

	void
	build(void);

	void
	clamp_to_color( RGBAPixel& c) const;

	void
	display_pixel(const int row, const int column, const RGBAPixel& pixel_color) const;

	ShadeRec
	hit_objects(Ray& ray);

	void
	delete_objects(void);

	void set_sample_number(const int number);

	void set_diffuse(float kd_, float dif_);


private:
	float 	 kd; 		//reflectivity
	float	 dif_illum;	//diffuse Light luminosity



};


#endif /* WORLD_H_ */
