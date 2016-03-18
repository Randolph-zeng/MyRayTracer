// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matte.h"

// ---------------------------------------------------------------- default constructor

Matte::Matte (void)
	:	Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian),
		specular_brdf(new GlossySpecular)
{}



// ---------------------------------------------------------------- copy constructor

Matte::Matte(const Matte& m)
	: 	Material(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;

	if(m.specular_brdf)
		specular_brdf = m.specular_brdf->clone(); 
	else  specular_brdf = NULL;	
}


// ---------------------------------------------------------------- clone

Material*										
Matte::clone(void) const {
	return (new Matte(*this));
}	


// ---------------------------------------------------------------- assignment operator

Matte& 
Matte::operator= (const Matte& rhs) {
	if (this == &rhs)
		return (*this);
		
	Material::operator=(rhs);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
		
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Matte::~Matte(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBAPixel
Matte::shade(ShadeRec& sr) {
	Vector3D 	wo 			= -sr.ray.d;
	RGBAPixel 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	//printf("Before r:%f g:%f b:%f\n",L.red,L.green,L.blue);
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0){
			bool in_shadow = false;
			Ray shadowRay(sr.hit_point,wi);
			in_shadow = sr.w.lights[j]->in_shadow(shadowRay,sr);

			if (!in_shadow)
			{
				L += (diffuse_brdf->f(sr, wo, wi)+specular_brdf->f(sr,wo,wi))* sr.w.lights[j]->L(sr) * ndotwi;	
			}
			
		} 
	
	}

	return (L);
}



	 //printf("After r:%f g:%f b:%f\n",L.red,L.green,L.blue);
	 // printf("\n");
	//+ specular_brdf->f(sr, wo, wi)