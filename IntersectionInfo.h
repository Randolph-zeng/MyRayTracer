#ifndef IntersectionInfo_h_
#define IntersectionInfo_h_
#include "Vector3D.h"
class GeometricObject;

struct IntersectionInfo {
  float t; // Intersection distance along the ray
  const GeometricObject* object; // Object that was hit
  Vector3D hit; // Location of the intersection
};

#endif
