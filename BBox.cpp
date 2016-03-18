#include "BBox.h"
#include <algorithm>
#include <stdio.h>


BBox::BBox(const Vector3D& min, const Vector3D& max)
  : min(min), max(max) { extent = max - min; }

BBox::BBox(const Vector3D& p)
  : min(p), max(p) { extent = max - min; }

void BBox::expandToInclude(const Vector3D& p) {

 
    min.x = std::min(min.x, p.x);
    min.y = std::min(min.y, p.y);
    min.z = std::min(min.z, p.z);
    max.x = std::max(max.x, p.x);
    max.y = std::max(max.y, p.y);
    max.z = std::max(max.z, p.z);
    extent = max - min;

}

void BBox::expandToInclude(const BBox& b) {    
    min.x = std::min(min.x, b.min.x);
    min.y = std::min(min.y, b.min.y);
    min.z = std::min(min.z, b.min.z);
    max.x = std::max(max.x, b.max.x);
    max.y = std::max(max.y, b.max.y);
    max.z = std::max(max.z, b.max.z);
    extent = max - min;
}

uint32_t BBox::maxDimension() const {
  uint32_t result = 0;
  if(extent.y > extent.x) result = 1;
  if(extent.z > extent.y) result = 2;
  return result;
}

float BBox::surfaceArea() const {
  return 2.f*( extent.x*extent.z + extent.x*extent.y + extent.y*extent.z );
}


bool BBox::intersect( Ray& ray, float *tnear, float *tfar)  {

    double t1 = (min[0] - ray.o[0])/ray.d[0];
    double t2 = (max[0] - ray.o[0])/ray.d[0];
 
    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);
 
    for (int i = 1; i < 3; ++i) {
        t1 = (min[i] - ray.o[i])/ray.d[i];
        t2 = (max[i] - ray.o[i])/ray.d[i];
 
        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
    }
    *tnear = tmin;
    *tfar  = tmax;

    return tmax > std::max(tmin, 0.0);


}
