//
//  Header.h
//  
//
//  Created by Orlando Pineda on 9/23/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Header_h
#define _Header_h


#include <utility>
#include <vector>
#include "Materials.h"
using namespace std;
#include "Intersection.h"
#include "Surface.h"
#include "BoundingBox.h"
class Sphere: public Surface {
  MyPoint origin;
  Material mats;
  float radius;
  BoundingBox box;
public:
  Sphere(MyPoint&, float, Material);
  double discriminant(Ray); 
  Intersection intersect(Ray, int);
  Material getMaterial(){return mats;};

  //vector<double> getPixelColor();
};
#endif
