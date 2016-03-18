/*
 * Ray.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#ifndef RAY_H_
#define RAY_H_

#include "Point3D.h"
#include "Vector3D.h"



class Ray {
public:
	Point3D o;
	Vector3D d;
	Vector3D inverse_d;
	Ray(void);
	Ray(const Point3D& origin,const Vector3D& direction);
	Ray(const Ray& other_ray);
	Ray& operator= (const Ray& rhs);
	void set_inverse();
	~Ray(void);
};

#endif /* RAY_H_ */
