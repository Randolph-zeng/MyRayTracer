/*
 * Ray.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#include "Ray.h"
#include <stdio.h>
Ray::Ray(void):o(0.0),d(0.0,0.0,1.0) {
	// TODO Auto-generated constructor stub
}

Ray::Ray(const Point3D& origin,const Vector3D& direction){
	o = origin;
	d = direction;
}

Ray::Ray(const Ray& other_ray){
	o = other_ray.o;
	d = other_ray.d;
}

Ray& Ray::operator= (const Ray& rhs){
	if(this == &rhs)
		return (*this);
	o = rhs.o;
	d = rhs.d;

	return (*this);
}

Ray::~Ray(void) {
	// TODO Auto-generated destructor stub
}

void Ray::set_inverse(){

	inverse_d.x = 1/d.x;
	inverse_d.y = 1/d.y;
	inverse_d.z = 1/d.z; 
}