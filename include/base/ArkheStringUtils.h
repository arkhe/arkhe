#ifndef __ARKHE_BASE_STRINGUTILS_H__
#define __ARKHE_BASE_STRINGUTILS_H__

//std includes
#include <string>
#include <sstream>
#include <vector>

#include <iostream>

namespace arkhe
{

namespace base
{

namespace string_utils
{

std::vector<std::string> getTokens(const std::string &line)
{
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string s;
	while(std::getline(ss,s,' '))
	{
		tokens.push_back(s);
	}
	return tokens;
}

} //namespace string_utils

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_STRINGUTILS_H__
