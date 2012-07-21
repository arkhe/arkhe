#ifndef __ARKHE_BASE_EXCEPTION_H__
#define __ARKHE_BASE_EXCEPTION_H__

//std includes
#include <string>

namespace arkhe
{

namespace base
{

class Exception
{
public:
	//constructors
	Exception(const std::string &msg);
	Exception(const Exception &copy);
	//destructor
	~Exception();
	//operators
	Exception &operator=(const Exception &copy);
	//methods
	const std::string &what() const;
private:
	//variables
	std::string message;
protected:
	//
}; //class Exception

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_EXCEPTION_H__
