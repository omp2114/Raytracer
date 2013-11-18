/*
 *  Materials.h
 *
 *
 * Created by Orlando Pineda on 9/22/12.
 * 
 * Stores specular, diffuse, and reflective values for a certain shape.
 */
#include "Materials.h"


Material::Material() {}
Material::Material(double dif[3], double spec[3], double phong, double r[3]) {
	phonge = phong;
  for (int i = 0; i < 3; i++){
    specularc[i] = spec[i];
    diffusec[i] = dif[i];
    reflection[i] = r[i];
  }
}
bool Material::isReflective() {
  if ((reflection[0]!=0) || (reflection[1] !=0) || (reflection[2] !=0)) return true;
  return false;
}
