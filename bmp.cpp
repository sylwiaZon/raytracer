#include "bmp.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <math.h>
#include <cmath>

using namespace std;

namespace JiMP2 {

BMP::BMP(uint16_t width, uint16_t height) :
		bitmapCoreHeader(width, height) {

	assert(IS_LITTLE_ENDIAN);
	assert(width > 0);
	assert(height > 0);

	const unsigned int rowSize = ((bitmapCoreHeader.bitsPerPixel * width + 31)
			/ 32) * 4;
	const unsigned int imgSize = rowSize * height;

	bmpFileHeader.size = 14 + bitmapCoreHeader.size + imgSize;
	bmpFileHeader.dataOffset = 14 + bitmapCoreHeader.size;

	pixelData = new unsigned char[imgSize];
	std::memset(pixelData, 255, imgSize);
}

BMP::~BMP() {
	delete[] pixelData;
}

void BMP::setPixel(uint16_t x, uint16_t y, unsigned char r, unsigned char g,
		unsigned char b) {
	assert(bitmapCoreHeader.bitsPerPixel == 24);

	const size_t rowSize = ((bitmapCoreHeader.bitsPerPixel
			* bitmapCoreHeader.bmpWidth + 31) / 32) * 4;
	const size_t offset = rowSize * (bitmapCoreHeader.bmpHeight - y)
			+ x * (bitmapCoreHeader.bitsPerPixel / 8);

	pixelData[offset + 0] = b;
	pixelData[offset + 1] = g;
	pixelData[offset + 2] = r;
}

void BMP::drawLine (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, unsigned char r, unsigned char g,unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    if(x1==x2){
        for(double i=min(y1,y2);i<=max(y1,y2);i+=0.00001){
            this->setPixel(x1, i, r,g,b);
        }
    }else{
        double a,c,y;
        a=(double)(y1-y2)/(double)(x1-x2);
        c=(double)y1-a*(double)x1;
        for(double i=min(x1,x2);i<=max(x1,x2);i+=0.00001){
            y=a*i+c;
            if(i<w&&y<h){
                this->setPixel(i, y, r,g,b);
            }
        }
    }
}


void BMP::drawRectangle(uint16_t xP, uint16_t yP, double width, double height, unsigned char r, unsigned char g, unsigned char b){
	int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
	for(int i=0;i<width;i++){
        if((i+xP)<w&&(yP)<h){
            this->setPixel(i+xP, yP, r,g,b);
        }
        if((i+xP)<w&&(yP+height)<h){
            this->setPixel(i+xP, yP+height, r,g,b);
        }
	}
	for(int i=0;i<height;i++){
        if(xP<w&&(yP+i)<h){
            this->setPixel(xP, yP+i, r,g,b);
        }
        if((xP+width-1)<w&&(yP+i)<h){
            this->setPixel(xP+width-1, yP+i, r,g,b);
        }
	}
}

void BMP::drawCircle(uint16_t x, uint16_t y, uint16_t R, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    double i=0;
    while(i<2*M_PI){
        if((x+int(sin(i)*R))<w && (y-int(cos(i)*(R)))<h){
            this->setPixel(x+int(sin(i)*(R)), y-int(cos(i)*(R)), r,g,b);
        }
		i+=0.001;
    }
}


void BMP::drawWheel(uint16_t x, uint16_t y, uint16_t R, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    for(int j=R;j>=0;j--){
        double i=0;
        while(i<2*M_PI){
            if((x+int(sin(i)*(R-j)))<w && (y-int(cos(i)*(R-j)))<h){
                this->setPixel(x+int(sin(i)*(R-j)), y-int(cos(i)*(R-j)), r,g,b);
            }
            i+=0.001;
        }
    }
}


void BMP::drawPartOfCircle(uint16_t x, uint16_t y, uint16_t R, double beg, double en, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    double i=0;
    while(i<2*M_PI){
        if(i*180/M_PI>=beg&&i*180/M_PI<=en){
                if((x+int(sin(i)*(R)))<w && (y-int(cos(i)*(R)))<h){
                    this->setPixel(x+int(sin(i)*(R)), y-int(cos(i)*(R)), r,g,b);
                }
            }
		i+=0.001;
    }
}

void BMP::drawPartOfWheel(uint16_t x, uint16_t y, uint16_t R, double beg, double en, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    for(int j=R;j>=0;j--){
        double i=0;
        while(i<2*M_PI){
            if(i*180/M_PI>=beg&&i*180/M_PI<=en){
                if((x+int(sin(i)*(R-j)))<w && (y-int(cos(i)*(R-j)))<h){
                    this->setPixel(x+int(sin(i)*(R-j)), y-int(cos(i)*(R-j)), r,g,b);
                }
            }
            i+=0.001;
        }
    }
}

void BMP::drawElipse(uint16_t x, uint16_t y, uint16_t Rx, uint16_t Ry, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    double i=0;
    while(i<2*M_PI){
        if((x+int(sin(i)*Rx))<w && (y-int(cos(i)*(Ry)))<h){
            this->setPixel(x+int(sin(i)*(Rx)), y-int(cos(i)*(Ry)), r,g,b);
        }
		i+=0.001;
    }
}

void BMP::drawPolygon(uint16_t x, uint16_t y, uint16_t n, uint16_t R, unsigned char r, unsigned char g, unsigned char b){
    int h=this->bitmapCoreHeader.bmpHeight;
    int w=this->bitmapCoreHeader.bmpWidth;
    int *tab=new int [n*2];
    for(int i=0;i<n;i++){
        tab[i*2]=int(sin(2*M_PI/5*i)*R)+x;
        tab[i*2+1]=int(cos(2*M_PI/5*i)*R)+y;
    }
    for(int i=0;i<n-1;i++){
        this->drawLine(tab[i*2],tab[i*2+1],tab[(i+1)*2],tab[(i+1)*2+1],r,g,b);
    }
    this->drawLine(tab[n*2-2],tab[n*2-1],tab[0],tab[1],r,g,b);
}


std::ostream& operator<<(std::ostream& os, const BMP& bmp) {
	os.write(bmp.bmpFileHeader.id, sizeof(bmp.bmpFileHeader.id));
	os.write((const char*) &bmp.bmpFileHeader.size,
			sizeof(bmp.bmpFileHeader.size));
	os.write(bmp.bmpFileHeader.reserved, sizeof(bmp.bmpFileHeader.reserved));
	os.write((const char*) &bmp.bmpFileHeader.dataOffset,
			sizeof(bmp.bmpFileHeader.dataOffset));

	os.write((const char*) &bmp.bitmapCoreHeader.size,
			sizeof(bmp.bitmapCoreHeader.size));
	os.write((const char*) &bmp.bitmapCoreHeader.bmpWidth,
			sizeof(bmp.bitmapCoreHeader.bmpWidth));
	os.write((const char*) &bmp.bitmapCoreHeader.bmpHeight,
			sizeof(bmp.bitmapCoreHeader.bmpHeight));
	os.write((const char*) &bmp.bitmapCoreHeader.colorPlanes,
			sizeof(bmp.bitmapCoreHeader.colorPlanes));
	os.write((const char*) &bmp.bitmapCoreHeader.bitsPerPixel,
			sizeof(bmp.bitmapCoreHeader.bitsPerPixel));

	const unsigned int rowSize = ((bmp.bitmapCoreHeader.bitsPerPixel
			* bmp.bitmapCoreHeader.bmpWidth + 31) / 32) * 4;
	const unsigned int imgSize = rowSize * bmp.bitmapCoreHeader.bmpHeight;

	os.write((const char*) bmp.pixelData, imgSize);

	return os;
}
}
