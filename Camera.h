/*
 *  Camera.h
 *
 *
 * Created by Orlando Pineda on 9/23/12.
 *
 * Code for the camera class
 */
#ifndef _Camera_h
#define _Camera_h
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>
#include "Surface.h"
#include "Intersection.h"
#include "light.h"
#include <iostream>
#include <algorithm>


using namespace std;
using namespace Imf;
using namespace Imath;

#include "Ray.h"
extern vector<Surface*> objectsList;
class Camera {
  MyPoint eye;
  vector<Light*> point_light;
  vector<Light*> ambient_light;
  vector<Light*> area_light;

  int pixel_width;
  int pixel_height;
  float d; // focal length
  MyVector direction;
  MyVector u;
  MyVector v;
  MyVector w;
  vector<Surface*> surfaces;

  int nx;
  int ny;
  
  float l,r,t,b;
public:
  Camera();
  Camera(MyPoint&, MyVector&, double, double, double, double, float);
	void setCamera(MyPoint&, MyVector&, double, double, double, double, float);
  void setPointLight(vector<Light*>);
  void setAmbientLight(vector<Light*>);
  void setAreaLight(vector<Light*>);
  void generatePixels(const char fileName[], int , int, int);
  void writeRgba(const char fileName[], const Rgba * );
  vector<MyPoint> genJitter(int n);
  vector<MyPoint> shuffle(vector<MyPoint>);
  vector<double> calculateShading(Ray, Intersection, Light l);
  vector<double> calculateAmbient(Intersection, Light l);
  vector<double> rayColor(Ray, double , double, double, int, int);
  Ray generateRay(int, int);
  Intersection hit(Ray, double, double, int);
  void setSurfaces(vector<Surface*> temp) {
    surfaces = temp;
  }
};

#endif
