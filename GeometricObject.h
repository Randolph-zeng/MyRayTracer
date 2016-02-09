/*
 * GeometricObject.h
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#ifndef GEOMETRICOBJECTS_GEOMETRICOBJECT_H_
#define GEOMETRICOBJECTS_GEOMETRICOBJECT_H_

#include "rgbapixel.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Constants.h"

class GeometricObject {
public:
	GeometricObject();

	GeometricObject(const GeometricObject & object);

	virtual GeometricObject* clone(void) const = 0;			// virtual copy constructor

	virtual ~GeometricObject();

	//It is very important to remember to calculate the normal in the hit point 
	//and record it in the ShadeRec object. It saves time and can be
	//used to do phong shading!
	virtual bool hit(const Ray& ray, double & t, ShadeRec& s) const = 0;

	void
	set_color(const RGBAPixel& c);

	void
	set_color(const uint8_t r, const uint8_t g, const uint8_t b);

	RGBAPixel
	get_color(void);

protected:
	RGBAPixel color;	//This stupid shit exists because all objects are unicolored for now.
	GeometricObject & operator = (const GeometricObject& rhs); //assignment operator
};


// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const RGBAPixel& c) {
	color = c;
}

// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const uint8_t r, const uint8_t g, const uint8_t b) {
	color.red = r;
	color.blue = b;
	color.green = g;
}

// --------------------------------------------------------------------  get_colour

inline RGBAPixel
GeometricObject::get_color(void) {
	return (color);
}


#endif /* GEOMETRICOBJECTS_GEOMETRICOBJECT_H_ */
