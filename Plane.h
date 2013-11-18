//
//  Plane.h
//  raytra
//
//  Created by Orlando Pineda on 10/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef raytra_Plane_h
#define raytra_Plane_h
#include "Surface.h" 
#include "Intersection.h"
#include <utility>
#include <vector>
#include "Materials.h"
using namespace std;

class Plane : public Surface {
    MyVector norm;
    float d; // Distance to the origin
    Material mats;
public:
    Plane(MyVector, float, Material);
    Intersection intersect(Ray, int);
    Material getMaterial(){return mats;};

    
};



#endif
