#include <iostream>
#include "drawing.cpp"
using namespace std;

int main(){
    Point origin(10,0,0);
    Vector startDirection(-3,0,0);
    Vector basisVector(0,0,1);
    Point center(-3,0,-2);
    Sphere sp(Point(-1500,-100,0),1000,Colour(0.5,0,0),Colour(),0,0);
    Sphere sp1(Point(-4,2,-2),1,Colour(0.2,0.6,0),Colour(),0,0);
    Sphere sp2(Point(-10,1,0),2,Colour(0.8,0.8,0.8),Colour(),0,1);
    Sphere sp3(Point(-5,-2,2),1,Colour(0.6,0.2,0.2),Colour(),0,0);
    Sphere light(Point(100,-30,0),2,Colour(1,1,1),Colour(3,3,3),0,0);
    //Sphere light(Point(-3,-3,0),1,Colour(0.6,0.2,0.2),Colour(2,2,2),0,0);

    Plane pl(Point(0,3,0),Vector(0,1,0),Colour(0.4,0.8,0.2),Colour(),0,0);
    Plane pl2(Point(0,0,20),Vector(1,0,-1),Colour(0.7,0.3,0),Colour(),0,0);
    Plane pl3(Point(0,0,-20),Vector(1,0,1),Colour(0.4,0.2,0.3),Colour(),0,0);

    //Cylinder cyl(Point(-10,0,0),Vector(0,2,2),Vector(1,0,0),Colour (0,1,0),Colour());
    //Cone con(Point(-5,0,0),Vector(1,2,1),M_PI/6,4,Colour (0,1,0),Colour(),0,0);
    //Cube cub(Point(-10,0,0),Vector(1,0,1),Vector(0,-1,0),Colour(0.2,0.6,0.2),Colour(),0,0);
    Space space(6);
    space.addObject(&pl);
    space.addObject(&pl2);
    space.addObject(&pl3);
    space.addObject(&light);
    //space.addObject(&sp1);
    space.addObject(&sp2);
    //space.addObject(&con);
	//space.addObject(&cub);
    RaytracerDrawing drawing(500,500,origin,startDirection,basisVector);
    drawing.draw(space);
}
