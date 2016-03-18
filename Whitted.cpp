// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include <stdio.h>

// -------------------------------------------------------------------- default constructor

Whitted::Whitted(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
Whitted::Whitted(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

Whitted::~Whitted(void) {}


// -------------------------------------------------------------------- trace_ray

RGBAPixel	
Whitted::trace_ray( Ray& ray) const {		
		ShadeRec sr(world_ptr->hit_objects(ray));    
			
		if (sr.hit_an_object) {
			sr.ray = ray;		
			return (sr.material_ptr->shade(sr));   
		}
		else{
			 //printf("background_color_rached\n");
			return (world_ptr->background_color);
		}
																																				
}
