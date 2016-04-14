// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "AreaLight.h"

// ---------------------------------------------------------------- default constructor
	
AreaLight::AreaLight(void)
	: 	Light(),
		object_ptr(NULL),
		material_ptr(NULL)
{}	


// ---------------------------------------------------------------- copy constructor 
	
AreaLight::AreaLight(const AreaLight& al)
	: 	Light(al) {
	if(al.object_ptr)
		object_ptr = al.object_ptr->clone(); 
	else  object_ptr = NULL;
	
	if(al.material_ptr)
		material_ptr = al.material_ptr->clone(); 
	else  material_ptr = NULL;
}


// ---------------------------------------------------------------- clone

AreaLight* 
AreaLight::clone(void)const {
	return (new AreaLight(*this));
}					


// ---------------------------------------------------------------- destructor
 								
AreaLight::~AreaLight(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}


// --------------------------------------------------------------- assignment operator

AreaLight&														
AreaLight::operator= (const AreaLight& rhs) {
	if (this == &rhs)
		return (*this);
		
	Light::operator=(rhs);
	
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
		
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// --------------------------------------------------------------- get_direction

Vector3D								
AreaLight::get_direction(ShadeRec& sr) {
	sample_point = object_ptr->sample();    // used in the G function
	light_normal = object_ptr->get_normal(sample_point); 
	wi = sample_point - sr.hit_point;  		// used in the G function
	wi.normalize();
	
	return (wi);
}


// --------------------------------------------------------------- L

RGBAPixel								
AreaLight::L(ShadeRec& sr) {
	float ndotd = -light_normal * wi; 
	
	if (ndotd > 0.0)		
		return (material_ptr->get_Le(sr)); 
	else
		return (black);
}


// ---------------------------------------------------------------- in_shadow	

bool									
AreaLight::in_shadow(Ray& ray, const ShadeRec& sr) const {

	//use accelerate structure
	ShadeRec temp = ShadeRec(sr);
	float d =  object_ptr->getCentroid().distance(ray.o);
	IntersectionInfo I;
    bool hit = sr.w.bvh->getIntersection(ray, &I, false, &temp);
    float hit_d = ray.o.distance((ray.o+I.t*ray.d));



    bool hit_light = (I.object == object_ptr);

    return (!hit_light && hit_d < d);
}


// ---------------------------------------------------------------- G
// G is part of the geometric factor

float
AreaLight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sr.hit_point);
		
	return (ndotd / d2);
}


// ---------------------------------------------------------------- pdf

float									
AreaLight::pdf( ShadeRec& sr) const {
	//printf("AreaLight pdf reached\n");
	return (object_ptr->pdf(sr));
}
