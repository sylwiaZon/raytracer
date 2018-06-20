#include <iostream>
#include <cmath>
#include <windows.h>
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
Vector Vector::vectorProduct(const Vector &v)const{
    return Vector(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
}
void Vector::normalize(){
    float l=getLength();
    x=x/l;
    y=y/l;
    z=z/l;
}
void Vector::setLength(float d){
    normalize();
    x=x*d;
    y=y*d;
    z=z*d;
}
float Vector::getLength(){
    return sqrt((*this).dot(*this));
}

Point translate(const Point &p, const Vector &v){
    return Point(p.x+v.x,p.y+v.y,p.z+v.z);
}
float distanceFromPlane(const Point &p, const float &A,const float &B,const float &C,const float &D){
    float dist=abs(A*p.x+B*p.y+C*p.z+D);
    dist=dist/sqrt(A*A+B*B+C*C);
    return dist;
}
bool onPlane(const Point &p, const float &A,const float &B,const float &C,const float &D){
    float eps=1e-3;
    if((p.x*A+p.y*B+p.z*C+D)<eps){
        return true;
    }
    return false;
}
float pointsDistance(const Point &p1,const Point &p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z);
}


Colour::Colour ():x(0),y(0),z(0){};
Colour::Colour (float _x,float _y,float _z):x(_x),y(_y),z(_z){};
Colour Colour::operator+(const Colour &c){
    return Colour(x+c.x,y+c.y,z+c.z);
}
Colour Colour::operator*(const float &c){
    return Colour(x*c,y*c,z*c);
}
Colour Colour::operator*(const Colour &c){
    return Colour(x*c.x,y*c.y,z*c.z);
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

Plane::Plane(const Point &p,const Vector &v,const Colour &col,const Colour &emc):normalVector(v){
    center=p;
    colour=col;
    emissionColour=emc;
    normalVector.normalize();
}
bool Plane::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
    float a,b,c,d;
    float eps=1e-3;
    a=normalVector.x;
    b=normalVector.y;
    c=normalVector.z;
    d=-(center.x*a+center.y*b+center.z*c);
    float dist;
    dist=abs(a*origin.x+b*origin.y+c*origin.z+d)/sqrt(a*a+b*b+c*c);
    //cout << "dist " << dist << " "<<a << " " <<b << " " <<c << " " <<d<< endl;
    float cosAlpha=normalVector.dot(direction);
    if(cosAlpha<0){
        cosAlpha=-cosAlpha;
    }
    t0=dist/cosAlpha;
    Vector cop=direction;
    cop.setLength(t0);
    Point inter=translate(origin,cop);
    if(a*inter.x+b*inter.y+c*inter.z+d<=eps){
        return true;
    }
    return false;
}

Vector Plane::getNormalVector(const Point &hit){
    return normalVector;
}

Cylinder::Cylinder(const Point &p, const Vector &vh,const Vector &vp,const Colour &col,const Colour &em):heightVector(vh),baseVector(vp){
    center=p;
    colour=col;
    emissionColour=em;
}
Point Cylinder::closerPoint(const Vector &v1,const Vector &v2, const Point &origin){
    Point p1=translate(center,v1);
    p1=translate(p1,v2);
    float dist1=pointsDistance(p1,origin);
    Point p2=translate(center,v1);
    Vector v3=v2;
    v3=v3*-1;
    p2=translate(p1,v3);
    float dist2=pointsDistance(p1,origin);
    return dist1<dist2?p1:p2;
}
bool Cylinder::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
    t0=intersectBase(origin,direction);
    bool intBase=(t0!=100000);
    Vector planeNormalVec=direction.vectorProduct(heightVector);
    float A,B,C,D;
    A=planeNormalVec.x;
    B=planeNormalVec.y;
    C=planeNormalVec.z;
    D=-(A*origin.x+B*origin.y+C*origin.z);
    float dist=distanceFromPlane(center,A,B,C,D);
    if(dist>baseVector.getLength()&&!intBase){
        return false;
    }
    Vector axisPlane=planeNormalVec;
    axisPlane.setLength(dist);
    if(!onPlane(translate(center,axisPlane),A,B,C,D)){
        axisPlane=axisPlane*-1;
    }
    Vector v=planeNormalVec.vectorProduct(heightVector);
    Point lowerPoint=closerPoint(axisPlane,v,origin);
    Point upperPoint=translate(lowerPoint,heightVector);
    float tA=heightVector.x;
    float tB=heightVector.y;
    float tC=heightVector.z;
    float tD=-(heightVector.x*center.x+heightVector.y*center.y+heightVector.z*center.z);
    //cout<< "odl"<<distanceFromPlane(lowerPoint,tA,tB,tC,tD)<<' '<< distanceFromPlane(upperPoint,tA,tB,tC,tD)<<"\n";
//ok
    Vector vecLower(origin,lowerPoint);
    Vector vecUpper(origin,upperPoint);
    float ang1=acos(vecLower.dot(direction)/vecLower.getLength());
    float ang2=acos(vecUpper.dot(direction)/vecUpper.getLength());
    float ang3=acos(vecUpper.dot(vecLower)/vecUpper.getLength()/vecLower.getLength());
    if(abs(ang1+ang2-ang3)>1e-3&&!intBase){
        return false;
    }
    //ok
    float cosAlpha=vecLower.dot(direction)/vecLower.getLength();
    float alfa=acos(cosAlpha);
    float cosBeta=vecUpper.dot(direction)/vecUpper.getLength();
    float beta=acos(cosBeta);

    t0=min(t0,vecUpper.getLength()*vecLower.getLength()*sin(alfa+beta)/(vecLower.getLength()*sin(alfa)+vecUpper.getLength()*sin(beta)));
    return true;
}
float Cylinder::intersectBase(const Point &origin,const Vector &direction){
    float t1=100000,t2=100000,t=0;
    Plane base1(center,heightVector,colour,Colour());
    Plane base2(translate(center,heightVector),heightVector,colour,Colour());
    bool res1=base1.intersect(origin,direction,t1,t);
    bool res2=base2.intersect(origin,direction,t2,t);
    if(!res1&&!res2){
        return 100000;
    }
    float ret=min(t1,t2);
    Vector directionCopy=direction;
    directionCopy.setLength(ret);
    Point p=translate(origin,directionCopy);
    float dist=(p.x-center.x)*(p.x-center.x)+(p.y-center.y)*(p.y-center.y)+(p.z-center.z)*(p.z-center.z);
    if(dist>baseVector.getLength()){
        return 100000;
    }
    return ret;
}
Vector Cylinder::getNormalVector(const Point &hit){
    Vector vecOP(center,hit);
    float length=vecOP.dot(heightVector)/heightVector.getLength();
    Vector heightVecAxis=heightVector;
    heightVecAxis.setLength(length);
    Point axisPoint=translate(center,heightVecAxis);
    return Vector(axisPoint,hit);
}

Space::Space(int n):objectsCount(0){objects=new Object* [n];}
Space::~Space(){
    /*for(int i=0;i<objectsCount;i++){
        delete objects[i];
    }*/
    delete []objects;
}
void Space::addObject(Object *obj){
    objects[objectsCount]=obj;
    objectsCount++;
}
Object* Space::getObject(int i)const {
    return objects[i];
}
int Space::getSize()const {
    return objectsCount;
}
