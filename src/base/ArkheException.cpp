//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace base
{

Exception::Exception(const std::string &msg)
{
	message = msg;
}

Exception::Exception(const Exception &copy)
{
	message = copy.message;
}

Exception::~Exception() {}

Exception &Exception::operator=(const Exception &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	message = copy.message;
	return *this;
}

const std::string &Exception::what() const
{
	return message;
}

} //namespace base

} //namespace arkhe
