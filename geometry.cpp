#include <iostream>
#include <cmath>
#include "geometry.h"
using namespace std;

Point::Point():x(0.0),y(0.0),z(0.0){};
Point::Point(float _x, float _y, float _z):x(_x),y(_y),z(_z){};

Vector::Vector():x(0),y(0),z(0){};
Vector::Vector(float _x, float _y, float _z):x(_x),y(_y),z(_z){};
Vector::Vector(Point start, Point ending):x(ending.x-start.x),y(ending.y-start.y),z(ending.z-start.z){};
Vector Vector::operator+( const Vector &v) const{
    return Vector(x+v.x,y+v.y,z+v.z);
}
Vector Vector::operator-(const Vector &v) const{
    return Vector(x-v.x,y-v.y,z-v.z);
}
Vector Vector::operator*(const float &f) const{
    return Vector(x*f,y*f,z*f);
}
float Vector::dot(const Vector &v) const{
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
float Vector::getLength() const{
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
    if(abs(p.x*A+p.y*B+p.z*C+D)<eps){
        return true;
    }
    return false;
}
float pointsDistance(const Point &p1,const Point &p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}

float pointBetween(const Point &p,const Point &s,const Point &e){
	if(min(s.x,e.x)<=p.x&&p.x<=max(s.x,e.x)&&
		min(s.y,e.y)<=p.y&&p.y<=max(s.y,e.y)&&
		min(s.z,e.z)<=p.z&&p.z<=max(s.z,e.z))
		return true;
	return false;
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
Sphere::Sphere(const Point &c, const float &rad, const Colour &col,const Colour &emc,const float & tran,const float & relf):radius(rad){
    colour = col;
    center=c;
    emissionColour=emc;
    transparency = tran;
    reflection = relf;
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
    Vector v = Vector (center,hit);
    v.normalize();
    return v;
}

Plane::Plane(const Point &p,const Vector &v,const Colour &col,const Colour &emc,const float & tran,const float & relf):normalVector(v){
    center=p;
    colour=col;
    emissionColour=emc;
    normalVector.normalize();
    transparency = tran;
    reflection = relf;
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
    if(onPlane(inter,a,b,c,d)){
        return true;
    }
    return false;
}

Vector Plane::getNormalVector(const Point &hit){
    return normalVector;
}

Cylinder::Cylinder(const Point &p, const Vector &vh,const Vector &vp,const Colour &col,const Colour &em,const float & tran,const float & relf):heightVector(vh),baseVector(vp){
    center=p;
    colour=col;
    emissionColour=em;
    transparency = tran;
    reflection = relf;
}
Point Cylinder::closerPoint(const Vector &v1,const Vector &v2, const Point &origin){
    Point p1=translate(center,v1);
    p1=translate(p1,v2);
    float dist1=pointsDistance(p1,origin);
    Point p2=translate(center,v1);
    Vector v3=v2;
    v3=v3*-1;
    p2=translate(translate(center,v1),v3);
    float dist2=pointsDistance(p2,origin);
    return abs(dist1)<abs(dist2)?p1:p2;
}
bool Cylinder::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
    t0=min(intersectBase(origin,direction,translate(center,heightVector)),intersectBase(origin,direction,center));
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
    Vector v=axisPlane.vectorProduct(heightVector);
    v.setLength(sqrt((baseVector.getLength()*baseVector.getLength())-(axisPlane.getLength()*axisPlane.getLength())));
    Point lowerPoint=closerPoint(axisPlane,v,origin);
    Point upperPoint=translate(lowerPoint,heightVector);
    float tA=heightVector.x;
    float tB=heightVector.y;
    float tC=heightVector.z;
    float tD=-(heightVector.x*center.x+heightVector.y*center.y+heightVector.z*center.z);
    Vector vecLower(origin,lowerPoint);
    Vector vecUpper(origin,upperPoint);
    float ang1=acos(vecLower.dot(direction)/vecLower.getLength());
    float ang2=acos(vecUpper.dot(direction)/vecUpper.getLength());
    float ang3=acos(vecUpper.dot(vecLower)/vecUpper.getLength()/vecLower.getLength());
    bool angCond = (abs(ang1+ang2-ang3)<=1e-3);
    if(!angCond&&!intBase){
        return false;
    }

    float cosAlpha=vecLower.dot(direction)/vecLower.getLength();
    float alfa=acos(cosAlpha);
    float cosBeta=vecUpper.dot(direction)/vecUpper.getLength();
    float beta=acos(cosBeta);
    if(angCond){
        t0=(t0,(heightVector.y*(origin.x-lowerPoint.x)-heightVector.x*(origin.y)+heightVector.x*lowerPoint.y)/(heightVector.x*direction.y-heightVector.y*direction.x));
    }
    float t7=vecUpper.getLength()*vecLower.getLength()*sin(alfa+beta)/(vecLower.getLength()*sin(alfa)+vecUpper.getLength()*sin(beta));
    Vector copyDirection=direction;
    copyDirection.setLength(t0);
    Point cop=translate(origin,copyDirection);
    Vector test = heightVector.vectorProduct(Vector(lowerPoint,cop));
    float a1=pointsDistance(cop,upperPoint);
    float a2=pointsDistance(cop,lowerPoint);
    float a3=pointsDistance(upperPoint,lowerPoint);
    return true;
}
float Cylinder::intersectBase(const Point &origin,const Vector &direction,const Point &cent){
    float t1=100000,t=0;
    Plane base1(cent,heightVector*-1,colour,Colour(),0,0);
    bool res1=base1.intersect(origin,direction,t1,t);
    if(!res1){
        return 100000;
    }
    Vector copyDirection=direction;
    copyDirection.setLength(t1);
    Point hit=translate(origin,copyDirection);
    float dist=pointsDistance(hit,cent);
    if(dist>baseVector.getLength()){
        return 100000;
    }
    return t1;
}
Vector Cylinder::getNormalVector(const Point &hit){
    Vector vecOP(center,hit);
    float length=vecOP.dot(heightVector)/heightVector.getLength();
    Vector heightVecAxis=heightVector;
    heightVecAxis.setLength(length);
    Point axisPoint=translate(center,heightVecAxis);
    Vector ret;
    if(abs(heightVector.getLength()-heightVecAxis.getLength())>1e-3){
        ret = Vector(axisPoint,hit);
    }else{
        ret = heightVector;
    }
    ret.normalize();
    return ret;
}

Cone::Cone(const Point &p, const Vector &vh, const float & a, const float & h,const Colour &col,const Colour &em,const float & tran,const float & relf):heightVector(vh), alfa(a),height(h){
	center = p;
    colour=col;
    emissionColour=em;
    heightVector.normalize();
    transparency = tran;
    reflection = relf;
}

float Cone::intersectBase(const Point &origin,const Vector &direction){
	Vector ch = heightVector;
	ch.setLength(height);
	Point basecenter = translate(center,ch);
	Plane base = Plane(basecenter,heightVector,Colour(),Colour(),0,0);
	float t = 10000,t2=10000;
	if(base.intersect(origin,direction,t,t2)){
		Vector hv = direction;
		hv.setLength(t);
		Point hit = translate(origin,hv);
		if(pointsDistance(hit,basecenter)<tan(alfa)*height){
				return t;
		}else
			return 10000;
	}
	return 10000;
}

bool Cone::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
	float tb = intersectBase(origin,direction);
	bool intbase = (tb!=10000);
	float cosa = cos(alfa);
	Vector CO = Vector(center,origin);
	float a = direction.dot(heightVector)*direction.dot(heightVector)-cosa*cosa;
	float b = 2*(direction.dot(heightVector)*CO.dot(heightVector)-direction.dot(CO)*cosa*cosa);
	float c = (CO.dot(heightVector)*CO.dot(heightVector)-CO.dot(CO)*cosa*cosa);
	float dlt = b*b-4*a*c;
	bool intsurf = (dlt>=0);
	if(dlt<0&&!intbase) return false;
	else if(dlt==0){
		t0=t1=-b/(2*a);
	}else if(dlt>0){
		t0 = (-b-sqrt(dlt))/(2*a);
		t1 = (-b+sqrt(dlt))/(2*a);
		if(t1<t0) swap(t0,t1);
	}

	Vector vc = direction;
	vc.setLength(t0<0?min(tb,t1):t0);
	Point hit = translate(origin,vc);
	float h = Vector(center,hit).getLength()*cos(alfa);
	if(h>height&&t0>=0){
		t0 = t1;
		vc.setLength(t0);
		hit = translate(origin,vc);
		h = Vector(center,hit).getLength()*cos(alfa);
	}
	if(!intbase&&h>height)
		return false;
	if(!intbase&&Vector(center,hit).dot(heightVector)<0)
		return false;
	if(intbase)
	if(intbase&&!intsurf){
		t0=tb;
	}else if(intbase&&intsurf&&tb<t0){
		t1=t0;
		t0=tb;
	}else if(intbase&&intsurf&&tb<t1){
		t1=tb;
	}
	return true;
}
Vector Cone::getNormalVector(const Point &hit){
	Vector hv = heightVector;
	hv.setLength(height);
	Point basecenter=translate(center,hv);
	float A=hv.x;
	float B=hv.y;
	float C=hv.z;
	float D=-hv.x*basecenter.x-hv.y*basecenter.y-hv.z*basecenter.z;
	if(onPlane(hit,A,B,C,D)){
		return heightVector;
	}
	Vector CH = Vector(center,hit);
	float h = CH.getLength()/cos(alfa);
	Vector cv = heightVector;
	cv.setLength(h);
	Point p = translate(center, cv);
	Vector n = Vector(p,hit);
	n.normalize();
	return n;
}


