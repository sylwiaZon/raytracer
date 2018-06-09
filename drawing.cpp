#include <iostream>
#include "geometry.cpp"
using namespace std;

class Drawing{
    int width, height;
public:
    Drawing(int w, int h):width(w),height(h){};
    virtual void draw(const Space &space)=0;
};

class RaytracerDrawing:Drawing{
    Point origin;
    void trace(const Vector &direction){}
    void render(){
        cout << "I'm rendering";
    }
public:
    RaytracerDrawing(int w, int h,const Point &o):Drawing(w,h),origin(o){};
    void draw(const Space &space){
        render();
    }
};
