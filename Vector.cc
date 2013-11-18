#include "Vector.h"

MyVector::MyVector() {
  x = 0;
  y = 0;
  z = 0;
}

MyVector::MyVector(MyPoint& a, MyPoint& b) {
  x = a.getX() - b.getX();
  y = a.getY() - b.getY();
  z = a.getZ() - b.getZ();
}
MyVector::MyVector(double x1, double y1, double z1) {
  x = x1;
  y = y1;
  z = z1;
}
double MyVector::getLength() {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
void MyVector::printVector() {
  cout << "{" << x << "i ," << y << "j ," << z << "k}" << endl;
}
MyVector MyVector::normal() {
  // Compute l
  return MyVector(x/getLength(), y/getLength(), z/getLength());  
}
MyVector MyVector::operator+(MyVector other) {
  return MyVector(x+other.getX(), y+ other.getY(), z+other.getZ());
}
MyVector MyVector::operator-() {
  return MyVector(-x, -y, -z);
}
MyVector MyVector::operator-(MyVector other) {
  return MyVector(x - other.getX(), y - other.getY(), z - other.getZ());
}
MyVector MyVector::operator/(double scalar) {
  return MyVector(x/scalar, y/scalar, z/scalar);
}
MyVector MyVector::operator*(MyVector other) {
  return MyVector(  (y*other.getZ()) - z * other.getY(), z * other.getX() - x*other.getZ(), x * other.getY() - y * other.getX());
}
MyVector MyVector::operator*(double scalar) {
  return MyVector( x * scalar, y * scalar, z * scalar);
}
double MyVector::dot(MyVector other) {
  return x * other.getX() + y * other.getY() + z * other.getZ();
}
double MyVector::dot(MyPoint other) {
    return x * other.getX() + y * other.getY() + z * other.getZ();
}
