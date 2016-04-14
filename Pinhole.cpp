// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the Pinhole class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "Pinhole.h"

#include <math.h>

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)		
	:	Camera(),
		d(500),
		zoom(1.0)
{}


// ----------------------------------------------------------------------------- copy constructor

Pinhole::Pinhole(const Pinhole& c)   		
	: 	Camera(c),
		d(c.d),
		zoom(c.zoom)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
Pinhole::clone(void) const {
	return (new Pinhole(*this));
}



// ----------------------------------------------------------------------------- assignment operator

Pinhole& 
Pinhole::operator= (const Pinhole& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	d 		= rhs.d;
	zoom	= rhs.zoom;

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

Pinhole::~Pinhole(void) {}	

//------------------------------------------------------------------ clamp

RGBAPixel
Pinhole::max_to_one( RGBAPixel& c) const  {
	float max_value = max(c.red, max(c.green, c.blue));

	if (max_value > 255)
		return (c / max_value)*255.0;
	else
		return (c);
}



// ----------------------------------------------------------------------------- render_scene

void 												
Pinhole::render_scene(const World& world) {

	RGBAPixel	pixel_color;
	ViewPlane	vp(world.vp);
	Ray			ray;
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.psize/ zoom;
	float		zw		= 100.0;			// hardwired in (z origin of ray)
	int 		sample_number = world.sample_number;
	Tracer* 	tracer_ptr = world.tracer_ptr;
	bool 		perspective = true;

	Image = new PNG( hres + 1, vres + 1); // not sure if we need to + 1

	//if not perspective, then orthographic
	if ( !perspective)
	{
		ray.d = Vector3D(0, 0, -1);
		for (int r = 0; r < vres; r++)			// up
			for (int c = 0; c <= hres; c++) {	// across
				pixel_color = black;
				for (int p = 0; p < sample_number; ++p)
					for (int q = 0; q < sample_number; ++q){
						double x = s * (c - 0.5 * hres + (q+0.5)/sample_number);
						double y = s * (r - 0.5 * vres + (p+0.5)/sample_number);
						ray.o = Point3D(x,y,zw);
						pixel_color = pixel_color + tracer_ptr->trace_ray(ray,0);						//
					}
								
				pixel_color = pixel_color/(sample_number*sample_number);
				*( (*Image)(c,vres-r-1) ) = pixel_color;	
			}

	}
	else{
		ray.o = eye;
		for (int r = 0; r < vres; r++)			// up
			for (int c = 0; c <= hres; c++) {	// across
				pixel_color = black;
				for (int p = 0; p < sample_number; ++p)
					for (int q = 0; q < sample_number; ++q){
						double x = s * (c - 0.5 * hres + (q+0.5)/sample_number);
						double y = s * (r - 0.5 * vres + (p+0.5)/sample_number);
						
						ray.d = x * u + y * v - d * w;					
						ray.d.normalize();
						//multiply by the inverse eliminates the shadow don't know why
						//ray.set_inverse();
						pixel_color = pixel_color + tracer_ptr->trace_ray(ray,0);	
					}
							
				pixel_color = pixel_color/(sample_number*sample_number);
				//printf("before  red:%f green:%f blue:%f\n",pixel_color.red,pixel_color.green,pixel_color.blue );
				pixel_color = max_to_one(pixel_color);
				//printf("After  red:%f green:%f blue:%f\n",pixel_color.red,pixel_color.green,pixel_color.blue );
				*( (*Image)(c,vres-r-1) ) = pixel_color;
			}

	}

}



