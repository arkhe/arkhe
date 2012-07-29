//arkhe base includes
#include "ArkhePPMImage.h"
#include "ArkheException.h"
#include "ArkheStringUtils.h"

//std includes
#include <fstream>

namespace arkhe
{

namespace base
{

PPMImage::PPMImage() : Image() {}

PPMImage::PPMImage(unsigned int width,unsigned int height) : Image(width,height) {}

PPMImage::PPMImage(const std::string &file)
{
	read(file);
}

bool PPMImage::read(const std::string &file)
{
	std::ifstream in_file(file,std::ios::in | std::ios::binary);
	if(!in_file.is_open())
	{
		return false;
	}
	else
	{
		std::string line;
		std::vector<std::string> tokens;
		std::stringstream ss;
		bool got_header = false;
		bool got_wh = false;
		bool got_max = false;
		std::vector<std::string> data;
		while(in_file.good())
		{
			std::getline(in_file,line);
			tokens = string_utils::getTokens(line);
			if(tokens.size() == 1 && tokens[0][0] == '#')
			{
				//skip comments
			}
			else if(tokens.size() == 1 && tokens[0][0] == 'P' && tokens[0][1] == '6')
			{
				got_header = true;
			}
			else
			{
				tokens = string_utils::getTokens(line);
				if(tokens.size() == 2)
				{
					if(!got_header)
					{
						throw Exception("not a valid PPM file");
					}
					//width and height
					ss = std::stringstream(tokens[0]);
					ss >> m_width;
					ss = std::stringstream(tokens[1]);
					ss >> m_height;
					m_pixels = T2dArray<Image::Pixel>(m_width,m_height);
					got_wh = true;
					//std::cout << "GOT WIDTH AND HEIGHT: " << m_width << ' ' << m_height << std::endl;
				}
				else if(tokens.size() == 1)
				{
					if(!got_wh)
					{
						throw Exception("not a valid PPM file");
					}
					//max value
					//std::cout << "GOT MAX VALUE" << std::endl;
					got_max = true;
				}
				else
				{
					if(!got_header && !got_wh && !got_max)
					{
						throw Exception("not a valid PPM file");
					}
					//pixel data
					std::cout << "GOT PIXEL DATA: " << tokens.size() << " ITEMS" << std::endl;
					data.insert(data.end(),tokens.begin(),tokens.end());
				}
			}
		}
		std::cout << "NUM PIXELS: " << data.size() << std::endl;
	}
	in_file.close();
	return true;
}

bool PPMImage::write(const std::string &file) const
{
	return false;
}

} //namespace base

} //namespace arkhe
