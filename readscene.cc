#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Sphere.h"
#include "Vector.h"
#include "Camera.h"
#include "Materials.h"
#include "Triangle.h"
#include "light.h"
#include "Plane.h"
using namespace std;

#define IM_DEBUGGING
vector<Surface*> objectsList;
vector<Light*> pointLightList;
vector<Light*> ambientLightList;
vector<Light*> areaLightList;


Camera * cam;
Material * lastMaterialLoaded = NULL;

//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//
void read_wavefront_file (
                          const char *file,
                          std::vector< int > &tris,
                          std::vector< float > &verts)
{
  
  // clear out the tris and verts vectors:
  tris.clear ();
  verts.clear ();
  
  ifstream in(file);
  char buffer[1025];
  string cmd;
  
  
  for (int line=1; in.good(); line++) {
    in.getline(buffer,1024);
    buffer[in.gcount()]=0;
    
    cmd="";
    
    istringstream iss (buffer);
    
    iss >> cmd;
    
    if (cmd[0]=='#' or cmd.empty()) {
      // ignore comments or blank lines
      continue;
    } 
    else if (cmd=="v") {
      // got a vertex:
      
      // read in the parameters:
      double pa, pb, pc;
      iss >> pa >> pb >> pc;
      
      verts.push_back (pa);
      verts.push_back (pb);
      verts.push_back (pc);
    } 
    else if (cmd=="f") {
      // got a face (triangle)
      
      // read in the parameters:
      int i, j, k;
      iss >> i >> j >> k;
      
      // vertex numbers in OBJ files start with 1, but in C++ array
      // indices start with 0, so we're shifting everything down by
      // 1
      tris.push_back (i-1);
      tris.push_back (j-1);
      tris.push_back (k-1);
    } 
    else {
      std::cerr << "Parser error: invalid command at line " << line << std::endl;
    }
    
  }
  
  in.close();
  
  //   std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}
// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
  
  float thisFloatVal = 0.;    // the return value
  
  if (whichToken == 0) {
    cerr << "error: the first token on a line is a character!" << endl;
    exit (-1);
  }
  
  // c++ string class has no super-easy way to tokenize, let's use c's:
  char *cstr = new char [inString.size () + 1];
  
  strcpy (cstr, inString.c_str());
  
  char *p = strtok (cstr, " ");
  if (p == 0) {
    cerr << "error: the line has nothing on it!" << endl;
    exit (-1);
  }
  
  for (int i = 0; i < whichToken; i++) {
    p = strtok (0, " ");
    if (p == 0) {
      cerr << "error: the line is not long enough for your token request!" << endl;
      exit (-1);
    }
  }
  
  thisFloatVal = atof (p);
  
  delete[] cstr;
  
  return thisFloatVal;
}


