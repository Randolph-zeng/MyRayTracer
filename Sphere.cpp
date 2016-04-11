// This file contains the definition of the class sphere

#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;

					
// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		inv_area(1/(4*PI))
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		inv_area(1/(4*PI*r*r))
{}


// ---------------------------------------------------------------- clone

Sphere* 
Sphere::clone(void) const {
	return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius),
		inv_area(sphere.inv_area)
{}



// ---------------------------------------------------------------- assignment operator

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;
	inv_area = rhs.inv_area;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


// ---------------------------------------------------------------- bbox

BBox 
Sphere::getBBox(void) const {
	return BBox(center-Vector3D(radius,radius,radius), center+Vector3D(radius,radius,radius));
	
}

Vector3D 
Sphere::getCentroid(void) const {
    return center;
}
//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, float& tmin, ShadeRec& sr,IntersectionInfo& I) const {
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
		I.t = t;
		I.object = this;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
		I.t = t;
		I.object = this;	
			return (true);
		} 
	}
	return (false);
}

bool Sphere::shadow_hit(const Ray& ray, float& tmin,IntersectionInfo& I) const{
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			I.t = t;
			I.object = this;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			I.t = t;
			I.object = this;
			return (true);
		} 
	}
	
	return (false);
}






void Sphere::set_sampler(Sampler* sampler){
	sampler_ptr = sampler;
}

Point3D Sphere::sample(void){

	Point3D sample_point = sampler_ptr->sample_sphere();
	return (center + sample_point * radius); 

}

float Sphere::pdf(ShadeRec& sr){
	return inv_area;
}

Normal Sphere::get_normal(const Point3D& p){
	Normal n = Normal(p-center); 
	n.normalize();
	return n;
}
