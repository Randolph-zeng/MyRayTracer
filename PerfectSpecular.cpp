// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PerfectSpecular.h"
#include <math.h>
// ---------------------------------------------------------- default constructor

PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0.0), 
		cr(RGBAPixel(255,255,255))
{}

// ---------------------------------------------------------- destructor

PerfectSpecular::~PerfectSpecular(void) {}


// ---------------------------------------------------------------------- clone

PerfectSpecular* 
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}	


// ---------------------------------------------------------- f

RGBAPixel
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

RGBAPixel
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)  {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	RGBAPixel temp = (cr * kr / fabs(sr.normal * wi));
	temp = max_to_one(temp);
	return temp; // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}											 // for transparency when ray hits inside surface?, if so it should go in Chapter 24

RGBAPixel
PerfectSpecular::max_to_one( RGBAPixel& c) const  {
	float max_value = max(c.red, max(c.green, c.blue));
	if (max_value > 255)
		return (c / max_value)*255.0;
	else
		return (c);
}

// ---------------------------------------------------------- sample_f
// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

RGBAPixel
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)  {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	pdf = fabs(sr.normal * wi);
	return ( cr * kr);  
}

// ---------------------------------------------------------- rho

RGBAPixel
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}