Cube::Cube(const Point &p, const Vector &_a,const Vector &_b,float h,const Colour &col,const Colour &em,const float & tran,const float & relf):a(_a),b(_b),height(h){
	c = a.vectorProduct(b);
	a.normalize();
	b.normalize();
	c.normalize();
	center = p;
	colour = col;
	emissionColour = em;
    transparency = tran;
    reflection = relf;
}

float Cube::intersectOnPlane(const Point &origin,const Vector &direction, Vector a, Vector b, Vector c){
	a.setLength(height);
	b.setLength(height);
	c.setLength(height);
	float aA,aB,aC,aD1,aD2;
	Point candA = translate(center,a);
	aA=a.x;aB=a.y;aC=b.y;
	aD1=-a.x*center.x-a.y*center.y-a.z*center.z;
	aD2=-a.x*candA.x-a.y*candA.y-a.z*candA.z;
	if(distanceFromPlane(origin,aA,aB,aC,aD1)<distanceFromPlane(origin,aA,aB,aC,aD2)) candA=center;
	Plane pl = Plane(candA,a,Colour(),Colour(),0,0);
	float t0,t1;
	bool intct = pl.intersect(origin,direction,t0,t1);
	if(!intct) return 10000;
	Vector pointVector = direction;
	pointVector.setLength(t0);
	Point S = translate(origin,pointVector);
	Point p = translate(candA,b);
	p = translate(p,c);
	Vector cS(candA,S);
	float d1 = cS.vectorProduct(b).getLength()/b.getLength();
	float d2 = cS.vectorProduct(c).getLength()/c.getLength();
	if(d1<c.getLength()&&d2<b.getLength()&&cS.dot(b)>0&&cS.dot(c)>0) return t0;
	else return 10000;
}

