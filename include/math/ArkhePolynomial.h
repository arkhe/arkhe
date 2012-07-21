#ifndef __ARKHE_MATH_POLYNOMIAL_H__
#define __ARKHE_MATH_POLYNOMIAL_H__

//arkhe math includes
#include "ArkheComplex.h"

//std includes
#include <vector>
#include <map>
#include <ostream>

namespace arkhe
{

namespace math
{

//forward class declarations
class RootFinding;
class MathIntegrityTests;

//term
//for now it has been implemented with the
//assumption that all terms will have a single
//variable. if multivariable terms are to be
//added then it's just a matter of adding
//a variable identifier and comparision code.
class Term
{
public:
	//constructors
	Term();
	explicit Term(double x);
	Term(const Complex &_c,unsigned int _n);
	Term(const Term &copy);
	//operators
	Term &operator=(const Term &copy);
	Complex operator()(const Complex &t) const;
	Term operator+(const Term &right) const;
	Term &operator+=(const Term &right);
	Term operator-() const;
	Term operator-(const Term &right) const;
	Term &operator-=(const Term &right);
	Term operator*(const Term &right) const;
	Term &operator*=(const Term &right);
	Term operator/(const Term &right) const;
	Term &operator/=(const Term &right);
	bool operator==(const Term &right) const;
	bool operator!=(const Term &right) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Term &t);
	//methods
	Term derivative() const;
	//variables
	Complex c; //coefficient
	unsigned int n; //power
private:
	//
protected:
	//
}; //class Term

//polynomial class with complex coefficients
//complex numbers allow us to use numbers that
//are subsets of the complex set ie. integers
//since Complex has an explicit cast to double type
//you can treat this class as if Complex is a double
//by passing double (as well as int, unsigned int etc)
//themselves, ie. Complex c = Math::PI
class Polynomial
{
public:
	//friend classes
	friend RootFinding;
	friend MathIntegrityTests;
	//enums
	enum Type
	{
		ZERO = -1,
		CONSTANT = 0,
		LINEAR = 1,
		QUADRATIC = 2,
		CUBIC = 3,
		QUARTIC = 4,
		QUINTIC = 5,
		ARBITRARY = 100 //arbitrary degree
	};
	//constructors
	Polynomial();
	Polynomial(const Complex &c);
	Polynomial(const Complex &m,const Complex &b);
	Polynomial(const Complex &a,const Complex &b,const Complex &c);
	Polynomial(const Complex &a,const Complex &b,const Complex &c,const Complex &d);
	Polynomial(const Complex &a,const Complex &b,const Complex &c,const Complex &d,const Complex &e);
	Polynomial(const Complex &a,const Complex &b,const Complex &c,const Complex &d,const Complex &e,const Complex &f);
	Polynomial(const Term terms[]);
	Polynomial(const std::vector<Term> &terms);
	Polynomial(const Polynomial &copy);
	//destructor
	~Polynomial();
	//operators
	Polynomial &operator=(const Polynomial &copy);
	Complex operator()(const Complex &t) const;
	Polynomial operator+(const Complex &c) const;
	Polynomial operator+(const Polynomial &right) const;
	Polynomial &operator+=(const Complex &c);
	Polynomial &operator+=(const Polynomial &right);
	Polynomial operator-() const;
	Polynomial operator-(const Complex &c) const;
	Polynomial operator-(const Polynomial &right) const;
	Polynomial &operator-=(const Complex &c);
	Polynomial &operator-=(const Polynomial &right);
	Polynomial operator*(const Complex &c) const;
	Polynomial operator*(const Polynomial &right) const;
	Polynomial &operator*=(const Complex &c);
	Polynomial &operator*=(const Polynomial &right);
	Polynomial operator/(const Complex &c) const;
	//TODO: add division by polynomial
	//cannot add /= operator due to the fact
	//that a remainder can occur, which makes
	// the resultant a non-polynomial, but a rational function
	//
	//Possibly return a factored form polynomial in the division op
	//P(x) = (x - r)(Q(x) + R(x)
	//if R(x) = 0, then (x - r) is a perfect factor of P(x)
	//
	Polynomial &operator/=(const Complex &c);
	bool operator==(const Polynomial &right) const;
	bool operator!=(const Polynomial &right) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Polynomial &p);
	//methods
	void clean();
	int degree() const;;
	Type type() const;
	unsigned int terms() const;
	bool hasTerm(unsigned int n) const;
	bool hasTerm(unsigned int n,Term &t) const;
	bool isReal() const;
	Polynomial monic() const;
	Polynomial derivative() const;
//private:
	//enums
	enum LikeTerms
	{
		BOTH_TERMS,
		FIRST_TERM,
		SECOND_TERM,
		NO_TERMS
	}; //enum LikeTerms
	//quotient-remainder pair
	//used for finding bounds easily
	class QR
	{
	public:
		//constructors
		QR();
		QR(const Polynomial &Q,const Polynomial &R);
		QR(const QR &copy);
		//destructor
		~QR();
		//operators
		QR &operator=(const QR &copy);
		//methods
		bool hasNegativeTerm() const;
		bool signsAlternate() const;
		//variables
		Polynomial *q;
		Polynomial *r;
	private:
		//
	protected:
		//
	}; //class QR
	//methods
	void removeZeroTerms(); //private as we always ensure the polynomial has non-zero terms
	static LikeTerms likeTerms(unsigned int n,const Polynomial &a,const Polynomial &b,Term &at,Term &bt);
	unsigned int signVariations(bool negate=false) const;
	bool hasNegativeTerm() const;
	bool signsAlternate() const;
	void divide(const Polynomial &p,Polynomial &q,Polynomial &r) const;
	QR divide(const Polynomial &p) const;
	bool bounds(int u_start,int l_start,int &upper_bound,int &lower_bound);
	std::vector<Complex> solve() const;
	std::vector<Complex> solve(const Polynomial &p) const;
	//variables
	int m_degree; //degree of this polynomial, -1 for zero polynomial
	Type m_type; //type of this polynomial
	std::map<unsigned int,Term> m_terms; //quick access to terms of a certain power
	//static variables
	static const bool m_stream_out_types;
protected:
	//
}; //class Polynomial

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_POLYNOMIAL_H__
