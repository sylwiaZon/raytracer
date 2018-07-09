#include <iostream>
#include "geometry.h"
#include "drawing.h"
#include "creation.h"
#include <fstream>
using namespace std;

//s-sphere
//l-light
//c-cone
//u-cube
//y-cylinder
//p-plain
//o-origin

void create (Space &space, fstream &file){
	char t;
	Object *obj;
	Point *origin;
	Vector *startDirection;
	Vector *basisVector;
	bool is=0;
	float line[20],ang, height, width;
	while(!file.eof()){
		file >> t;
		switch(t){
			case 'o':
				if(is==0){
					is=1;
					file >> line[1];
					file >> line[2];
					file >> line[3];
					file >> line[4];
					file >> line[5];
					file >> line[6];
					file >> line[7];
					file >> line[8];
					file >> line[9];
					file >> line[10];
					file >> line[11];
					file >> line[12];
					origin= new Point(line[1],line[2],line[3]);
					startDirection= new Vector(line[4],line[5],line[6]);
					basisVector= new Vector(line[7],line[8],line[9]);
					ang=line[10];
					height=line[11];
					width=line[12];
				}
				break;
			case 's': 
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				obj=new Sphere(Point (line[1],line[2],line[3]),line[4],Colour(line[5],line[6],line[7]),Colour(),line[8],line[9]);
				space.addObject(obj); 
				break;
			case 'c':
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				file >> line[10];
				file >> line[11];
				obj=new Cone(Point(line[1],line[2],line[3]),Vector(line[4],line[5],line[6]),M_PI/line[7],line[8],Colour (line[9],line[10],line[11]),Colour(),0,0);
				space.addObject(obj);  
				break;
			case 'u':
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				file >> line[10];
				file >> line[11];
				file >> line[12];
				file >> line[13];
				obj=new Cube(Point(line[1],line[2],line[3]),Vector(line[4],line[5],line[6]),Vector(line[7],line[8],line[9]),line[10],Colour(line[11], line[12],line[13]),Colour(),0,0);
				space.addObject(obj);  
				break;
			case 'y':
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				file >> line[10];
				file >> line[11];
				file >> line[12];
				obj=new Cylinder(Point(line[1],line[2],line[3]),Vector(line[4],line[5],line[6]),Vector(line[7],line[8],line[9]),Colour (line[10],line[11],line[12]),Colour(),0,0);
				space.addObject(obj);  
				break;
			case 'p':
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				obj=new Plane(Point(line[1],line[2],line[3]),Vector(line[4],line[5],line[6]),Colour(line[7],line[8],line[9]),Colour(),0,0);
				space.addObject(obj);  
				break;
			case 'l':
				file >> line[1];
				file >> line[2];
				file >> line[3];
				file >> line[4];
				file >> line[5];
				file >> line[6];
				file >> line[7];
				file >> line[8];
				file >> line[9];
				file >> line[10];
				obj=new Sphere(Point (line[1],line[2],line[3]),line[4],Colour(line[5],line[6],line[7]),Colour(line[8],line[9],line[10]),0,0);
				space.addObject(obj);  
				break;
			default: 
				cout << "undefined command";
				is=0;
				break;
		}
		t='0';
	}
	RaytracerDrawing drawing(height,width,*origin,*startDirection,*basisVector, ang);
	drawing.draw(space);
}
