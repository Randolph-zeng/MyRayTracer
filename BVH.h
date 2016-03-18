#ifndef __BVH_H__
#define __BVH_H__

#include "BBox.h"
#include <vector>
#include <stdint.h>
#include "GeometricObject.h"
#include "IntersectionInfo.h"
#include "Ray.h"
#include "ShadeRec.h"
//! Node descriptor for the flattened tree
struct BVHFlatNode {
  BBox bbox;
  uint32_t start, nPrims, rightOffset;
};

//! \author Brandon Pelfrey
//! A Bounding Volume Hierarchy system for fast Ray-Object intersection tests
class BVH {
  uint32_t nNodes, nLeafs, leafSize;
  std::vector<GeometricObject*>* build_prims;

  //! Build the BVH tree out of build_prims
  void build();

  // Fast Traversal System
  BVHFlatNode *flatTree;

  public:
  BVH(std::vector<GeometricObject*>* objects, uint32_t leafSize=4);
  bool getIntersection( Ray& ray, IntersectionInfo *intersection, bool occlusion, ShadeRec* sr) const ;

  ~BVH();
};

#endif
