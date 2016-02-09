/*
 * Triangle.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Ruiss
 */
#include "Triangle.h"

//#include <stdio.h>

const double Triangle::kEpsilon = 0.001;



 Triangle::Triangle():vertex1(),vertex2(),vertex3(),n(){
 	//constructor
 }

 Triangle::Triangle(Point3D a, Point3D b, Point3D c):vertex1(a),vertex2(b),vertex3(c){
 	Vector3D v1v2 = Vector3D(b-a);
 	Vector3D v1v3 = Vector3D(c-a);
 	Vector3D norm = v1v2 ^ v1v3;
 	norm.normalize();
 	n = Normal(norm);

	//constructor
 }

 Triangle::Triangle(Point3D a, Point3D b, Point3D c, Normal normal):vertex1(a),vertex2(b),vertex3(c){
	//constructor
	normal.normalize();
	n = normal;
 }

 Triangle::~Triangle(){
 	//no pointer, no cleaning
 }

 Triangle&
 Triangle::operator = (const Triangle& rhs){
 	if(this == &rhs)
 		return (*this);

 	//Let's see what will happen if this line is not included
 	//GeometricObject::operator= (rhs);

 	vertex1 = rhs.vertex1;
 	vertex2 = rhs.vertex2;
 	vertex3 = rhs.vertex3;
 	n 		= rhs.n;

 	return (*this);
 }

Triangle*
Triangle::clone()const{
	return (new Triangle(vertex1,vertex2,vertex3,n));
} 


 //#419 begin# type == 3 # src = http://www.scratchapixel.com/code.php?id=9&origin=/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle
 bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const{

	//replace a in the formula with vertex1
	//float t = (a-ray.o)*n/(ray.d*n);
 	double t = (vertex1-ray.o)*n/(ray.d*n);
 	// inside or outside test
 	if (t >kEpsilon)
 	{
 		
 		Vector3D P = ray.o + ray.d * t;
		Vector3D C; // vector perpendicular to triangle's plane 

     // edge 0
		Vector3D V1V2 = vertex2 - vertex1;

		Vector3D V1P = P - vertex1;
		C = V1V2 ^ V1P; 
        if ((n *C) < 0) return false; // P is on the right side 
 
     // edge 1
        Vector3D V2V3 = vertex3 - vertex2;
		Vector3D V2P = P - vertex2;
		C = V2V3 ^ V2P; 
		if ((n*C) < 0)  return false; // P is on the right side 
 
     // edge 2
		Vector3D V3V1 = vertex1 - vertex3;
		Vector3D V3P = P - vertex3;
		C = V3V1 ^ V3P;
		if((n*C)< 0)	return false;

		tmin = t;
		sr.normal 	 = n;
		sr.local_hit_point = ray.o + t * ray.d;
		return true;
 	}

 	return false;
 }

 //#419 end#


