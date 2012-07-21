#ifndef __ARKHE_MATH_COMPLEX_H__
#define __ARKHE_MATH_COMPLEX_H__

//std includes
#include <ostream>

namespace arkhe
{

namespace math
{

class Complex
{
public:
	//constructors
	Complex();
	Complex(double real,double imag=0.0); //default to a real which is useful for polynomials
	explicit Complex(unsigned int real); //explicit cast to an int
	explicit Complex(int real); //explicit cast to an int
	explicit Complex(double real); //explicit cast to a double
	Complex(const Complex &copy);
	//destructor
	~Complex();
	//operators
	Complex &operator=(const Complex &copy);
	Complex operator+(double scalar) const;
	Complex operator+(const Complex &right) const;
	Complex &operator+=(double scalar);
	Complex &operator+=(const Complex &right);
	Complex operator-() const;
	Complex operator-(double scalar) const;
	Complex operator-(const Complex &right) const;
	Complex &operator-=(double scalar);
	Complex &operator-=(const Complex &right);
	Complex operator*(double scalar) const;
	Complex operator*(const Complex &right) const;
	Complex &operator*=(double scalar);
	Complex &operator*=(const Complex &right);
	Complex operator/(double scalar) const;
	Complex operator/(const Complex &right) const;
	Complex &operator/=(double scalar);
	Complex &operator/=(const Complex &right);
	bool operator<(const Complex &right) const
	{
		return arg() < right.arg(); //for std::sort - used to remove duplicates
	}
	bool operator==(const Complex &right) const;
	bool operator!=(const Complex &right) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Complex &c);
	//methods
	void clean();
	bool isZero() const;
	bool equal(const Complex &right) const;
	bool isReal() const;
	bool isImag() const;
	bool isComplex() const;
	const double mod() const;
	const double arg() const;
	Complex sqr() const;
	Complex pow(double n) const;
	Complex conjugate() const;
	void sqrt(Complex &root1,Complex &root2) const;
	//static variables
	static const Complex ZERO;
	//variables
	double r;
	double i;
private:
	//
protected:
	//
}; //class complex

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_COMPLEX_H__
