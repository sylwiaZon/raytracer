#include <iostream>
#include "drawing.cpp"
using namespace std;

int main(){
    Point origin(10,0,0);
    Vector startDirection(-3,0,0);
    Vector basisVector(0,0,1);
    Point center(-3,0,-2);
    Sphere sp(center,1,Colour(0.5,0,0),Colour());
    Sphere sp1(Point(-1,2,0),1,Colour(0.2,0.6,0),Colour());
    Sphere sp2(Point(-100,1,0),50,Colour(0.2,0.6,0.2),Colour());
    Sphere light(Point(100,-40,-5),2,Colour(0.5,0,0),Colour(3,3,3));
    Plane pl(Point(-10,-10,0),Vector(10,1,1),Colour(0,0.8,0.7),Colour());
    Cylinder cyl(Point(-3,0,0),Vector(1,1,1),Vector(1,-2,1),Colour (0,1,0),Colour());
    Space space(4);
    space.addObject(&pl);
    space.addObject(&light);
    space.addObject(&sp);
    space.addObject(&cyl);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
