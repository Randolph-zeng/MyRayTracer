#ifndef __PINHOLE__
#define __PINHOLE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class Pinhole

//#include "World.h"    // we can #include "World.h" here
#include "png.h"
#include "Camera.h"
#include "World.h"
//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
	public:
		PNG * Image;		//Temporarily public
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const float _d);
		
		void
		set_zoom(const float zoom_factor);
		
		virtual void 												
		render_scene(const World& world);

		RGBAPixel
		max_to_one(RGBAPixel& c) const;
		
	private:
			
		float	d;		// view plane distance
		float	zoom;	// zoom factor

};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	

#endif

