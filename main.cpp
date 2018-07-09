#include <iostream>
#include "geometry.h"
#include "drawing.h"
using namespace std;

int main(){
    Point origin(10,0,0);
    Vector startDirection(-3,0,0);
    Vector basisVector(0,0,1);
    Sphere spback(Point(0,0,0),1000,Colour(1,1,1),Colour(),0,0);
    Sphere sp(Point (-3,0,-2),1,Colour(0.5,0,0),Colour(),0,0);
    Sphere sp1(Point(-4,2,-2),1,Colour(0.2,0.5,0.8),Colour(),0,0.5);
    Sphere sp2(Point(-7,1,2),2,Colour(0.2,0.6,0.2),Colour(),0,0);
    Sphere sp3(Point(-3,-2,2),0.5,Colour(1,0,0),Colour(),0,0);
    Sphere light(Point(100,-80,20),2,Colour(1,1,1),Colour(1,1,1),0,0);
    Plane pl(Point(0,4,0),Vector(0,-1,0),Colour(0,1,0),Colour(),0,0);
    Plane p2(Point(-100,0,0),Vector(2,0,0),Colour(0,0,100),Colour(),0,0);
    Cylinder cyl(Point(-11,-1.3,-2),Vector(3,0.01,-2),Vector(-1,0,0),Colour (1,0,1),Colour(),0,0);
    Cylinder cyl2(Point(-10,0,-3),Vector(0,3,0),Vector(1,0,0),Colour (1,0,1),Colour(),0,0);
    Cone con(Point(-2.5,-2.8,0.8),Vector(-1,2,3),M_PI/16,1,Colour (0,1,0),Colour(),0,0);
    Cone con2(Point(-2.5,-2.8,3.1),Vector(-1,2,-3),M_PI/16,1,Colour (0,1,0),Colour(),0,0);
    Cube cub(Point(-20,3,-1),Vector(1,0,1),Vector(0,-1,0),2,Colour(0.98, 0.45, 0.43),Colour(),0,0);
    Sphere sp4(Point(-20,0,-1),1,Colour(0.5,0,0.2),Colour(),0,0);
    Space space(15);
    space.addObject(&spback);    
    space.addObject(&light);
    space.addObject(&pl);
    space.addObject(&p2);
    space.addObject(&sp3);
    space.addObject(&sp1);
    space.addObject(&sp2);
    space.addObject(&cyl);
    space.addObject(&cyl2);
	space.addObject(&con);
	space.addObject(&con2);
	space.addObject(&cub);
	space.addObject(&sp4);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
