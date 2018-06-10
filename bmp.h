#ifndef __BMP_H
#define __BMP_H

#include <stdint.h>
#include <iostream>
#include <sstream>


// define IS_LITTLE_ENDIAN (!!(union { uint16_t u16; unsigned char c; }){ .u16 = 1 }.c)
#define IS_LITTLE_ENDIAN (*(uint16_t *)"\0\xff" > 0x100)

namespace JiMP2 {

/*
 * Informacje o formacie BMP https://en.wikipedia.org/wiki/BMP_file_format
 */

struct BMPFileHeader {
	char id[2];
	uint32_t size;
	char reserved[4];
	uint32_t dataOffset;

	BMPFileHeader() :
			id { 'B', 'M' }, size(0), dataOffset(0) {
		//id[0] = 'B';
		//id[1] = 'M';
	}
};

struct BitmapCoreHeader {
	const uint32_t size;
	const uint16_t bmpWidth;
	const uint16_t bmpHeight;
	const uint16_t colorPlanes;
	const uint16_t bitsPerPixel;

	BitmapCoreHeader(uint16_t width, uint16_t height) :
			size(12), bmpWidth(width), bmpHeight(height), colorPlanes(1),
			bitsPerPixel(24)
	{
	}

};

class BMP {
	BMPFileHeader bmpFileHeader;
	unsigned char* pixelData;

public:
	BitmapCoreHeader bitmapCoreHeader;

	BMP(uint16_t width, uint16_t height);
	virtual ~BMP();

	void setPixel(uint16_t x, uint16_t y, unsigned char r, unsigned char g, unsigned char b);

    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, unsigned char r, unsigned char g, unsigned char b);

    void drawRectangle(uint16_t xP, uint16_t yP, double width, double height, unsigned char r, unsigned char g, unsigned char b);

    void drawCircle(uint16_t x, uint16_t y, uint16_t R, unsigned char r, unsigned char g, unsigned char b);

    void drawWheel(uint16_t x, uint16_t y, uint16_t R, unsigned char r, unsigned char g, unsigned char b);

    void drawPartOfCircle(uint16_t x, uint16_t y, uint16_t R, double beg, double en, unsigned char r, unsigned char g, unsigned char b);

    void drawPartOfWheel(uint16_t x, uint16_t y, uint16_t R, double beg, double en,unsigned char r, unsigned char g, unsigned char b);

    void drawElipse(uint16_t x, uint16_t y, uint16_t Rx, uint16_t Ry, unsigned char r, unsigned char g, unsigned char b);

    void drawPolygon(uint16_t x, uint16_t y, uint16_t n, uint16_t R, unsigned char r, unsigned char g, unsigned char b);

	friend std::ostream& operator<<(std::ostream& os, const BMP& bmp);
};

}

#endif
