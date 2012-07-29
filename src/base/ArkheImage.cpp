//arkhe base includes
#include "ArkheImage.h"

namespace arkhe
{

namespace base
{

Image::Image() {}

Image::Image(unsigned int w,unsigned int h) : m_width(w),m_height(h) {}

Image::Image(const Image &copy)
{
	m_width = copy.m_width;
	m_height = copy.m_height;
	m_pixels = copy.m_pixels;
}

Image::~Image() {}

Image &Image::operator=(const Image &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	m_width = copy.m_width;
	m_height = copy.m_height;
	m_pixels = copy.m_pixels;
	return *this;
}

Image::Pixel Image::getPixel(unsigned int x,unsigned int y)
{
	return m_pixels(x,y);
}

void Image::setPixel(unsigned int x,unsigned int y,const Image::Pixel &p)
{
	m_pixels(x,y) = p;
}

} //namespace base

} //namespace arkhe
