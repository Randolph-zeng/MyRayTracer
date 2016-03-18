/*
 * Plane.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#include "Plane.h"


// ----------------------------------------------------------------------  default constructor

Plane::Plane(void)
	: 	GeometricObject(),
		a(0.0),
		n(0, 1, 0)
{}


// ----------------------------------------------------------------------  constructor

Plane::Plane(const Point3D& point, const Normal& normal)
	:	GeometricObject(),
		a(point),
		n(normal)
{
		n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Plane::Plane(const Plane& plane)
	:	GeometricObject(plane),
		a(plane.a),
		n(plane.n)
{}


// ---------------------------------------------------------------- clone

Plane*
Plane::clone(void) const {
	return (new Plane(*this));
}


// ---------------------------------------------------------------- assignment operator

Plane&
Plane::operator= (const Plane& rhs)	{

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Plane::~Plane(void)
{}


// ----------------------------------------------------------------- hit
bool Plane::hit(const Ray& ray, float& tmin, ShadeRec& sr,IntersectionInfo& I)const{
	float t = (a-ray.o)*n/(ray.d*n);

	if(t> 0.001){
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t*ray.d;
		return true;
	}
	return false;

}


bool Plane::shadow_hit(const Ray& ray, float& tmin,IntersectionInfo& I)const {
	float t = (a-ray.o)*n/(ray.d*n);

	if(t> 0.001){
		tmin = t;
I.t = t;
		I.object = this;		
		return true;
	}
	return false;

}


BBox 
Plane::getBBox(void)const{
	
}

	
Vector3D 
Plane::getCentroid() const{

}	


