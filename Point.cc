#include "Point.h"

MyPoint::MyPoint() {
  x = 0;
  y = 0;
  z = 0;
}
MyPoint::MyPoint(double x1, double y1, double z1) {
  x = x1;
  y = y1;
  z = z1;
}
void MyPoint::printPoint() {
  cout << "(" << x << "," << y << "," << z << ")" << endl;
}
MyVector MyPoint::operator-(MyPoint other) {
  return MyVector(*this, other);
}
MyPoint MyPoint::operator+(MyVector other) {
  return MyPoint(x + other.getX(), y + other.getY(), z+ other.getZ());
}
MyPoint MyPoint::operator/(double scalar) {
	return MyPoint(x/scalar, y/scalar, z/scalar);
}
