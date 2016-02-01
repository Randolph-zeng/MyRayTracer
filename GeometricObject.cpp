/*
 * GeometricObject.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: Ruiss
 */

#include "GeometricObject.h"

GeometricObject::GeometricObject():color(black){

}

GeometricObject::GeometricObject(const GeometricObject & object):color(object.color){
}

GeometricObject& GeometricObject::operator=(const GeometricObject& rhs){
	if(this == &rhs)
		return (*this);
	color = rhs.color;
	return (*this);
}

GeometricObject::~GeometricObject() {
	// TODO Auto-generated destructor stub
}

