#ifndef __REFLECTIVE__
#define __REFLECTIVE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matte.h"
#include "PerfectSpecular.h"
#include "rgbapixel.h"

class Reflective: public Matte {	
	public:
	
		Reflective(void);										

		Reflective(const Reflective& rm);						

		Reflective& 
		operator= (const Reflective& rhs);						

		virtual Reflective*										
		clone(void) const;				

		~Reflective(void);										
		
		void
		set_kr(const float k);
				
		void													
		set_cr(const RGBAPixel& c);
		
		void
		set_cr(const float r, const float g, const float b);
		
		void
		set_cr(const float c);
		
		virtual RGBAPixel										
		shade(ShadeRec& sr);

		virtual RGBAPixel
		area_light_shade(ShadeRec& sr);

		RGBAPixel max_to_one( RGBAPixel& c) const;
		
	private:
	
		PerfectSpecular* reflective_brdf;		
};


// ---------------------------------------------------------------- set_kr

inline void
Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const RGBAPixel& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}

#endif
