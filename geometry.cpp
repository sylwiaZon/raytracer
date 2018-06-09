#include <iostream>
#include <cmath>
#include "geometry.h"
using namespace std;

Point::Point():x(0.0),y(0.0),z(0.0){};
Point::Point(float _x, float _y, float _z):x(_x),y(_y),z(_z){};


Vector::Vector():x(0),y(0),z(0){};
Vector::Vector(float _x, float _y, float _z):x(_x),y(_y),z(_z){};
Vector::Vector(Point start, Point ending):x(ending.x-start.x),y(ending.y-start.y),z(ending.z-start.z){};
Vector Vector::operator+( const Vector &v){
    return Vector(x+v.x,y+v.y,z+v.z);
}
Vector Vector::operator-(const Vector &v){
    return Vector(x-v.x,y-v.y,z-v.z);
}
Vector Vector::operator*(const float &f){
    return Vector(x*f,y*f,z*f);
}
float Vector::dot(const Vector &v){
    return (x*v.x+y*v.y+z*v.z);
}
void Vector::norm(){
    float l=sqrt(x*x+y*y+z*z);
    x=x/l;
    y=y/l;
    z=z/l;
}

Colour::Colour ():x(0),y(0),z(0){};
Colour::Colour (float _x,float _y,float _z):x(_x),y(_y),z(_z){};

Sphere::Sphere(const Point &c, const float &rad, const Colour &col):center(c),radius(rad){ colour = col; };
bool Sphere::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
    Vector l(origin,center);
    float dp=l.dot(direction);
    if(dp<0)return false;
    float dist2=l.dot(l)-dp*dp;
    if(dist2>radius*radius) return false;
    float t=sqrt(radius*radius-dist2);
    t0=dp-t;
    t1=dp+t;
    return true;
}

Space::Space(int n):objectsCount(0){objects=new Object [n];}
Space::~Space(){delete []objects;}
void Space::addObject(const Object &obj){
    objects[objectsCount]=obj;
    objectsCount++;
}
Object Space::getObject(int i){
    return objects[i];
}
int Space::getSize(){
    return objectsCount;
}
