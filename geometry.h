#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include <iostream>
#include <cmath>
using namespace std;

class Point{
public:
    float x,y,z;
    Point();
    Point(float _x, float _y, float _z);
};


class Vector{
public:
    float x,y,z;
    Vector();
    Vector(float _x, float _y, float _z);
    Vector(Point start, Point ending);
    Vector operator+( const Vector &v);
    Vector operator-(const Vector &v);
    Vector operator*(const float &f);
    float dot(const Vector &v);
    void norm();
};

class Colour {
public:
    float x,y,z;
    Colour ();
    Colour (float _x,float _y,float _z);
};

class Object{
public:
    Colour colour;
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1){};
};

class Sphere:public Object{
public:
    Point center;
    float radius;
    Sphere(const Point &c, const float &rad, const Colour &col);
    bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
};

class Space{
    Object *objects;
    int objectsCount;
public:
    Space(int n);
    ~Space();
    void addObject(const Object &obj);
    Object getObject(int i);
    int getSize();
};

#endif
