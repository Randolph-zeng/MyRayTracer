#include "PointLight.h"
#include "World.h"



PointLight::PointLight(void){
	location = Vector3D();
	color = RGBAPixel(255,255,255);
	ls = 0.8;
}

PointLight::PointLight(Vector3D position,RGBAPixel c, float d){
	location = position;
	color = c;
	ls = d;	
}

PointLight::PointLight(const PointLight& ptl){
	location = ptl.location;
	color = ptl.color;
	ls = ptl.ls;
}

PointLight::~PointLight(void){

}

PointLight&
PointLight::operator= (const PointLight& rhs){
	if (this == &rhs)
	{
		return (*this);
	}
	this->color = rhs.color;
	this->location = rhs.location;
	this->ls = rhs.ls;
	return (*this);
}

PointLight* 						
PointLight::clone(void) const{
	return (new PointLight(*this));
}


Vector3D								
PointLight::get_direction(ShadeRec& sr){
	return ((location-Vector3D(sr.local_hit_point)).hat());
}	

//without distance attenuation, this is identical to the ambient light class
RGBAPixel														
PointLight::L(ShadeRec& sr){
	return (color*ls);
}


//
bool
PointLight::in_shadow(Ray & ray,const ShadeRec& sr)const{
	// float t;
	// int num_objects = sr.w.objects.size();
	

	// for (int i = 0; i < num_objects; ++i)
	// {
	// 	if (sr.w.objects[i]->shadow_hit(ray,t)&& t < d)
	// 	{
	// 		return (true);
	// 	}
	// }

	// return false;

	float d = location.distance(ray.o);
	IntersectionInfo I;
    bool hit = sr.w.bvh->getIntersection(ray, &I, true, NULL);
    return hit;

}	