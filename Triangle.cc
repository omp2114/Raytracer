//
//  Triangle.cc
//  raytra
//
//  Created by Orlando Pineda on 10/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <limits>
#include <utility>
#include "Triangle.h"

Triangle::Triangle(MyPoint p1, MyPoint p2, MyPoint p3, Material material) {
  a = p1;
  b = p2;
  c = p3;
  mats = material;
  norm = ((p2 - p1) * (p3 - p1)).normal();
  double xmax=0,xmin=0,ymax = 0,ymin=0,zmax=0,zmin = 0;
  if (a.getX() >= b.getX() && a.getX() >= c.getX()) {
	  xmax = a.getX();
  }else if (b.getX() >= a.getX() && b.getX() >= c.getX()) {
	  xmax = b.getX();
  }else if (c.getX() >= a.getX() && c.getX() >= b.getX()) {
	  xmax = c.getX();
  }
  if (a.getX() <= b.getX() && a.getX() <= c.getX()) {
	  xmin = a.getX();
  }else if (b.getX() <= a.getX() && b.getX() <= c.getX()) {
	  xmin = b.getX();
  }else if (c.getX() <= a.getX() && c.getX() <= b.getX()) {
	  xmin = c.getX();
  }
  if (a.getY() <= b.getY() && a.getY() <= c.getY()) {
	  ymin = a.getY();
  }else if (b.getY() <= a.getY() && b.getY() <= c.getY()) {
	  ymin = b.getY();
  }else if (c.getY() <= a.getY() && c.getY() <= b.getY()) {
	  ymin = c.getY();
  }
  if (a.getY() >= b.getY() && a.getY() >= c.getY()) {
  	  ymax = a.getY();
  }else if (b.getY() >= a.getY() && b.getY() >= c.getY()) {
  	  ymax = b.getY();
  }else if (c.getY() >= a.getY() && c.getY() >= b.getY()) {
  	  ymax = c.getY();
  }
  if (a.getZ() <= b.getZ() && a.getZ() <= c.getZ()) {
	  zmin = a.getZ();
  }else if (b.getZ() <= a.getZ() && b.getZ() <= c.getZ()) {
	  zmin = b.getZ();
  }else if (c.getZ() <= a.getZ() && c.getZ() <= b.getZ()) {
	  zmin = c.getZ();
  }
  if (a.getZ() >= b.getZ() && a.getZ() >= c.getZ()) {
  	  zmax = a.getZ();
  }else if (b.getZ() >= a.getZ() && b.getZ() >= c.getZ()) {
  	  zmax = b.getZ();
  }else if (c.getZ() >= a.getZ() && c.getZ() >= b.getZ()) {
  	  zmax = c.getZ();
  }

  box = BoundingBox(xmin,ymin,zmin,xmax,ymax,zmax, this);
}
Intersection Triangle::intersect(Ray ray, int renderflag) {
  if (box.intersect(ray) && renderflag ==0) {
	  	double a_ = a.getX() - b.getX();
		double b_ = a.getY() - b.getY();
		double c_ = a.getZ() - b.getZ();
		double d_ = a.getX() - c.getX();
		double e_ = a.getY() - c.getY();
		double f_ = a.getZ() - c.getZ();
		double g_ = ray.getDir().getX();
		double h_ = ray.getDir().getY();
		double i_ = ray.getDir().getZ();
		double j_ = a.getX() - ray.getOrigin().getX();
		double k_ = a.getY() - ray.getOrigin().getY();
		double l_ = a.getZ() - ray.getOrigin().getZ();

		double m = a_ * (e_ * i_ - h_ * f_) + b_ * ( g_ * f_ - d_ * i_) + c_ * ( d_ * h_ - e_ * g_);
		double t = -(f_ * (a_ * k_ - j_ * b_) + e_ * (j_ * c_ - a_ * l_) + d_ * (b_ * l_ - k_ * c_)) / m;
		double t0 = 0.1;
		double t1 = std::numeric_limits<double>::infinity();
		double gama = (i_ * ( a_ * k_ - j_ * b_) + h_ * ( j_ * c_ - a_ * l_) + g_ * (b_ * l_ - k_ * c_))/m;
		double beta = (j_ * (e_ * i_ - h_ * f_) + k_ * (g_ * f_ - d_ * i_) + l_ * (d_ * h_ - e_ * g_))/m;


		if (t < t0 || t > t1) return Intersection();
		if (gama < 0 || gama > 1) return Intersection();
		if (beta < 0 || beta > 1 - gama) return Intersection();
		if (t <= 0) return Intersection();
		MyPoint hitpoint = ray.getOrigin() + ray.getDir() * t;
		return Intersection(t, hitpoint, norm,  this);
  } else if (box.intersect(ray) && renderflag ==1) {
	  return box.getIntersect(ray);
  } else {
	  return Intersection();
  }
  
}

