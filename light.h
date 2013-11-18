//
//  light.h
//  raytra
//
//  Created by Orlando Pineda on 9/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef raytra_light_h
#define raytra_light_h
#include "Vector.h"
class Light {
  int type;
  float light_intensity[3];
  MyPoint light_origin;
  MyVector directional_light;
  MyPoint center;
  MyVector v;
  MyVector u;
  float length;
public:
  Light();
  Light(MyPoint&, float[3]);
  Light(MyVector&, float, float, float);
  Light(float, float, float);
  Light(MyPoint, MyVector, MyVector, float, float[3]);
  MyPoint getOrigin() { return light_origin;};
  MyVector getDirection() { return directional_light;};
  int getType() { return type;};
  float* getIntensity() {return light_intensity;};
};


#endif
