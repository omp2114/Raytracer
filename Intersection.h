//
//  Intersection.h
//  
//
//  Created by Orlando Pineda on 9/23/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Intersection_h
#define _Intersection_h
#include "Vector.h"
#include "Surface.h"
class Surface;
class Intersection {
  MyPoint point1;
  double t1;
  MyPoint point2;
  Surface*  surface_id;
  MyVector normal1;
  MyVector normal2;
  double t2;
  bool intersected;
  bool has_second;
public:
  Intersection();
  Intersection(double, MyPoint&, MyVector&, Surface*);
  Intersection(double, double, MyPoint&, MyPoint&, MyVector&, MyVector&, Surface*);
  bool getIntersected(){return intersected;};
  MyVector getNormal1(){return normal1;};
  MyVector getNormal2(){return normal2;};
  MyPoint getIntersection1(){ return point1;};
  MyPoint getIntersection2(){return point2;};
  double getT(){return t1;};
  bool hasSecond(){return has_second;};
  Intersection separateFirst() { return Intersection(t1, point1, normal1, surface_id); };
  Intersection separateSecond() {return Intersection(t2, point2, normal2, surface_id);};
  Surface* getSurfaceId(){return surface_id;};
};



#endif
