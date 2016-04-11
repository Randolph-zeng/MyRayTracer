#ifndef __LIGHT__
#define __LIGHT__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Vector3D.h"
#include "rgbapixel.h"
#include "Ray.h"
#include "ShadeRec.h"
class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
						
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;

		virtual bool
		in_shadow( Ray& ray, const ShadeRec& sr)const = 0;				
																
		virtual RGBAPixel														
		L(ShadeRec& sr);	

		virtual float
		G(const ShadeRec& sr) const;
		
		virtual float									
		pdf( ShadeRec& sr) const ;

									
};

#endif
