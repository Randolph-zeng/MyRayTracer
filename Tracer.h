/*
 * Tracer.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#ifndef TRACERS_TRACER_H_
#define TRACERS_TRACER_H_

#include "Constants.h"
#include "Ray.h"
#include "rgbapixel.h"


class World;

class Tracer {
public:
	Tracer();
	Tracer(World* world_ptr);


	virtual ~Tracer(); // this destructor should be inherited by all derived class

	virtual RGBAPixel trace_ray(const Ray& ray)const; // promise to not changing the ray and other class member

//	virtual RGBAPixel trace_ray(const Ray& ray, const int depth) const;

//protected because it is accessible by its public derived class

protected:
// we need a world pointer here because we need to have access to background color
// and geometric object(aka their color)
	World* world_ptr;
};

#endif /* TRACERS_TRACER_H_ */
