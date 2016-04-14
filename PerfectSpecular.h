#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this implements perfect specular reflection for indirect illumination
// with reflective materials 

#include "BRDF.h"
#include "Normal.h"
#include "rgbapixel.h"

class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		~PerfectSpecular(void);
		
		virtual PerfectSpecular*
		clone(void) const;
		
		void
		set_kr(const float k);
		
		void
		set_cr(const RGBAPixel& c);
		
		void													
		set_cr(const float r, const float g, const float b);
		
		void													
		set_cr(const float c);

		RGBAPixel max_to_one( RGBAPixel& c) const; 
		
		virtual RGBAPixel
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBAPixel
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) ;
		
		virtual RGBAPixel
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) ;
		
		virtual RGBAPixel
		rho(const ShadeRec& sr, const Vector3D& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		RGBAPixel 	cr;			// the reflection colour
};


// -------------------------------------------------------------- set_kr

inline void
PerfectSpecular::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

inline void
PerfectSpecular::set_cr(const RGBAPixel& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.red = r; cr.green = g; cr.blue = b;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float c) {
	cr.red = c; cr.green = c; cr.blue = c;
}

#endif

