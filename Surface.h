//
//  Surface.h
//  
//
//  Created by Orlando Pineda on 9/23/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Surface_h
#define _Surface_h
#include "Ray.h"
#include "Intersection.h"
#include "Materials.h"
class Intersection;
//#include <vector>
using namespace std;
class Surface {
public:
  virtual Intersection intersect(Ray, int) = 0;
  virtual Material getMaterial() = 0;
 // vector<double> getPixelColor();
};
#endif
