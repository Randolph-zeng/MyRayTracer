#ifndef __SPHERE__
#define __SPHERE__

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"
#include "BBox.h"
#include "Sampler.h"
//-------------------------------------------------------------------------------- class Sphere
class Sphere: public GeometricObject {	
								  	
	public:
		
		Sphere(void);   									// Default constructor
				
		Sphere(Point3D center, double r);					// Constructor 
					
		Sphere(const Sphere& sphere); 						// Copy constructor
		
		virtual Sphere* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~Sphere(void);   									

		Sphere& 											// assignment operator
		operator= (const Sphere& sphere);				
																					
		void
		set_center(const Point3D& c);
		
		void
		set_center(const double x, const double y, const double z);
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, float& t, ShadeRec& s,IntersectionInfo& I) const;
	//BVH AND BBOX
		virtual BBox 
		getBBox(void)const;

	
		virtual Vector3D 
		getCentroid() const;		

		bool shadow_hit(const Ray& ray, float& tmin,IntersectionInfo& I) const;
		
		//for area lighting!
		void set_sampler(Sampler* sampler);

		virtual Point3D sample(void);

		virtual float pdf( ShadeRec& sr);

		virtual Normal get_normal(const Point3D& p);


	private:
	
		Point3D 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays

		//For area light shading/////////////////////////////////
		Sampler* 	sampler_ptr;
		float 		inv_area;
};



inline void
Sphere::set_center(const Point3D& c) {
	center = c;
}
		
inline void
Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
Sphere::set_radius(const double r) {
	radius = r;
}

#endif
