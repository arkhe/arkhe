#ifndef __ARKHE_BASE_PPMIMAGE_H__
#define __ARKHE_BASE_PPMIMAGE_H__

//arkhe base includes
#include "ArkheImage.h"

namespace arkhe
{

namespace base
{

class PPMImage : public Image
{
public:
	//constructor
	PPMImage();
	PPMImage(unsigned int width,unsigned int height);
	PPMImage(const std::string &file);
	//methods
	bool read(const std::string &file);
	bool write(const std::string &file) const;
private:
	//
protected:
	//
}; //class PPMImage

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_PPMIMAGE_H__
