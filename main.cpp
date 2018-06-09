#include <iostream>
#include "drawing.cpp"
using namespace std;

int main(){
    Point a;
    Point b(4,5,6);
    cout << a.x << " " << a.y << " " << a.z << endl ;
    cout << b.x << " " << b.y << " " << b.z << endl ;
    Vector c;
    Vector d(a,b);
    Vector e(3,5,8);

    cout << c.x << " "<< c.y << " " << c.z << endl;
    cout << d.x << " " << d.y << " " << d.z << endl ;
    cout << e.x << " " << e.y << " " << e.z << endl ;
    e.norm();
    Vector p=e;
    cout << p.x << " " << p.y << " " << p.z << endl ;

    Space space(5);
    space.addObject(Sphere (b,5,Colour()));
    RaytracerDrawing f(500,500,a);
    f.draw(space);
}
