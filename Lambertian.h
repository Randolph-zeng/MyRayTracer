
#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This implements a perfect diffuse scatterer

#include "BRDF.h"

class Lambertian: public BRDF 
{
	public:
	
		Lambertian(void);
		
		Lambertian(const Lambertian& lamb);
		
		Lambertian& 
		operator= (const Lambertian& rhs);
		
		virtual
		~Lambertian(void);
		
		virtual Lambertian*
		clone(void) const;
		
		virtual RGBAPixel
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) ;
		
		virtual RGBAPixel												
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) ;
		
		virtual RGBAPixel
		rho(const ShadeRec& sr, const Vector3D& wo) ;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);
		
		void
		set_cd(const RGBAPixel& c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void													
		set_cd(const float c);
					
	private:
	
		float		kd;
		RGBAPixel 	cd;
};




// -------------------------------------------------------------- set_ka

inline void
Lambertian::set_ka(const float k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
Lambertian::set_kd(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const RGBAPixel& c) {
	cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void													
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.red = r; cd.green = g; cd.blue = b;
}


// ---------------------------------------------------------------- set_cd

inline void													
Lambertian::set_cd(const float c) {
	cd.red = c; cd.green = c; cd.blue = c;
}

#endif

