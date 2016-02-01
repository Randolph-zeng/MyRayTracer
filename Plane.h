/*
 * Plane.h
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#ifndef GEOMETRICOBJECTS_PLANE_H_
#define GEOMETRICOBJECTS_PLANE_H_

#include "GeometricObject.h"
class Plane : public GeometricObject{

public:
	Plane();

	Plane(const Point3D & point, const Normal & normal);

	Plane(const Plane& plane);

	virtual Plane* clone(void) const;

	Plane& operator=(const Plane& rhs);

	virtual ~Plane();

	//note all three parameters are passed by reference
	virtual bool hit(const Ray&ray, double& tmin, ShadeRec& sr) const;


private:
	Point3D a;	//the expression for a plane is n(p-a) = 0
	Normal n;


};

#endif /* GEOMETRICOBJECTS_PLANE_H_ */
