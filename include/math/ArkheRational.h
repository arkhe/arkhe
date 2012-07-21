#ifndef __ARKHE_MATH_RATIONAL_H__
#define __ARKHE_MATH_RATIONAL_H__

//math includes
#include "ArkheComplex.h"

namespace arkhe
{

namespace math
{

//forward declarations
class Polynomial;

//a rational function is a ratio of
//two polynomials
class Rational
{
public:
	friend class Polynomial;
	//constructors
	Rational();
	Rational(const Polynomial &p1,const Polynomial &p2);
	Rational(const Rational &copy);
	//destructor
	~Rational();
	//operators
	Rational &operator=(const Rational &copy);
	Complex operator()(double t) const;
private:
	//variables
	Polynomial *dividend;
	Polynomial *divisor;
protected:
	//
}; //class Rational

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_RATIONAL_H__
