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
    Vector vectorProduct(const Vector & v);
    void normalize();
    void setLenght(float d);
    float getLenght();
};

Point translate(const Point &p, const Vector &v);

class Colour {
public:
    float x,y,z;
    Colour ();
    Colour (float _x,float _y,float _z);
    Colour operator+(const Colour &c);
    Colour operator*(const float &c);
};

class Object{
public:
    Colour colour;
    Point center;
    Colour emissionColour;
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1){};
    virtual Vector getNormalVector(const Point &hit){};
};

class Sphere:public Object{
public:
    float radius;
    Sphere();
    Sphere(const Point &c, const float &rad, const Colour &col,const Colour &emc);
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
    virtual Vector getNormalVector(const Point &hit);
};

class Space{
    Sphere *objects;
    int objectsCount;
public:
    Space(int n);
    ~Space();
    void addObject(const Sphere &obj);
    Sphere getObject(int i) const;
    int getSize() const;
};

#endif
