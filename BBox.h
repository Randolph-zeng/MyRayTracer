#ifndef __BBOX_H__
#define __BBOX_H__

#include "Ray.h"
#include "Vector3D.h"
#include <stdint.h>

struct BBox {
  Vector3D min, max, extent;
  BBox(){}
  BBox(const Vector3D& min, const Vector3D& max);
  BBox(const Vector3D& p);

  bool intersect( Ray& ray, float *tnear, float *tfar) ;
  void expandToInclude(const Vector3D& p);
  void expandToInclude(const BBox& b);
  uint32_t maxDimension() const;
  float surfaceArea() const;
};

#endif
