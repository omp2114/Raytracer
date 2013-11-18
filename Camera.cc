/*
 *  Camera.cc
 *
 *
 * Created by Orlando Pineda on 9/23/12.
 *
 * Code for the camera class
 */

#include <iostream>
#include "Camera.h" 
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>
#include "Surface.h"
#include "Intersection.h"
#include <iostream>
#include <limits>
using namespace std;
using namespace Imf;
using namespace Imath;
Camera::Camera() {
	
}
Camera::Camera(MyPoint& e, MyVector& dir, double iw, double ih, double pw, double ph, float f) {
  MyVector up(0,1,0);
  eye = e;

  pixel_width = pw;
  pixel_height = ph;
  nx = pw;
  ny = ph;
  d=f;
  direction = dir;
  l = -iw/2;
  r = iw/2; 
  t = -ih/2;
  b = ih/2;
  u = (direction * up).normal();
  v = (u * direction).normal();
  w = (-direction).normal();
}

// The code that writes the colors into a matrix of pixels that is to be
// written into the image
void Camera::generatePixels(const char fileName[], int primary, int shadow, int renderflag) {
	Array2D<Rgba> pixels;
	pixels.resizeErase(pixel_height, pixel_width);
  int n = 2;
  for (int i = 0; i < pixel_width; i++) {
    for (int j = 0; j < pixel_height; j++) {
      vector<double> color;
      color.clear();
      color.push_back(0);
      color.push_back(0);
      color.push_back(0);
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
          srand((unsigned)time(NULL));
          double temp = ((double)rand() / (double)RAND_MAX);
          Ray genray = generateRay(i + (k + temp)/n, j+(l + temp)/n);
          vector<double> c = rayColor(genray, .01, std::numeric_limits<double>::infinity(), 0, shadow, renderflag);
          color[0] += c[0];
          color[1] += c[1];
          color[2] += c[2];
        }
      }
      Rgba& px = pixels[j][i];
      px.r = color[0]/(n * n);
      px.b = color[2]/(n * n);
      px.g = color[1]/(n * n);
	    }
	  }
	writeRgba(fileName,&pixels[0][0]);
}

// The code that actually writes the image file.
void Camera::writeRgba(const char fileName[], const Rgba *pixels) {
  RgbaOutputFile file(fileName, pixel_width, pixel_height, WRITE_RGBA);
  file.setFrameBuffer (pixels, 1, pixel_width);
  file.writePixels (pixel_height);
}

// Code that generates the rays that will shoot into the environment
Ray Camera::generateRay(int i , int j) {
  double uv = l + (r-l) * ( i + 0.5)/ nx;
  double vv = b + (t-b) * (j + 0.5)/ny;

  return Ray(eye, ((w * -d) + (u * uv)+ (v * vv)));
}

// Sets point lights read in from object
void Camera::setPointLight(vector<Light*> l) {
  point_light = l;
}

// Sets ambient lights read in from object
void Camera::setAmbientLight(vector<Light *> l) {
  ambient_light = l;
}

// Sets area light read in from object
void Camera::setAreaLight(vector<Light*> a) {
	area_light = a;
}

// Returns a color vector for a certain point using Blinn-Phong shading
vector<double> Camera::calculateShading(Ray genray, Intersection intersect, Light light) {
  MyVector v = (-genray.getDir()).normal();
  MyVector l = (light.getOrigin() - intersect.getIntersection1()).normal();
  MyVector h = (v + l).normal();
  
  float krd = intersect.getSurfaceId()->getMaterial().getDiffuse()[0];
  float krs = intersect.getSurfaceId()->getMaterial().getSpecular()[0];
  double lr = (krd * light.getIntensity()[0] * max(0.0, intersect.getNormal1().dot(l))) + (krs * light.getIntensity()[0] * pow( max(0.0, intersect.getNormal1().dot(h)), intersect.getSurfaceId()->getMaterial().getPhong()));
  
  float kgd = intersect.getSurfaceId()->getMaterial().getDiffuse()[1];
  float kgs = intersect.getSurfaceId()->getMaterial().getSpecular()[1];
  double lg = (kgd * light.getIntensity()[1] * max(0.0, intersect.getNormal1().dot(l))) + (kgs * light.getIntensity()[0] * pow( max(0.0, intersect.getNormal1().dot(h)), intersect.getSurfaceId()->getMaterial().getPhong()));
  
  float kbd = intersect.getSurfaceId()->getMaterial().getDiffuse()[2];
  float kbs = intersect.getSurfaceId()->getMaterial().getSpecular()[2];
  double lb = (kbd * light.getIntensity()[2] * max(0.0, intersect.getNormal1().dot(l))) + (kbs * light.getIntensity()[0] * pow( max(0.0, intersect.getNormal1().dot(h)), intersect.getSurfaceId()->getMaterial().getPhong()));
  
  vector<double> ls;
  ls.push_back(lr);
  ls.push_back(lg);
  ls.push_back(lb);
  return ls;
}

