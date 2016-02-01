#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeometricObject.h"
#include "Vector3D.h"

class Triangle:public GeometricObject{

	public:
		Point3D		vertex1;
		Point3D		vertex2;
		Point3D		vertex3;
		Normal		n;
		
		Triangle();	//	default constructor

		Triangle(Point3D a, Point3D b, Point3D c);

		Triangle(Point3D a, Point3D b, Point3D c, Normal normal);

		virtual ~Triangle();	// destructor

		virtual Triangle* clone()const;

		Triangle& operator=(const Triangle& rhs); // copy constructor

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;


	private:
		static const double kEpsilon;

};


#endif
