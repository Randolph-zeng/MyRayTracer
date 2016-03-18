#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <math.h>  // a lot of hit functions use use maths functions

#include "Constants.h"
#include "BBox.h"
#include "BVH.h"
#include "rgbapixel.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "IntersectionInfo.h"

class Material;	


//----------------------------------------------------------------------------------------------------- class GeometricObject

class GeometricObject {	
	public:	

		GeometricObject(void);									
		
		GeometricObject(const GeometricObject& object);			
	
		virtual GeometricObject*								
		clone(void) const = 0;

		virtual 												
		~GeometricObject(void);	
			
		virtual bool 												 
		hit(const Ray& ray, float& t, ShadeRec& s,IntersectionInfo& I) const = 0;	

		virtual bool shadow_hit(const Ray& ray, float& tmin,IntersectionInfo& I) const = 0;
		
		virtual void 							// This needs to be virtual so that it can be overridden in Compound
		set_material(Material* mPtr); 			// It therefore shouldn't be inlined
		
		Material*					
		get_material(void) const;

				   
		// The following three functions are only required for Chapter 3
		
		void
		set_color(const RGBAPixel& c);
				
		void
		set_color(const float r, const float g, const float b);
		
		RGBAPixel
		get_color(void);
		
		// virtual void 
		// set_bounding_box(void);
		
		virtual BBox 
		getBBox(void)const = 0;

		virtual Vector3D 
		getCentroid() const = 0;

		virtual void 										// required for compound objects
		add_object(GeometricObject* object_ptr);
				
		
		// The following two functions are only required for objects that are light sources, eg disks, rectangles, and spheres
		 
		virtual Point3D 		
		sample(void);
		
		virtual float
		pdf(ShadeRec& sr); 
				
		
		// The following two functions allow us to simplify the code for smooth shaded triangle meshes
		
		virtual Normal
		get_normal(void) const; 
		
		virtual Normal
		get_normal(const Point3D& p); 

	
	protected:
	
		mutable Material*   material_ptr;   	// mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
		RGBAPixel   			color;				// only used for Bare Bones ray tracing
	
		GeometricObject&						
		operator= (const GeometricObject& rhs);
};


// --------------------------------------------------------------------  set_color

inline void
GeometricObject::set_color(const RGBAPixel& c) {
	color = c;
}

// --------------------------------------------------------------------  set_color

inline void 
GeometricObject::set_color(const float r, const float g, const float b) {
	color.red = r;
	color.blue = b;
	color.green = g;
}

// --------------------------------------------------------------------  get_color

inline RGBAPixel 
GeometricObject::get_color(void) {
	return (color);
}

#endif
