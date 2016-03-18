#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include "rgbapixel.h"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.0001; 
const double	kHugeValue	= 1.0E10;

const RGBAPixel	black(((float)0.),((float)0.),((float)0.));
const RGBAPixel	white((float)255.,(float)255.,(float)255.);
const RGBAPixel	red((float)255.,(float) 0., (float)0.);

const float invRAND_MAX = 1.0 / (float)RAND_MAX;

#endif
