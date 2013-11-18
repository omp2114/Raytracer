#ifndef __VECTOR_H__
#define __VECTOR_H__


#include <iostream>
using namespace std;

#include "Point.h"
#include <cmath>

class MyPoint;

class MyVector {
  MyPoint p1();
  MyPoint p2();
  double x, y, z;
public:
  MyVector();
  MyVector(MyPoint&, MyPoint&);
  MyVector(double, double, double);
  MyVector normal();
  double getX() { return x;};
  double getY() { return y;};
  double getZ() { return z;};
  double getMagnitude(){return sqrt(pow(x,2) + pow(y,2) + pow(z,2));};
  double dot(MyVector other);
  double dot(MyPoint other);
    
  MyVector operator+(MyVector other);
  MyVector operator*(MyVector other);
  MyVector operator-(MyVector other);
  MyVector operator*(double scalar);
  MyVector operator-();
  MyVector operator/(double scalar);
  void printVector();
  double getLength();
};
#endif
