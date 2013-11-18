/*
 *  Intersection.cc
 *  
 *
 * Created by Orlando Pineda on 9/23/12.
 * Class representing an intersection between a ray and a shape. Store
 * the shape, point, normals to be used for ray color and reflections.
 */

#include "Intersection.h"
Intersection::Intersection(double time1, MyPoint& p1, MyVector& norm, Surface * surface) {
  t1 = time1;
  point1 = p1;
  intersected = true;
  normal1 = norm;
  has_second = false;
  surface_id = surface;
}
Intersection::Intersection(double time1, double time2,MyPoint& p1, MyPoint& p2, MyVector& norm1, MyVector& norm2, Surface * surface) {
  t1 = time1;
  point1 = p1;
  t2 = time2;
  point2 = p2;
  intersected = true;
  normal1 = norm1;
  normal2 = norm2;
  has_second = true;
  surface_id = surface;
}
Intersection::Intersection() {
  intersected = false;
}

