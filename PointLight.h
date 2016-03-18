#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "rgbapixel.h"
#include "Vector3D.h"
#include "BVH.h"
#include "BBox.h"
//#include "ShadeRec.h"

class BVH;

class PointLight: public Light{
public:
	//default constructor
	PointLight(void);

	PointLight(Vector3D position,RGBAPixel c, float d);
	//copy constructor
	PointLight(const PointLight& ptl);

	~PointLight(void);

	PointLight& 								
	operator= (const PointLight& rhs);

	PointLight* 						
	clone(void) const;
					
	Vector3D								
	get_direction(ShadeRec& sr);	

																
	RGBAPixel														
	L(ShadeRec& sr);	

	bool
	in_shadow(Ray & ray,const ShadeRec& sr)const;	



private:
	//The default color,ls,location are white, 0.8, (0,0,0)
	float ls;
	RGBAPixel color;
	Vector3D location;

};


#endif