//
//  Ray.cpp
//  
//
//  Created by Orlando Pineda on 9/22/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Ray.h"
Ray::Ray() {
  dir = MyVector();
  origin = MyPoint();
}
Ray::Ray(MyPoint p, MyVector v) {
  origin = p;
  dir = v.normal();
}
Ray::Ray(MyPoint& p, MyPoint& a, MyPoint& b) {
  origin = p;
  dir = MyVector(a,b).normal();
}
MyPoint Ray::getOrigin() {
  return origin;
}
MyVector& Ray::getDir() {
  return dir;
}
MyVector Ray::getNormDir() {
  return dir.normal();
}
MyPoint Ray::getPoint(double t) {
	return origin + (dir * t);
}