bool Cube::intersect(const Point &origin,const Vector &direction,float &t0, float &t1){
	float ta = intersectOnPlane(origin,direction,a,b,c);
	float tb = intersectOnPlane(origin,direction,b,a,c);
	float tc = intersectOnPlane(origin,direction,c,a,b);
	t0=min(ta,min(tb,tc));
	if(t0!=10000) return true;
	return false;
}
Vector Cube::getNormalVector(const Point &hit){
	Vector aa = a;
	aa.setLength(height);
	Point candA = translate(center,aa);
	float A = aa.x,B=aa.y,C=aa.z;
	float D1=-aa.x*center.x-aa.y*center.y-aa.z*center.z;
	float D2=-aa.x*candA.x-aa.y*candA.y-aa.z*candA.z;
	if(onPlane(hit,A,B,C,D1)||onPlane(hit,A,B,C,D2)) return a;
	Vector bb = b;
	bb.setLength(height);
	Point candB = translate(center,bb);
	A = bb.x,B=bb.y,C=bb.z;
	D1=-bb.x*center.x-bb.y*center.y-bb.z*center.z;
	D2=-bb.x*candB.x-bb.y*candB.y-bb.z*candB.z;
	if(onPlane(hit,A,B,C,D1)||onPlane(hit,A,B,C,D2)) return b;
	return c;
}
Space::Space(int n):objectsCount(0){objects=new Object* [n];}
Space::~Space(){
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