//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//
void parseSceneFile (char *filnam)
{
  
  ifstream inFile(filnam);    // open the file
  string line;
  
  if (! inFile.is_open ()) {  // if it's not open, error out.
    cerr << "can't open scene file" << endl;
    exit (-1);
  }
  
  
  // Note: you'll have to keep track of whatever the last material
  // you loaded in was, so you can apply it to any geometry that gets loaded. 
  // So here, you'll have something like:
  //
  // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
  //
  // and each time you load in a new piece of geometry (sphere, triangle, plane)
  // you will set its material to lastMaterialLoaded.
  
  
  while (! inFile.eof ()) {   // go through every line in the file until finished
    
    getline (inFile, line); // get the line
    
    switch (line[0])  {     // we'll decide which command based on the first character
        
        //
        // geometry types:
        //
        // NOTE: whichever type of geo you load in, set its material to
        // be "lastMaterialLoaded"
        //
      case 's': {
        // it's a sphere, load in the parameters
        
        float x, y, z, r;
        x = getTokenAsFloat (line, 1); 
        y = getTokenAsFloat (line, 2); 
        z = getTokenAsFloat (line, 3); 
        r = getTokenAsFloat (line, 4); 

        MyPoint center((double)x,(double)y,(double)z);
				Sphere *temp = new Sphere(center, r, *lastMaterialLoaded); 
				objectsList.push_back(temp);


        // build your sphere here from the parameters
        // i.e. you must call your sphere constructor and set its position
        // and radius from the above values. You must also put your new
        // sphere into the objects list (which can be global)
        // So something like;
        // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
        // ms->setMaterial (lastMaterialLoaded)
        // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
        
#ifdef IM_DEBUGGING
        // if we're debugging, show what we got:
        cout << "got a sphere with ";
        cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
#endif
				}
        break;
        
      case 't':  { // triangle
        float x1, y1, z1, x2, y2, z2, x3, y3, z3;
        x1 = getTokenAsFloat (line, 1); 
        y1 = getTokenAsFloat (line, 2); 
        z1 = getTokenAsFloat (line, 3); 
        x2 = getTokenAsFloat (line, 4); 
        y2 = getTokenAsFloat (line, 5); 
        z2 = getTokenAsFloat (line, 6); 
        x3 = getTokenAsFloat (line, 7); 
        y3 = getTokenAsFloat (line, 8); 
        z3 = getTokenAsFloat (line, 9); 
        cout << "Got a Triangle" << endl;

        MyPoint a(x1, y1, z1);
        MyPoint b(x2, y2, z2);
        MyPoint c(x3, y3, z3);
        Triangle *temp = new Triangle(a, b, c, *lastMaterialLoaded);
        objectsList.push_back(temp);

        
      }
        break;
        
      case 'p': {  // plane
        float nx, ny, nz, d;
        nx = getTokenAsFloat(line, 1);
        ny = getTokenAsFloat(line, 2);
        nz = getTokenAsFloat(line, 3);
        d  = getTokenAsFloat(line, 4);
        cout << "Got a plane" << endl;
        MyVector normal(nx, ny, nz);
        Plane *temp = new Plane(normal, d, *lastMaterialLoaded);
        objectsList.push_back(temp);
        
      }
        
        break;
       
        //
        // camera:
        //
      case 'c':   {// camera
		      // one trick here: the cameras pixel count (width, height) are integers,
		      // so cast them.
					float x, y, z, vx, vy, vz, d, iw, ih, pw, ph;
					x = getTokenAsFloat (line, 1);
					y = getTokenAsFloat (line, 2);
					z = getTokenAsFloat (line, 3);
					vx = getTokenAsFloat (line, 4);
					vy = getTokenAsFloat (line, 5);
					vz = getTokenAsFloat (line, 6);
					d = getTokenAsFloat (line, 7);
					iw = getTokenAsFloat (line, 8);
					ih = getTokenAsFloat (line, 9);
					pw = getTokenAsFloat (line, 10);
					ph = getTokenAsFloat (line, 11);

					MyPoint eye((double)x,(double)y,(double)z);
					MyVector direction((double)vx, (double)vy, (double)vz);
					


				cam = new Camera(eye,direction,iw,ih,pw,ph,d);

				
				}	
        break;
        
        //
        // lights:
        //
      case 'l': {  // light
        
        // slightly different from the rest, we need to examine the second param,
        // which is at the third position on the line:
        switch (line[2]) {
          case 'p': {
            float x, y, z, r, g, b;
            x = getTokenAsFloat(line, 2);
            y = getTokenAsFloat(line, 3);
            z = getTokenAsFloat(line, 4);
            r = getTokenAsFloat(line, 5);
            g = getTokenAsFloat(line, 6);
            b = getTokenAsFloat(line, 7);

            MyPoint origin(x,y,z);
            float intensity[3] = {r, g, b};
            Light * light = new Light(origin, intensity);
            pointLightList.push_back(light);
            
            
          }// point light
            break;
          /*case 'd':   // directional light
            break;*/
          case 'a': {  // ambient light
            float r, g, b;
            r = getTokenAsFloat(line, 2);
            g = getTokenAsFloat(line, 3);
            b = getTokenAsFloat(line, 4);
            Light *light = new Light(r, g, b);
            ambientLightList.push_back(light);
          }
            break;
          case 's' : {
        	float x,y,z,vx,vy,vz,ux,uy,uz,len,r,g,b;
        	x = getTokenAsFloat(line, 2);
        	y = getTokenAsFloat(line, 3);
        	z = getTokenAsFloat(line, 4);
        	vx = getTokenAsFloat(line,5);
         	vy = getTokenAsFloat(line, 6);
            vz = getTokenAsFloat(line, 7);
            ux = getTokenAsFloat(line, 8);
            uy = getTokenAsFloat(line,9);
         	uz = getTokenAsFloat(line, 10);
            len = getTokenAsFloat(line, 11);
            r = getTokenAsFloat(line, 12);
            g = getTokenAsFloat(line,13);
            b = getTokenAsFloat(line,14);
            MyPoint center(x,y,z);
            MyVector udirection(ux,uy,uz);
            MyVector vdirection(vx,vy,vz);
            float rgb[3]= {r, g, b};
            Light * light = new Light(center, udirection, vdirection, len, rgb);
            areaLightList.push_back(light);
          }
          	break;
            
        }
   //    
      }
        break;
    //    
        //
        // materials:
        //
      case 'm':{
    	  float dr, dg, db, sr, sg, sb, r, ir, ig, ib;
        dr = getTokenAsFloat (line, 1);
        dg = getTokenAsFloat (line, 2);
        db = getTokenAsFloat (line, 3);
        sr = getTokenAsFloat (line, 4);
        sg = getTokenAsFloat (line, 5);
        sb = getTokenAsFloat (line, 6);
        r = getTokenAsFloat (line, 7);
        ir = getTokenAsFloat (line, 8);
        ig = getTokenAsFloat (line, 9);
        ib = getTokenAsFloat (line, 10);
        double d[3] = {dr, dg, db};
        double s[3] = {sr, sg, sb};
        double i[3] = {ir, ig, ib};

        lastMaterialLoaded = new Material(d, s, r, i);

      }   // material
        // the trick here: we should keep a pointer to the last material we read in,
        // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
        // we migh then do something like this:
        //
        //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
        //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);
        //
       break;
        
        
      case '/':{}
        // don't do anything, it's a comment
        break;
        
        
        //
        // options
        //
      case 'w':  {
        string  filename = line;
        string file = filename.substr(2);
        
        
        std::vector< int > tris;
        std::vector< float > verts;
        read_wavefront_file(file.c_str(), tris, verts);
        
        for(int i = 0; i < (int) tris.size(); i+=3) {
          // Get the Indexes for the triangle vertices
          int idx1 = tris[i];
          int idx2 = tris[i+1];
          int idx3 = tris[i+2];
          
          // Create the points in correct order
          MyPoint first(verts[idx1 *3], verts[idx1*3+1], verts[idx1*3+2]);
          MyPoint second(verts[idx2 *3], verts[idx2*3+1], verts[idx2*3+2]);
          MyPoint third(verts[idx3 *3], verts[idx3*3+1], verts[idx3*3+2]);
          Triangle * temp = new Triangle(first, second, third, *lastMaterialLoaded);
          
          // Push Triangle into objects list
          objectsList.push_back(temp);
          
        }
        //parseSceneFile(<#char *filnam#>)
      }// make your own options if you wish {
        
        break;
    }
    
  }
}



int main (int argc, char *argv[])
{
  
  if (argc != 6) {
    cerr << "useage: raytra scenefilename" << endl;
		cout << "Please make sure to pass the source file AND the write file AND the number of primary followed by the number of shadow rays AND a flag of 0 to render normally and 1 to render bounding boxes" << endl;
    return -1;
  }

  parseSceneFile (argv[1]);
  (*cam).setPointLight(pointLightList);
  (*cam).setAmbientLight(ambientLightList);
  (*cam).setAreaLight(areaLightList);
  (*cam).setSurfaces(objectsList);
  (*cam).generatePixels(argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
  //cout << (double) 1/-0 << endl;
  delete cam;
  delete lastMaterialLoaded;
  /*for (Surface* surface : objectsList) {
    delete surface;
  }*/


  
  return 0;
}
