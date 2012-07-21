//arkhe math includes
#include "ArkheRational.h"
#include "ArkhePolynomial.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

Rational::Rational() : dividend(0),divisor(0) {}

Rational::Rational(const Polynomial &p1,const Polynomial &p2)
{
	dividend = new Polynomial(p1);
	divisor = new Polynomial(p2);
}

Rational::Rational(const Rational &copy)
{
	dividend = new Polynomial(*copy.dividend);
	divisor = new Polynomial(*copy.divisor);
}

Rational::~Rational()
{
	if(dividend)
	{
		delete dividend;
		delete divisor; //both must exist together
	}
}

Rational &Rational::operator=(const Rational &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	if(dividend)
	{
		delete dividend;
		delete divisor; //both must exist together
	}
	dividend = new Polynomial(*copy.dividend);
	divisor = new Polynomial(*copy.divisor);
	return *this;
}

Complex Rational::operator()(double t) const
{
	Complex c1 = (*dividend)(t);
	Complex c2 = (*divisor)(t);
	if(c2.isZero())
	{
		throw arkhe::base::Exception("division by zero");
	}
	return c1 / c2;
}

} //namespace math

} //namespace arkhe
