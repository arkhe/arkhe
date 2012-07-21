#ifndef __ARKHE_DEMOS_EXCEPTION_TESTS_H__
#define __ARKHE_DEMOS_EXCEPTION_TESTS_H__

//arkhe base includes
#include "ArkheException.h"
using namespace arkhe::base;

float throw_on_div_by_zero(float x,float y)
{
	//divide x by y
	if(y == 0)
	{
		throw Exception("divide by zero");
	}
	else
	{
		return x / y;
	}
}

#endif //__ARKHE_DEMOS_EXCEPTION_TESTS_H__
