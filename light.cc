/*
 *  light.cc
 *
 *  Created by Orlando Pineda on 9/29/12.
 * 
 * Class that stores and allows access to light object information
 */

#include <iostream>
#include "light.h"

Light::Light(){}

Light::Light(MyPoint p, MyVector ud, MyVector vd, float l, float rgb[3]) {
	center = p;
	u = ud;
	v = vd;
	length = l;
	for (int i = 0; i <3; i ++) {
	    light_intensity[i] = rgb[i];
	  }
}
Light::Light(float rt, float bt, float gt) {
  light_intensity[0] = rt;
  light_intensity[1] = gt;
  light_intensity[2] = bt;
}
Light::Light(MyPoint& p, float rgb[3]) {
  light_origin = p;
  for (int i = 0; i <3; i ++) {
    light_intensity[i] = rgb[i];
  }
}
