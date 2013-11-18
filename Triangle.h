//
//  Triangle.h
//  raytra
//
//  Created by Orlando Pineda on 10/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef raytra_Triangle_h
#define raytra_Triangle_h

#include <utility>
#include <vector>
#include "Materials.h"
using namespace std;
#include "Intersection.h"
#include "Surface.h"
#include "BoundingBox.h"
class Triangle: public Surface {
    MyPoint a;
    MyPoint b;
    MyPoint c;
    MyVector norm;
    Material mats;
    BoundingBox box;
public:
    Triangle(MyPoint, MyPoint, MyPoint, Material);
    //double discriminant(Ray); 
    Intersection intersect(Ray, int);
    Material getMaterial(){return mats;};
    
    //vector<double> getPixelColor();
};


#endif
