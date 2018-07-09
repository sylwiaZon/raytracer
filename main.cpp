#include <fstream>
#include "geometry.h"
#include "drawing.h"
#include "creation.h"
using namespace std;


int main(int argc, char ** argv){
	Space space(100);
	if(argc>1){
		fstream file;
		file.open(argv[1], std::ios::in);
		cout<<"before good";
     	if (file.good())
        {
        	cout<<"after good";
        	create(space,file);
        	file.close();
       	}
	}
}
