//
//  Plane.cc
//  raytra
//
//  Created by Orlando Pineda on 10/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Plane.h"
Plane::Plane(MyVector normal, float distance, Material material){
    norm = normal;
    d = distance;
    mats = material;
}
Intersection Plane::intersect(Ray r, int renderflag) {
  MyVector temp(r.getOrigin().getX(), r.getOrigin().getY(), r.getOrigin().getZ());
  
  double t =temp.dot(norm) + d;
  t /= r.getDir().dot(norm);
  t = -t;
  MyPoint point = r.getOrigin() + r.getDir() * t;
  
  if (r.getDir().dot(norm) == 0) return Intersection();
  if (t <= 0.1) return Intersection();
  return Intersection(t, point, norm, this);
  
}

