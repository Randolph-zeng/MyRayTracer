#include "Emissive.h"


Emissive::Emissive(void):ls(0.0),ce(0,0,0){
}

Emissive::Emissive(const Emissive& m):ls(m.ls),ce(m.ce){	
}

Material*										
Emissive::clone(void) const{
	return new Emissive(*this);
}

Emissive::~Emissive(void){	
}

Emissive& 
Emissive::operator= (const Emissive& rhs){
	if (this == &rhs)
		return (*this);
	ls = rhs.ls;
	ce = rhs.ce;
	return (*this);
}


void Emissive::scale_radiance(const float _ls){
	ls = _ls;
}

void Emissive::set_ce(float r,float g,float b){
	ce = RGBAPixel(r,g,b);
}

RGBAPixel Emissive::area_light_shade(ShadeRec& sr){
	if (-sr.normal * sr.ray.d > 0.0)
	{
		return (ce*ls);
	}
	else
		return black;	
}

RGBAPixel Emissive::shade(ShadeRec& sr){
	return black;
}


RGBAPixel Emissive::get_Le(ShadeRec& sr){
	return (ce*ls);
}