//
//  Computer Graphics.cpp
//  
//
//  Created by Orlando Pineda on 9/23/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sphere.h"
#include <cmath>
#include <limits>
Sphere::Sphere(MyPoint& o, float r, Material material) {
  origin = o;
  radius = r;
  mats = material;
  box = BoundingBox(o.getX() - r, o.getY() - r, o.getZ() - r, o.getX() + r, o.getY() +r, o.getZ() + r, this);
}
double Sphere::discriminant(Ray ray) {

  double left = pow((ray.getDir().dot((ray.getOrigin() - origin))),2);

  double right = (ray.getDir().dot(ray.getDir())) *((ray.getOrigin()- origin).dot(ray.getOrigin() - origin) - pow(radius, 2));
  return left-right;
}
Intersection Sphere::intersect(Ray ray, int renderflag) {
  if (box.intersect(ray) && renderflag ==0) {
	  if ( discriminant(ray) == 0) {
		  double t = (- ray.getDir().dot((ray.getOrigin() - origin)) + sqrt(discriminant(ray)))/(ray.getDir().dot(ray.getDir()));
		  MyPoint intersect = ray.getOrigin() + ( ray.getDir() * t);
		  MyVector normvec = ((intersect/radius) - (origin/radius)).normal();

		  if ( t < 0 || t >std::numeric_limits<double>::infinity()) return Intersection();
		  return Intersection(t, intersect, normvec, this);
		} else if (discriminant(ray) > 0) {
		  double t1 = (-ray.getDir().dot((ray.getOrigin() - origin)) + sqrt(discriminant(ray))) / (ray.getDir().dot(ray.getDir()));
		  double t2 = (-ray.getDir().dot((ray.getOrigin() - origin)) - sqrt(discriminant(ray)))/(ray.getDir().dot(ray.getDir()));
		  MyPoint intersect1 = ray.getOrigin() + (ray.getDir() * t1);
		  MyPoint intersect2 = ray.getOrigin() + (ray.getDir() * t2);
		  MyVector normvec1 = ((intersect1/radius) - (origin/radius)).normal();
		  MyVector normvec2 = ((intersect2/radius) - (origin/radius)).normal();
		  if ( t1 < 0 || t1 >std::numeric_limits<double>::infinity()) return Intersection();
		  if ( t2 < 0 || t2 >std::numeric_limits<double>::infinity()) return Intersection();

		  return Intersection(t1, t2, intersect1, intersect2, normvec1, normvec2, this);
		}
  }else if (box.intersect(ray) && renderflag ==1) {
	  return box.getIntersect(ray);
  } else {
	  return Intersection();
  }
  return Intersection();

}
