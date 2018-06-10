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
Vector Vector::vectorProduct(const Vector &v){
    return Vector(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
}
void Vector::normalize(){
    float l=getLenght();
    x=x/l;
    y=y/l;
    z=z/l;
}
void Vector::setLenght(float d){
    normalize();
    x=x*d;
    y=y*d;
    z=z*d;
}
float Vector::getLenght(){
    return sqrt((*this).dot(*this));
}

Point translate(const Point &p, const Vector &v){
    return Point(p.x+v.x,p.y+v.y,p.z+v.z);
}

Colour::Colour ():x(0),y(0),z(0){};
Colour::Colour (float _x,float _y,float _z):x(_x),y(_y),z(_z){};
Colour Colour::operator+(const Colour &c){
    return Colour(x+c.x,y+c.y,z+c.z);
}
Colour Colour::operator*(const float &c){
    return Colour(x*c,y*c,z*c);
}
Sphere::Sphere(){}
Sphere::Sphere(const Point &c, const float &rad, const Colour &col,const Colour &emc):radius(rad){
    colour = col;
    center=c;
    emissionColour=emc;
};
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

Vector Sphere::getNormalVector(const Point &hit){
    return Vector (center,hit);
}
Space::Space(int n):objectsCount(0){objects=new Sphere [n];}
Space::~Space(){delete []objects;}
void Space::addObject(const Sphere &obj){
    objects[objectsCount]=obj;
    objectsCount++;
}
Sphere Space::getObject(int i)const {
    return objects[i];
}
int Space::getSize()const {
    return objectsCount;
}
