/*
 * BoundingBox.cc
 *
 *  Created on: Nov 5, 2012
 *      Author: orlando
 *
 * Similar to the shape class, this class works the same way except instead of
 * returning the intersection point of the shape, it returns an intersection point
 * for a bounding box around the shape.
 */
#include "BoundingBox.h"
#include "Intersection.h"
BoundingBox::BoundingBox(MyPoint mn, MyPoint mx, Surface * surface) {
	min = mn;
	max = mx;
	surface_id = surface;
}

BoundingBox::BoundingBox(float xmin, float ymin, float zmin, float xmax ,float ymax, float zmax, Surface * surface) {
	min = MyPoint(xmin, ymin, zmin);
	max = MyPoint(xmax, ymax, zmax);
	surface_id = surface;
}

// Box ray intersection code. Simply retunrs true or false if a ray intersects the box
bool BoundingBox::intersect(Ray r) {
	double txmax, txmin, tymax, tymin, tzmax, tzmin;
	double ax = (double) 1/ r.getDir().getX();
	if (ax >= 0) {
		txmin = (double)(min.getX() - r.getOrigin().getX())/r.getDir().getX();
		txmax =  (double)(max.getX() - r.getOrigin().getX())/r.getDir().getX();
	} else {
		txmin = (double)(max.getX() - r.getOrigin().getX())/r.getDir().getX();
		txmax =  (double)(min.getX() - r.getOrigin().getX())/r.getDir().getX();
	}
	double ay = (double) 1/ r.getDir().getY();

	if (ay >= 0) {
		tymin =  (min.getY() - r.getOrigin().getY())/r.getDir().getY();
		tymax =  (max.getY() - r.getOrigin().getY())/r.getDir().getY();
	} else {
		tymin =  (max.getY() - r.getOrigin().getY())/r.getDir().getY();
		tymax =  (min.getY() - r.getOrigin().getY())/r.getDir().getY();
	}
	double az = (double) 1/ r.getDir().getZ();

	if (az >= 0) {
		tzmin =  (min.getZ() - r.getOrigin().getZ())/r.getDir().getZ();
		tzmax =  (max.getZ() - r.getOrigin().getZ())/r.getDir().getZ();

	} else {
		tzmin =  (max.getZ() - r.getOrigin().getZ())/r.getDir().getZ();
		tzmax =  (min.getZ() - r.getOrigin().getZ())/r.getDir().getZ();

	}
	if (txmin > tymax || tymin > txmax || tzmin > txmax || tzmin > tymax || txmin > tzmax || tymin > tzmax) {
		return false;
	} else {
		return true;
	}
}

// Code that returns the actual intersection if the ray intersects the bounding box
Intersection BoundingBox::getIntersect(Ray r) {
	double txmax, txmin, tymax, tymin, tzmax, tzmin;
	double ax = (double) 1/ r.getDir().getX();
	if (ax >= 0) {
		txmin = (double)(min.getX() - r.getOrigin().getX())/r.getDir().getX();
		txmax =  (double)(max.getX() - r.getOrigin().getX())/r.getDir().getX();
	} else {
		txmin = (double)(max.getX() - r.getOrigin().getX())/r.getDir().getX();
		txmax =  (double)(min.getX() - r.getOrigin().getX())/r.getDir().getX();
	}
	double ay = (double) 1/ r.getDir().getY();

	if (ay >= 0) {
		tymin =  (min.getY() - r.getOrigin().getY())/r.getDir().getY();
		tymax =  (max.getY() - r.getOrigin().getY())/r.getDir().getY();
	} else {
		tymin =  (max.getY() - r.getOrigin().getY())/r.getDir().getY();
		tymax =  (min.getY() - r.getOrigin().getY())/r.getDir().getY();
	}
	double az = (double) 1/ r.getDir().getZ();

	if (az >= 0) {
		tzmin =  (min.getZ() - r.getOrigin().getZ())/r.getDir().getZ();
		tzmax =  (max.getZ() - r.getOrigin().getZ())/r.getDir().getZ();

	} else {
		tzmin =  (max.getZ() - r.getOrigin().getZ())/r.getDir().getZ();
		tzmax =  (min.getZ() - r.getOrigin().getZ())/r.getDir().getZ();

	}
	if (txmin > tymax || tymin > txmax || tzmin > txmax || tzmin > tymax || txmin > tzmax || tymin > tzmax) {
		return Intersection();
	} else {
		double tmin =0, tmax =0;
		MyVector norm1;
		MyVector norm2;
		tmin = (txmin > tymin) ? txmin : tymin;
		norm1 = (txmin > tymin) ? MyVector(-1,0,0) : MyVector(0,-1,0);

		tmin = (tzmin > tmin) ? tzmin : tmin;
		norm1 = (tzmin > tmin) ? MyVector(0,0,-1) : norm1;

		tmax = (txmax < tymax) ? txmax : tymax;
		norm2 = (txmax < tymax) ? MyVector(1,0,0) : MyVector(0,1,0);

		tmax = (tzmax < tmax) ? tzmax : tmax;
		norm2 = (tzmax < tmax) ? MyVector(0,0,1) : norm2;

		MyPoint intersect1 = r.getOrigin() + (r.getDir() * tmin);
		MyPoint intersect2 = r.getOrigin() + (r.getDir() * tmax);

		return Intersection(tmin, tmax, intersect1, intersect2, norm1, norm2, surface_id);
	}
}