// Calculates the ambient light value to be added to the image
vector<double> Camera::calculateAmbient(Intersection intersect, Light light) {
  float krd = intersect.getSurfaceId()->getMaterial().getDiffuse()[0];
  float kgd = intersect.getSurfaceId()->getMaterial().getDiffuse()[1];
  float kbd = intersect.getSurfaceId()->getMaterial().getDiffuse()[2];
  double lr = light.getIntensity()[0];
  double lg = light.getIntensity()[1];
  double lb = light.getIntensity()[2];
  vector<double> ls;
  ls.push_back(krd * lr);
  ls.push_back(kgd * lg);
  ls.push_back(kbd * lb);
  return ls;
}

// Calculates whether or not a ray has a "hit" which basically means if the ray
// intersects any shapes as moves through the environment
Intersection Camera::hit(Ray ray, double t0, double t1, int renderflag) {
  Intersection previous;
  for (int k = 0; k < (int)surfaces.size(); k++) { 
    Ray genray = ray;
    Intersection intersect = surfaces[k]->intersect(genray, renderflag);
    if (intersect.getIntersected()) {
      if (!previous.getIntersected()) {
        previous = intersect;
      } 
      Intersection intersect = surfaces[k]->intersect(ray, renderflag);
      if (intersect.hasSecond()) {
        if ((intersect.getIntersection1() - ray.getOrigin()).getMagnitude() < (intersect.getIntersection2() - /*eye*/ray.getOrigin()).getMagnitude()) {
          if ((intersect.getIntersection1() - ray.getOrigin()).getMagnitude() < (previous.getIntersection1() - /*eye*/ray.getOrigin()).getMagnitude()) {
            previous = intersect.separateFirst();
          }
        } else {
          if ((intersect.getIntersection2() - ray.getOrigin()).getMagnitude() < (previous.getIntersection1() - /*eye*/ray.getOrigin()).getMagnitude()) {
            previous = intersect.separateSecond();
          }
        }
      } else {
        if ((intersect.getIntersection1() - ray.getOrigin()).getMagnitude() < (previous.getIntersection1() - /*eye*/ray.getOrigin()).getMagnitude()) {
          previous = intersect;
        }
      }
    } 
  }
  if (previous.getT() < t0	) return Intersection();
  if (previous.getT() > t1) return Intersection();
  return previous;
}

// Puts it all together. If a ray hits, it calculates its color based on the lighting and 
// nearby objects. Handles reflection recursively.
vector <double> Camera::rayColor(Ray ray, double e, double t1, double recursion_limiter, int shadowpoints, int renderflag) {
  vector<double> color;
  color.push_back(0);
  color.push_back(0);
  color.push_back(0);
  Intersection hitrec = hit(ray, e, t1, renderflag);
  Intersection shadow_holder;
  if (hitrec.getIntersected()) {
    MyPoint p = hitrec.getIntersection1();
		if (ambient_light.size() > 0) {
			  for (int f = 0; f < (int)ambient_light.size(); f++) {
			    vector<double> l = calculateAmbient(hitrec, *ambient_light[0]);
			    color[0] += l[0];
			    color[1] += l[1];
			    color[2] += l[2];
			  }
		}
    for (int lights = 0; lights < point_light.size(); lights ++) {
      MyVector light_direction = (point_light[lights]->getOrigin() - hitrec.getIntersection1());
      MyPoint light_intersection = hitrec.getIntersection1();
      Ray shadow_ray(light_intersection, light_direction);
      Intersection shadowIntersection = hit(shadow_ray, e, t1, renderflag);
      if (shadowIntersection.getIntersected()) {
        shadow_holder = shadowIntersection;
      }
    }
    if (!shadow_holder.getIntersected()) {
      for (int q_ =0; q_ < point_light.size(); q_++) {
        vector<double> l = calculateShading(ray, hitrec, *point_light[q_]);
        color[0] += l[0];
        color[2] += l[2];
        color[1] += l[1];
      }

    }
  }
  if (hitrec.getIntersected() && recursion_limiter < 3) {
    MyVector reflection = ray.getDir() -  hitrec.getNormal1() * (2 * (ray.getDir().dot(hitrec.getNormal1())));
    Ray refray(hitrec.getIntersection1(), reflection);
    vector<double>  refcolor = rayColor(refray, e, std::numeric_limits<double>::infinity(), recursion_limiter +1, shadowpoints, renderflag);
    color[0] += hitrec.getSurfaceId()->getMaterial().getReflective()[0] * refcolor[0];
    color[1] += hitrec.getSurfaceId()->getMaterial().getReflective()[1] * refcolor[1];
    color[2] += hitrec.getSurfaceId()->getMaterial().getReflective()[2] * refcolor[2];
  }

    
  return color;
}
vector<MyPoint> Camera::shuffle(vector<MyPoint> point) {
	vector<MyPoint> points = point;
	for (int i = points.size() -1; i >=1; i--) {
		srand((unsigned)time(NULL));
    int temp = rand() % (i+1);
		MyPoint p1 = points[temp];
		MyPoint p2 = points[i];
		points[temp] = p2;
		points[i] = p1;
	}
	return points;
}
vector<MyPoint> Camera::genJitter(int n) {
	vector<MyPoint> points;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			srand((unsigned)time(0));
			double temp = ((double)rand() / (double)(RAND_MAX +1.0));
			points.push_back(MyPoint((i +temp)/n, (j+temp)/n, 0));
		}
	}
	return points;
	
}
