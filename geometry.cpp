#include <iostream>
#include <cmath>
using namespace std;

class Point{
public:
    float x,y,z;
    Point():x(0.0),y(0.0),z(0.0){};
    Point(float _x, float _y, float _z):x(_x),y(_y),z(_z){};
};


class Vector{
public:
    float x,y,z;
    Vector():x(0),y(0),z(0){};
    Vector(float _x, float _y, float _z):x(_x),y(_y),z(_z){};
    Vector(Point start, Point ending):x(ending.x-start.x),y(ending.y-start.y),z(ending.z-start.z){};
    Vector operator+( const Vector &v){
        return Vector(x+v.x,y+v.y,z+v.z);
    }
    Vector operator-(const Vector &v){
        return Vector(x-v.x,y-v.y,z-v.z);
    }
    Vector operator*(const float &f){
        return Vector(x*f,y*f,z*f);
    }
    float dot(const Vector &v){
        return (x*v.x+y*v.y+z*v.z);
    }
    void norm(){
        float l=sqrt(x*x+y*y+z*z);
        x=x/l;
        y=y/l;
        z=z/l;
    }
};

class Colour {
public:
    float x,y,z;
    Colour ():x(0),y(0),z(0){};
    Colour (float _x,float _y,float _z):x(_x),y(_y),z(_z){};
};

class Object{
public:
    Colour c;
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1){}
};

class Sphere:Object{
public:
    Point center;
    float radius;
    Colour colour;
    Sphere(const Point &c, const float &rad, const Colour &col):center(c),radius(rad),colour(col){};
    bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
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

};
