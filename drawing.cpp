#include <iostream>
#include <fstream>
#include "geometry.cpp"
#include "bmp.cpp"
using namespace std;

const float INFTY=100000;


class Drawing{
protected:
    int width, height;
public:
    Drawing(int w, int h):width(w),height(h){};
    virtual void draw(const Space &space)=0;
};

class RaytracerDrawing:Drawing{
    JiMP2::BMP picture;
    ofstream out;
    Point origin;
    Vector startDirection;
    Colour **canvas;
    Vector basisVector;
    Colour trace(const Point &origin, const Vector &direction, const Space &space){
        float t0,t1,t=INFTY;
        int id=-1;
        for (int i=0;i<space.getSize();i++){
            t0=INFTY,t1=INFTY;
            if(space.getObject(i)->intersect(origin,direction,t0,t1)){
                //cout << t0 << " " <<t1 << " " << direction.x << " "<< direction.y<< " "<<direction.z <<endl;
                //Sleep(1000);
                    //cout <<t0 << " " <<t1<<endl;
                if(t0<0){
                    t0=t1;
                }
                if(t>t0){
                    id=i;
                }
                t=min(t0,t);
            }
        }
        //cout << t << " ";
        if(id==-1){
            return Colour(0,0,0);
        }
        Vector d=direction;
        d.setLength(t);
        Point hit=translate(origin,d);
        Vector normalVector=space.getObject(id)->getNormalVector(hit);
        //cout << normalVector.x << " "<< normalVector.y << " "<< normalVector.z << endl;
        int transmission;
        float bias=1e-4;
        Colour colour;
        for(int i=0;i<space.getSize();i++){
            if(space.getObject(i)->emissionColour.x>0||space.getObject(i)->emissionColour.y>0||space.getObject(i)->emissionColour.z>0){
                Vector lightVector(hit,space.getObject(i)->center);
                lightVector.normalize();
                transmission=1;

                for(int j=0;j<space.getSize();j++){
                    if(i!=j&&j!=id){
                        if(space.getObject(j)->intersect(hit,lightVector,t0,t1)){
                            transmission=0;
                        }
                    }
                }
               //out<<colour.x<<" "<<colour.y<<" "<<colour.z<<" stary\n";
                //cout<<transmission<<" "<<lightVector.dot(normalVector)<<"\n";
                //cout<<lightVector.dot(normalVector)<<"\n";
                Colour c = space.getObject(id)->colour;
                //cout<<c.x<<" "<<c.y<<" "<<c.z<<"\n";
                colour=colour + c*space.getObject(i)->emissionColour*transmission*max(0.f,lightVector.dot(normalVector));
                //cout<<colour.x<<" "<<colour.y<<" "<<colour.z<<"\n";
            }
        }
        return colour;
    }
    void render(const Space &space){
        float aspectRatio=(float)width/(float)height;
        float alpha=M_PI*15/180;
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
                //cout << ((w-2*i)/w)*a.getLenght() <<" " <<c.getLenght()<< endl;
                d.setLength(((h-2*j)/h)*b.getLength());
                p=translate(s,c);
                p=translate(p,d);
                //cout << p.x << " " << p.y << " " <<p.z <<endl;
                Vector ray(origin,p);
                //cout << ray.x << ray.y << ray.z <<" ";
                ray.normalize();
                //cout << ray.x << ray.y << ray.z <<endl;
                //cout << i << " " << j << " " <<ray.x <<" "<<ray.y << " " <<ray.z <<endl;
                canvas[i][j]=trace(origin,ray,space);
            }
        }
    }
public:
    RaytracerDrawing(const int &w,
                     const int &h,
                     const Point &o,
                     const Vector &v,
                     const Vector &v2):Drawing(w,h),origin(o),startDirection(v),basisVector(v2),picture(JiMP2::BMP(w,h)){
            canvas=new Colour *[w];
            for(int i=0;i<w;i++) canvas[i]=new Colour[h];
            out.open("test.bmp", std::ofstream::binary);
        }
    void draw(const Space &space){
        render(space);
        int r,g,b;
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(canvas[i][j].x>0||canvas[i][j].y>0||canvas[i][j].z>0){
                    //cout << i << " " << j << " " << canvas[i][j].x << " " <<canvas[i][j].y << " " <<canvas[i][j].z << endl;
                    //cout <<min(255.f,canvas[i][j].x*255)<<min(255.f,canvas[i][j].y*255)<<min(255.f,canvas[i][j].z*255)<<endl;
                }
                r=min(255.f,canvas[i][j].x*255);
                g=min(255.f,canvas[i][j].y*255);
                b=min(255.f,canvas[i][j].z*255);

                //cout << i<<" "<<j<<" "<< r <<" " << g << " " <<b << endl;

                picture.setPixel(i,j,r,g,b);
            }
        }
        out<<picture;
    }

};
