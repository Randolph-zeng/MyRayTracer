/*
 * MultipleObjects.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#include "MultipleObjects.h"
#include "World.h" // include a header file inside a cpp file won't result in circular dependence!!!!!!!!!

MultipleObjects::MultipleObjects() {
	Tracer();
}

MultipleObjects::MultipleObjects(World* _worldPtr)
: Tracer(_worldPtr)
{}

//empty because there is no new member in this derived class now
MultipleObjects::~MultipleObjects() {

}

RGBAPixel MultipleObjects::trace_ray(const Ray& ray)const{
	//this function will return an ShadeRec object, and sr will be
	//initialized by copy constructor
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

	if(sr.hit_an_object){
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));//shadeRec is the glu between all the shading 
		//architecture since material has no direct access to the light
	}
	else
		return (world_ptr->background_color);

}


