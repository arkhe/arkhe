#ifndef __ARKHE_MATH_MATH_H__
#define __ARKHE_MATH_MATH_H__

namespace arkhe
{

namespace math
{

//collection of static class functions
//and free template functions below...
class Math
{
public:
	//static methods
	static const bool isZero(const double &x);
	static const bool isNaN(const double &x);
	static void clean(double &x);
	static const double recip(const double &x);
	static const bool equal(const double &a,const double &b);
	static const double abs(const double &x);
	static const double sqr(const double &x);
	static const double sqrt(const double &x);
	static const double pow(const double &a,const double &n);
	static const double sin(const double &x);
	static const double aSin(const double &x);
	static const double cos(const double &x);
	static const double aCos(const double &x);
	static void sinCos(const double &x,double &sx,double &cx);
	static const double tan(const double &x);
	static const double aTan(const double &x);
	static const double aTan2(const double &x,const double &y);
	static const int signum(const double &x);
	//static variables
	static const double MIN;
	static const double MAX;
	static const double EPSILON;
	static const double SMALLER_EPSILON;
	static const double NaN;
	static const double PI;
	static const double HALF_PI;
	static const double TWO_PI;
	static const double E;
	static const double DEG_TO_RAD;
	static const double RAD_TO_DEG;
private:
	//
protected:
	//
}; //class Math

//template functions
//get min value from pair
/*template<typename T>
const T min(const T &a,const T &b)
{
	return (a+b)/2 - ::abs(a-b)/2;
}

//get max value from pair
template<typename T>
const T max(const T &a,const T &b)
{
	return (a+b)/2 + ::abs(a-b)/2;
}

//lerp
template<typename T>
const T lerp(double t,const T &a,const T &b)
{
	return (a * (1.0 - t)) + (b * t);
}*/

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_MATH_H__
