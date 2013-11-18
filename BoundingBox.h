/*
 * BoundingBox.h
 *
 *  Created on: Nov 5, 2012
 *      Author: orlando
 *
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include "Vector.h"
#include "Ray.h"
#include <limits>
#include "Surface.h"

class BoundingBox {
	MyPoint min;
	MyPoint max;
	Surface*  surface_id;


public:
	BoundingBox() {}
	BoundingBox(MyPoint, MyPoint, Surface *);
	BoundingBox(float, float, float, float, float, float, Surface*);
	bool intersect(Ray);
	Intersection getIntersect(Ray);
};






#endif /* BOUNDINGBOX_H_ */
