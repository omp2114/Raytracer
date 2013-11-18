//
//  Point.h
//  
//
//  Created by Orlando Pineda on 9/22/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Point_h
#define _Point_h

#include <iostream>
using namespace std;

#include <cmath>
#include "Vector.h"

class MyVector;

class MyPoint {
  double x, y, z;
public:
  MyPoint();
  MyPoint(double, double, double);
  double getX() {return x;};
  double getY(){return y;};
  double getZ(){return z;};
  void printPoint();
  MyVector operator-(MyPoint);
  MyPoint operator+(MyVector);
  MyPoint operator/(double);
  
};

#endif
