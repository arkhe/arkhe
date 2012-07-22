//arkhe math includes
#include "ArkheMath.h"
#include "ArkheException.h"

//std includes
#include <math.h>
#include <limits>

namespace arkhe
{

namespace math
{

//static variable definitions
const double Math::MIN = std::numeric_limits<const double>::min();
const double Math::MAX = std::numeric_limits<const double>::max();
const double Math::EPSILON = 1.0E-8;
const double Math::SMALLER_EPSILON = std::numeric_limits<const double>::epsilon(); //2.22045e-016
const double Math::LARGER_EPSILON = 1.0E-3;
const double Math::PI = 3.1415926535897931; //::acosl(-1.0L);
const double Math::TWO_PI = 2.0 * Math::PI;
const double Math::HALF_PI = 0.5 * Math::PI;
const double Math::E = 2.7182818284590452;
const double Math::DEG_TO_RAD = Math::TWO_PI / 360.0;
const double Math::RAD_TO_DEG = 360.0 / Math::TWO_PI;

//checks whether a double is sufficiently close to zero
const bool Math::isZero(const double &x)
{
	if(::abs(x) < Math::EPSILON)
	{
		return true;
	}
	return false;
}

//checks whether a double passed is set to NaN (Not a Number)
const bool Math::isNaN(const double &x)
{
	return x != x; //not sure if this will always work...
	//best to replace with a more concrete version...
}

//if double is close enough to zero then make it exactly zero
void Math::clean(double &x)
{
	if(Math::isZero(x))
	{
		x = 0.0;
	}
}

//get the reciprocal of x
//does not check for division by zero
const double Math::recip(const double &x)
{
	return 1.0 / x;
}

//check whether two values are equal within an epsilon value
const bool Math::equal(const double &a,const double &b,const double epsilon)
{
	return ::abs(a-b) < epsilon;
}

//return absolute value
const double Math::abs(const double &x)
{
	return ::abs(x);
}

//square x
const double Math::sqr(const double &x) { return x*x; }

//compute the square root of x
const double Math::sqrt(const double &x) { return ::sqrt(x); }

//compute nth power of a
const double Math::pow(const double &a,const double &n)
{
	return ::pow(a,n);
}

//trig functions
const double Math::sin(const double &x) { return ::sin(x); }
const double Math::aSin(const double &x) { return ::asin(x); }
const double Math::cos(const double &x) { return ::cos(x); }
const double Math::aCos(const double &x) { return ::acos(x); }

void Math::sinCos(const double &x,double &sx,double &cx)
{
	sx = ::sin(x);
	cx = ::cos(x);
}

const double Math::tan(const double &x) { return ::tan(x); }
const double Math::aTan(const double &x) { return ::atan(x); }
const double Math::aTan2(const double &x,const double &y) { return ::atan2(x,y); }

//compute the sign of x
const int Math::signum(const double &x)
{
	//-1 if x < 0,
	//0 if x = 0,
	//1 if x > 0
	return ((0 < x) - (x < 0));
}

//template specializations
template<> bool are_equal<double>(const double &a,const double &b,const double &epsilon) { return Math::equal(a,b,epsilon); }
template<> double get_zero<double>() { return 0.0; }
template<> double get_unit<double>() { return 1.0; }
template<> double set_zero<double>(double &x) { x = 0.0; }
template<> double set_unit<double>(double &x) { x = 1.0; }
template<> double get_recip<double>(const double &x) { return Math::recip(x); }
template<> bool is_zero<double>(const double &x) { return Math::isZero(x); }
template<> bool is_nan<double>(const double &x) { return Math::isNaN(x); }

} //namespace math

} //namespace arkhe
