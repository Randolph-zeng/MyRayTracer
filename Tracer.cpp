/*
 * Tracer.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#include "Tracer.h"

Tracer::Tracer() {
	world_ptr = NULL;
	// TODO Auto-generated constructor stub
}

Tracer::Tracer(World* world){
	world_ptr = world;
}

Tracer::~Tracer() {
	if(world_ptr)
		world_ptr = NULL;// world object should be released in world class;
}

RGBAPixel Tracer::trace_ray(Ray& ray)const{
	printf("base tracer reached\n" );//shouldn't reached at all
	return (black);// defined in constant.h, essentially RGBAPixel(0,0,0)
}

//RGBAPixel Tracer::trace_ray(const Ray&ray, int depth) const{
//	return (black);
//}

