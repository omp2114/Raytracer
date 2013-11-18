#ifndef _Materials_h
#define _Materials_h

#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;
class Material {
	double diffusec[3];
	double specularc[3];
  double reflection[3];
	double phonge;

public:
	Material();
	Material(double[3], double[3], double, double[3]);
  /*~Material() {
    delete diffusec;
    delete specularc;
  }*/
	double* getDiffuse() { return diffusec;};
	double* getSpecular() { return specularc;};
	double getPhong() { return phonge;};
  double* getReflective() { return reflection;};
  bool isReflective();
};

















#endif
