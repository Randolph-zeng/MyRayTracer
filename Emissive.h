#ifndef __EMISSIVE__
#define __EMISSIVE__



#include "Material.h"
#include "rgbapixel.h"
#include "ShadeRec.h"

class Emissive: public Material{
private:
	float ls;
	RGBAPixel ce;
public:

	Emissive(void);											

	Emissive(const Emissive& m);
	
	virtual Material*										
	clone(void) const;									

	Emissive& 
	operator= (const Emissive& rhs);							

	~Emissive(void);	

	void scale_radiance(const float _ls);

	void set_ce(float r,float g,float b);

	// virtual RGBAPixel get_Le(ShadeRec& sr)const; //for environment light

	virtual RGBAPixel shade(ShadeRec& sr);

	virtual RGBAPixel area_light_shade(ShadeRec& sr);

	virtual RGBAPixel get_Le(ShadeRec& sr);


};



#endif
