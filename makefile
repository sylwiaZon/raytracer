__start__: a.out
	./a.out scene.txt 

a.out: main.o geometry.o bmp.o drawing.o creation.o
	g++ main.o geometry.o bmp.o drawing.o creation.o 
	
main.o: main.cpp 
	g++ -c main.cpp 
	
geometry.o: geometry.cpp geometry.h
	g++ -c geometry.cpp geometry.h
	
drawing.o: drawing.cpp drawing.h
	g++ -c drawing.cpp drawing.h
	
creation.o: creation.cpp creation.h
	g++ -c creation.cpp creation.h
