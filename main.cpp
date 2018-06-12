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
    Space space(4);
    space.addObject(sp);
    space.addObject(light);
    space.addObject(sp1);
    space.addObject(sp2);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
