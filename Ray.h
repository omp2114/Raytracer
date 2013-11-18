//
//  Ray.h
//  
//
//  Created by Orlando Pineda on 9/22/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Ray_h
#define _Ray_h
#include "Vector.h"
class Ray {
  MyPoint origin;
  MyVector dir;
public:
  Ray();
  Ray(MyPoint, MyVector);
  Ray(MyPoint&, MyPoint&, MyPoint&);
  MyPoint getOrigin();
  MyVector& getDir();
  MyPoint getPoint(double);
  MyVector getNormDir();
};


#endif
