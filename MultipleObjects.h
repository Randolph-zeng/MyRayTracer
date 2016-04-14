/*
 * MultipleObjects.h
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#ifndef TRACERS_MULTIPLEOBJECTS_H_
#define TRACERS_MULTIPLEOBJECTS_H_

#include "Tracer.h"

class Material;
class World;

class MultipleObjects : public Tracer {
public:

	MultipleObjects();

	MultipleObjects(World* _worldPtr);

	virtual ~MultipleObjects();
	// if a class is polymorphic (declares or inherits at least one virtual function),
	//and its destructor is not virtual, deleting it is undefined behavior regardless
	//of whether there are resources that would be leaked if the derived destructor is
	//not invoked.
	virtual RGBAPixel trace_ray( Ray& ray, const int depth) const;

};

#endif /* TRACERS_MULTIPLEOBJECTS_H_ */
