//arkhe math includes
#include "ArkheComplex.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//static variable definitions
const Complex Complex::ZERO(0.0,0.0);

Complex::Complex() : r(0.0),i(0.0) {}

Complex::Complex(double real,double imag)
{
	r = real;
	i = imag;
}

//explicit constructors
Complex::Complex(unsigned int real) : r(real),i(0.0) {}
Complex::Complex(int real) : r(real),i(0.0) {}
Complex::Complex(double real) : r(real),i(0.0) {}

Complex::Complex(const Complex &copy)
{
	r = copy.r;
	i = copy.i;
}

Complex::~Complex() {}

Complex &Complex::operator=(const Complex &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	r = copy.r;
	i = copy.i;
	return *this;
}

Complex Complex::operator+(double scalar) const
{
	return Complex(r+scalar,i);
}

Complex Complex::operator+(const Complex &right) const
{
	return Complex(r+right.r,i+right.i);
}

Complex &Complex::operator+=(double scalar)
{
	r += scalar;
	return *this;
}

Complex &Complex::operator+=(const Complex &right)
{
	r += right.r;
	i += right.i;
	return *this;
}

Complex Complex::operator-() const { return Complex(-r,-i); }

Complex Complex::operator-(double scalar) const
{
	return Complex(r-scalar,i);
}

Complex Complex::operator-(const Complex &right) const
{
	return Complex(r-right.r,i-right.i);
}

Complex &Complex::operator-=(double scalar)
{
	r -= scalar;
	return *this;
}

Complex &Complex::operator-=(const Complex &right)
{
	r -= right.r;
	i -= right.i;
	return *this;
}

Complex Complex::operator*(double scalar) const
{
	return Complex(r*scalar,i*scalar);
}

Complex Complex::operator*(const Complex &right) const
{
	return Complex
	(
		r*right.r - i*right.i,
		r*right.i + i*right.r
	);
}

Complex &Complex::operator*=(double scalar)
{
	r *= scalar;
	i *= scalar;
	return *this;
}

Complex &Complex::operator*=(const Complex &right)
{
	Complex res
	(
		r*right.r - i*right.i,
		r*right.i + i*right.r
	);
	return (*this = res);
}

Complex Complex::operator/(double scalar) const
{
	if(Math::isZero(scalar))
	{
		throw arkhe::base::Exception("division by zero");
	}
	
	double recip = 1.0 / scalar;
	return Complex(r*recip,i*recip);
}

Complex Complex::operator/(const Complex &right) const
{
	double denom = right.r*right.r + right.i*right.i;
	if(Math::isZero(denom))
	{
		throw arkhe::base::Exception("division by zero");
	}
	double recip = 1.0 / denom;
	return Complex
	(
		(r*right.r + i*right.i) * recip,
		(i*right.r - r*right.i) * recip
	);
}

Complex &Complex::operator/=(double scalar)
{
	if(Math::isZero(scalar))
	{
		throw arkhe::base::Exception("division by zero");
	}
	double recip = 1.0 / scalar;
	r *= recip;
	i *= recip;
	return *this;
}

Complex &Complex::operator/=(const Complex &right)
{
	double denom = right.r*right.r + right.i*right.i;
	if(Math::isZero(denom))
	{
		throw arkhe::base::Exception("division by zero");
	}
	double recip = 1.0 / denom;
	return (*this) = Complex
	(
		(r*right.r + i*right.i) * recip,
		(i*right.r - r*right.i) * recip
	);
}

bool Complex::operator==(const Complex &right) const
{
	return Math::equal(r,right.r) && Math::equal(i,right.i);
}

bool Complex::operator!=(const Complex &right) const
{
	return !Math::equal(r,right.r) || !Math::equal(i,right.i);
}

std::ostream &operator<<(std::ostream &out,const Complex &c)
{
	int tmp = Math::signum(c.i);
	if(!Math::isZero(c.r) && !Math::isZero(c.i))
	{
		if(tmp == -1)
		{
			out << '(' << c.r << " - " << Math::abs(c.i) << "i)";
		}
		else
		{
			if(c.i != 1.0)
			{
				out << '(' << c.r << " + " << c.i << "i)";
			}
			else
			{
				out << '(' << c.r << " + i)";
			}
		}
	}
	else if(!Math::isZero(c.r) && Math::isZero(c.i))
	{
		out << c.r;
	}
	else if(Math::isZero(c.r) && !Math::isZero(c.i))
	{
		if(c.i != 1.0)
		{
			out << c.i << 'i';
		}
		else
		{
			out << 'i';
		}
	}
	else if(Math::isZero(c.r) && Math::isZero(c.i))
	{
		out << 0.0;
	}
	return out;
}

void Complex::clean()
{
	Math::clean(r);
	Math::clean(i);
}

bool Complex::isZero() const
{
	return Math::isZero(r) && Math::isZero(i);
}

bool Complex::equal(const Complex &right) const
{
	return Math::equal(r,right.r) && Math::equal(i,right.i);
}

//is a real number when the imaginary part is zero
//even when the real part is also zero...
bool Complex::isReal() const
{
	return Math::isZero(i);
}

//is pure imaginary number when real part is zero
//but imaginary number is not...
bool Complex::isImag() const
{
	return Math::isZero(r) && !Math::isZero(i);
}

//if the imaginary part is non-zero then this
//is definitely a complex number. it is, however,
//not necessarily a pure imaginary number.
bool Complex::isComplex() const
{
	return !Math::isZero(i);
}

const double Complex::mod() const
{
	return Math::sqrt(r*r + i*i);
}

const double Complex::arg() const
{
	return Math::aTan2(i,r);
}

Complex Complex::sqr() const
{
	return Complex(r*r-i*i,2*r*i);
}

//compute nth power
Complex Complex::pow(double n) const
{
	double rn = Math::pow(mod(),n);
	double nphi = n * arg();
	return Complex(rn * Math::cos(nphi),rn * Math::sin(nphi));
}

Complex Complex::conjugate() const
{
	return Complex(r,-i);
}

//need to do checks for negatives...
void Complex::sqrt(Complex &root1,Complex &root2) const
{
	if(isComplex())
	{
		//square roots of a + bi (b != 0) are +- (gamma + delta*i)
		//gamma = ((a + (a^2 + b^2)^1/2)/2)^1/2
		//delta = signum(b)*((-a + (a^2 + b^2)^1/2)/2)^1/2
		//signum is the sign function
		double mod = Math::sqrt(r*r + i*i);
		double gamma = Math::sqrt((r + mod) * 0.5);
		double delta = Math::signum(i) * Math::sqrt((-r + mod) * 0.5);
		//set roots
		root1 = Complex(-gamma,-delta);
		root2 = Complex(gamma,delta);
	}
	else //is a real number
	{
		root1 = Math::sqrt(r);
	}
}

} //namespace math

} //namespace arkhe
