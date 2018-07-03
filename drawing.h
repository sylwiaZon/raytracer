#ifndef __DRAWING_H
#define __DRAWING_H

#include <iostream>
#include <fstream>
#include "geometry.h"
#include "bmp.h"
using namespace std;

const float INFTY=100000;


class Drawing{
protected:
    int width, height;
public:
    Drawing(int w, int h);
    virtual void draw(const Space &space);
};

class RaytracerDrawing:Drawing{
    JiMP2::BMP picture;
    ofstream out;
    Point origin;
    Vector startDirection;
    Colour **canvas;
    Vector basisVector;
    float mix(const float &a, const float &b, const float &mix);
    Colour trace(const Point &origin, const Vector &direction, const Space &space,int depth);
    void render(const Space &space);
public:
    RaytracerDrawing(const int &w,
                     const int &h,
                     const Point &o,
                     const Vector &v,
                     const Vector &v2);
    void draw(const Space &space);
};

#endif
