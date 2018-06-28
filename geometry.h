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
    float dot(const Vector &v) const;
    Vector vectorProduct(const Vector & v) const;
    void normalize();
    void setLength(float d);
    float getLength() const;
};

Point translate(const Point &p, const Vector &v);
float distanceFromPlane(const Point &p1, const float &A,const float &B,const float &C,const float &D);
bool onPlane(const Point &p, const float &A,const float &B,const float &C,const float &D);
float pointsDistance(const Point &p1,const Point &p2);
float pointBetween(const Point &p,const Point &s,const Point &e);

class Colour {
public:
    float x,y,z;
    Colour ();
    Colour (float _x,float _y,float _z);
    Colour operator+(const Colour &c);
    Colour operator*(const float &c);
    Colour operator*(const Colour &c);
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

class Plane:public Object{
    Vector normalVector;
public:
    Plane();
    Plane(const Point &p,const Vector &v,const Colour &col,const Colour &emc);
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
    virtual Vector getNormalVector(const Point &hit);
};

class Cylinder:public Object{
    Vector heightVector;
    Vector baseVector;
    Point closerPoint(const Vector &v1,const Vector &v2,const Point &origin);
    float intersectBase(const Point &origin,const Vector &direction,const Point &cent);
public:
    Cylinder();
    Cylinder(const Point &p, const Vector &vh,const Vector &vp,const Colour &col,const Colour &em);
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
    virtual Vector getNormalVector(const Point &hit);
};

class Cone:public Object {
	Vector heightVector;
	float alfa;
	float height;
	float intersectBase(const Point &origin,const Vector &direction);
public:
    Cone();
    Cone(const Point &p, const Vector &vh,const float& a,const float&h,const Colour &col,const Colour &em);
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
    virtual Vector getNormalVector(const Point &hit);
};

class Cube:public Object {
	Vector a,b,c;
	float intersectOnPlane(const Point &origin,const Vector &direction,const Vector &a,const Vector &b,const Vector &c);
public:
    Cube();
    Cube(const Point &p, const Vector &a,const Vector &b,const Colour &col,const Colour &em);
    virtual bool intersect(const Point &origin,const Vector &direction,float &t0, float &t1);
    virtual Vector getNormalVector(const Point &hit);
};

class Space{
    Object **objects;
    int objectsCount;
public:
    Space(int n);
    ~Space();
    void addObject(Object *obj);
    Object* getObject(int i) const;
    int getSize() const;
};

#endif
