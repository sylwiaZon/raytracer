#include <fstream>
#include "geometry.h"
#include "drawing.h"
#include "creation.h"
using namespace std;



int main(int argc, char ** argv){
	Space space(100);
	if(argc>1){
		fstream file;
		file.open("scene.txt", std::ios::in);
     	if (file.good())
        {
        	create(space,file);
        	file.close();
       	}
	}
}
