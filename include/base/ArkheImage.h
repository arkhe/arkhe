#ifndef __ARKHE_BASE_IMAGE_H__
#define __ARKHE_BASE_IMAGE_H__

//arkhe base includes
#include "ArkheT2dArray.h"

//std includes
#include <string>

namespace arkhe
{

namespace base
{

//all RGB pixel values to be stored as
//doubles in the range [0,1].
class Image
{
public:
	//structs
	struct Pixel
	{
		double r,g,b;
	}; //struct Pixel
	//constructors
	Image();
	Image(unsigned int w,unsigned int h);
	Image(const Image &copy);
	//destructor
	~Image();
	//operators
	Image &operator=(const Image &copy);
	//methods
	Pixel getPixel(unsigned int x,unsigned int y);
	void setPixel(unsigned int x,unsigned int y,const Pixel &p);
	virtual bool read(const std::string &file) = 0;
	virtual bool write(const std::string &file) const = 0;
private:
protected:
	//variables
	unsigned int m_width;
	unsigned int m_height;
	T2dArray<Pixel> m_pixels;
}; //class Image

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_IMAGE_H__
