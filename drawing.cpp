#include <iostream>
#include <fstream>
#include "drawing.h"
#include "geometry.h"
#include "bmp.h"
using namespace std;

Drawing::Drawing(int w, int h):width(w),height(h){};


float RaytracerDrawing::mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}
Colour RaytracerDrawing::trace(const Point &origin, const Vector &direction, const Space &space,int depth){
    float t0,t1,t=INFTY;
    int id=-1;
    for (int i=0;i<space.getSize();i++){
        t0=INFTY,t1=INFTY;
        if(space.getObject(i)->intersect(origin,direction,t0,t1)){
            if(t0<0){
                t0=t1;
            }
            if(t>t0){
                id=i;
            }
            t=min(t0,t);
        }
    }
    if(id==-1){
        return Colour(0,0,0);
    }
    Vector d=direction;
    d.setLength(t);
    Point hit=translate(origin,d);
    Vector normalVector=space.getObject(id)->getNormalVector(hit);
    float bias=1e-3;
    Object * cur = space.getObject(id);
    bool inside = false;
    if(direction.dot(normalVector)>0){
		normalVector=normalVector*(-1);
		inside = true;
    }
    if((cur->transparency>0||cur->reflection>0)&&depth<5){
		float facingratio = -direction.dot(normalVector);
		float effect = mix(pow(1 - facingratio, 3), 1, 0.1);
		Vector refldir = direction - normalVector * 2 * direction.dot(normalVector);
		refldir.normalize();
		Colour reflection = trace(translate(hit,normalVector * bias), refldir, space, depth + 1);

		Colour refraction;
		if (cur->transparency) {
			float ratio = 1.01, e = (inside) ? ratio : 1 / ratio;
			float cosi = -normalVector.dot(direction);
			float k = 1 - e * e * (1 - cosi * cosi);
			Vector refrdir = (direction * e) + (normalVector * (e *  cosi - sqrt(k)));
			refrdir.normalize();
			refraction = trace(translate(hit, normalVector * bias*(-1)), refrdir, space, depth + 1);
		}
		return (
			reflection * effect * cur->reflection +
			refraction * (1 - effect) * cur->transparency) * cur->colour;
	}else{
		int transmission;
		Colour colour;
		for(int i=0;i<space.getSize();i++){
			if(space.getObject(i)->emissionColour.x>0||space.getObject(i)->emissionColour.y>0||space.getObject(i)->emissionColour.z>0){
				Vector lightVector(translate(hit,normalVector*bias),space.getObject(i)->center);
				transmission=1;					
				lightVector.normalize();
				for(int j=0;j<space.getSize();j++){
					if(i!=j&&j!=id){
						if(space.getObject(j)->intersect(hit,lightVector,t0,t1)){
							if(t0<0) t0=t1;
							if(pointsDistance(hit,space.getObject(i)->center)>t0)
								transmission=0;
						}
					}
				}
				Colour c = space.getObject(id)->colour;
				colour=colour + c*space.getObject(i)->emissionColour*transmission*max(0.f,lightVector.dot(normalVector));
			}
		}
		return colour+cur->emissionColour;
	}
}
void RaytracerDrawing::render(const Space &space){
    float aspectRatio=(float)width/(float)height;
    float alpha=angle;
    Point s=translate(origin,startDirection);
    Vector a= basisVector;
    a.setLength(startDirection.getLength()*tan(alpha));
    Vector b=a.vectorProduct(startDirection);
    b.setLength(a.getLength()/aspectRatio);
    Point p;
    float w=width,h=height;
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            Vector c=a,d=b;
            c.setLength(((w-2*i)/w)*a.getLength());
            d.setLength(((h-2*j)/h)*b.getLength());
            p=translate(s,c);
            p=translate(p,d);
            Vector ray(origin,p);
            ray.normalize();
            canvas[i][j]=trace(origin,ray,space,0);
        }
    }
}
RaytracerDrawing::RaytracerDrawing(const int &w,
                 const int &h,
                 const Point &o,
                 const Vector &v,
                 const Vector &v2,
                 const float &ang):Drawing(w,h),origin(o),startDirection(v),basisVector(v2),picture(JiMP2::BMP(w,h)){
        canvas=new Colour *[w];
        for(int i=0;i<w;i++) canvas[i]=new Colour[h];
        out.open("test.bmp", std::ofstream::binary);
        angle=ang;
    }
void RaytracerDrawing::draw(const Space &space){
    render(space);
    int r,g,b;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            r=min(255.f,canvas[i][j].x*255);
            g=min(255.f,canvas[i][j].y*255);
            b=min(255.f,canvas[i][j].z*255);
            picture.setPixel(i,j,r,g,b);
        }
    }
    out<<picture;
}


