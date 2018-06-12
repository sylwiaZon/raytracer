#include <iostream>
#include "drawing.cpp"
using namespace std;

int main(){
    Point origin(10,0,0);
    Vector startDirection(-3,0,0);
    Vector basisVector(0,0,1);
    Point center(-3,0,-2);
    Sphere sp(center,1,Colour(0.5,0,0),Colour());
    Sphere sp1(Point(-3,2,0),1,Colour(0.2,0.6,0),Colour());
    Sphere sp2(Point(-100,1,0),50,Colour(0.2,0.6,0.2),Colour());
    Sphere light(Point(500,-5,-2),2,Colour(0.5,0,0),Colour(3,3,3));
    Plane pl(Point(-1000,10000,10000),Vector(Point(-1000,10000,10000),origin),Colour(0.9,0.8,0.7),Colour());
    Space space(4);
    space.addObject(&sp);
    space.addObject(&light);
    space.addObject(&sp1);
    space.addObject(&pl);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
