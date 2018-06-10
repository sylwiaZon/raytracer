#include <iostream>
#include "drawing.cpp"
using namespace std;

int main(){
    Point origin(3,0,0);
    Vector startDirection(-3,0,0);
    Vector basisVector(0,0,1);
    Point center(-3,0,0);
    Sphere sp(center,1,Colour(0.5,0,0),Colour());
    Sphere light(Point(-1,5,0),2,Colour(0.5,0,0),Colour(3,3,3));
    Space space(2);
    space.addObject(sp);
    space.addObject(light);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
