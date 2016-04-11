// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Material.h"

// ---------------------------------------------------------------- default constructor

Material::Material(void) {}


// ---------------------------------------------------------------- copy constructor

Material::Material(const Material& m) {}



// ---------------------------------------------------------------- assignment operator

Material& 
Material::operator= (const Material& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

Material::~Material(void)
{}


// ---------------------------------------------------------------- shade

RGBAPixel
Material::shade(ShadeRec& sr) {
	return (RGBAPixel(0,0,0));
}


RGBAPixel Material::get_Le(ShadeRec& sr){
	
	printf("base material get_Le reached\n" );
	return (RGBAPixel(0,0,0));
}

RGBAPixel
Material::area_light_shade(ShadeRec& sr){
	printf("base material area_light_shade reached\n" );
	return (RGBAPixel(0,0,0));	
}	