//arkhe math includes
#include "ArkhePolynomial.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

//std includes
#include <algorithm>

namespace arkhe
{

namespace math
{

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN TERM /////////////////////////
//////////////////////////////////////////////////////////////

Term::Term() {}
Term::Term(double x) : n(0) { c = x; }
Term::Term(const Complex &_c,unsigned int _n) : c(_c),n(_n) {}
Term::Term(const Term &copy)
{
	c = copy.c;
	n = copy.n;
}

Term &Term::operator=(const Term &copy)
{
	if(this == &copy) return *this;
	c = copy.c;
	n = copy.n;
	return *this;
}

Complex Term::operator()(const Complex &t) const
{
	return c * t.pow(n);
}

Term Term::operator+(const Term &right) const
{
	if(n != right.n)
	{
		throw arkhe::base::Exception("not like terms");
	}
	return Term(c + right.c,n);
}

Term &Term::operator+=(const Term &right)
{
	if(n != right.n)
	{
		throw arkhe::base::Exception("not like terms");
	}
	c += right.c;
	return *this;
}

Term Term::operator-() const { return Term(-c,n); }

Term Term::operator-(const Term &right) const
{
	if(n != right.n)
	{
		throw arkhe::base::Exception("not like terms");
	}
	return Term(c - right.c,n);
}

Term &Term::operator-=(const Term &right)
{
	if(n != right.n)
	{
		throw arkhe::base::Exception("not like terms");
	}
	c -= right.c;
	return *this;
}

Term Term::operator*(const Term &right) const
{
	return Term(c * right.c,n + right.n);
}

Term &Term::operator*=(const Term &right)
{
	c *= right.c;
	n += right.n;
	return *this;
}

Term Term::operator/(const Term &right) const
{
	//division by zero taken care of in the complex class
	return Term(c / right.c,n - right.n);
}

Term &Term::operator/=(const Term &right)
{
	//division by zero taken care of in the complex class
	c /= right.c;
	n -= right.n;
	return *this;
}

bool Term::operator==(const Term &right) const
{
	return c == right.c && n == right.n;
}

bool Term::operator!=(const Term &right) const
{
	return c != right.c || n != right.n;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Term &t)
{
	if(t.n > 1)
	{
		out << t.c << "x^" << t.n;
	}
	else if(t.n == 1)
	{
		out << t.c << 'x';
	}
	else
	{
		out << t.c;
	}
	return out;
}

//get the derivative of this term
Term Term::derivative() const
{
	if(n > 0)
	{
		return Term(c * n,n - 1);
	}
	return Term(Complex::ZERO,0);
}

//////////////////////////////////////////////////////////////
////////////////////////// END TERM //////////////////////////
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
////////////////////// BEGIN POLYNOMIAL //////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const bool Polynomial::m_stream_out_types = false;

//default constructor makes zero polynomial
Polynomial::Polynomial() : m_degree(-1),m_type(Polynomial::ZERO) {}

//construct constant polynomial
Polynomial::Polynomial(const Complex &c) : m_degree(0),m_type(Polynomial::CONSTANT)
{
	m_terms[0] = Term(c,0);
	removeZeroTerms();
}

//construct linear polynomial of the form mx + b
Polynomial::Polynomial
(
	const Complex &m,
	const Complex &b
) : m_degree(1),m_type(Polynomial::LINEAR)
{
	m_terms[1] = Term(m,1);
	m_terms[0] = Term(b,0);
	removeZeroTerms();
}

//construct quadratic polynomial of the form ax^2 + bx + c
Polynomial::Polynomial
(
	const Complex &a,
	const Complex &b,
	const Complex &c
) : m_degree(2),m_type(Polynomial::QUADRATIC)
{
	m_terms[2] = Term(a,2);
	m_terms[1] = Term(b,1);
	m_terms[0] = Term(c,0);
	removeZeroTerms();
}

//construct cubic polynomial of the form ax^3 + bx^2 + cx + d
Polynomial::Polynomial
(
	const Complex &a,
	const Complex &b,
	const Complex &c,
	const Complex &d
) : m_degree(3),m_type(Polynomial::CUBIC)
{
	m_terms[3] = Term(a,3);
	m_terms[2] = Term(b,2);
	m_terms[1] = Term(c,1);
	m_terms[0] = Term(d,0);
	removeZeroTerms();
}

//construct quartic polynomial of the form ax^4 + bx^3 + cx^2 + dx + e
Polynomial::Polynomial
(
	const Complex &a,
	const Complex &b,
	const Complex &c,
	const Complex &d,
	const Complex &e
) : m_degree(4),m_type(Polynomial::QUARTIC)
{
	m_terms[4] = Term(a,4);
	m_terms[3] = Term(b,3);
	m_terms[2] = Term(c,2);
	m_terms[1] = Term(d,1);
	m_terms[0] = Term(e,0);
	removeZeroTerms();
}

//construct quintic polynomial of the form ax^5 + bx^4 + cx^3 + dx^3 + ex + f
Polynomial::Polynomial
(
	const Complex &a,
	const Complex &b,
	const Complex &c,
	const Complex &d,
	const Complex &e,
	const Complex &f
) : m_degree(5),m_type(Polynomial::QUINTIC)
{
	m_terms[5] = Term(a,5);
	m_terms[4] = Term(b,4);
	m_terms[3] = Term(c,3);
	m_terms[2] = Term(d,2);
	m_terms[1] = Term(e,1);
	m_terms[0] = Term(f,0);
	removeZeroTerms();
}

//construct arbitrary polynomial of the form anx^n + an-1x^n-1 + an-2x^n-2 + ... + a1x + a0
//from array
Polynomial::Polynomial(const Term terms[]) : m_type(Polynomial::ARBITRARY)
{
	unsigned int size = sizeof(terms) / sizeof(Term);
	m_degree = -1;
	if(size > 0)
	{
		for(int i=0; i<(int)size; i++)
		{
			if(!terms[i].c.isZero())
			{
				if(m_degree < (int)terms[i].n)
				{
					m_degree = terms[i].n;
				}
			}
		}
	}
	removeZeroTerms();
}

//construct arbitrary polynomial of the form anx^n + an-1x^n-1 + an-2x^n-2 + ... + a1x + a0
//from std::vector
Polynomial::Polynomial(const std::vector<Term> &terms) : m_type(Polynomial::ARBITRARY)
{
	m_degree = -1;
	if(terms.size() > 0)
	{
		std::vector<Term>::const_iterator i = terms.begin();
		while(i != terms.end())
		{
			if(!i->c.isZero())
			{
				m_terms[i->n] = Term(i->c,i->n);
				if(m_degree < (int)i->n)
				{
					m_degree = i->n;
				}
			}
			++i;
		}
		removeZeroTerms();
	}
}

//copy constructor
Polynomial::Polynomial(const Polynomial &copy)
{
	m_degree = copy.m_degree;
	m_type = copy.m_type;
	m_terms = copy.m_terms;
}

//destructor
Polynomial::~Polynomial() {}

//assignment operator
Polynomial &Polynomial::operator=(const Polynomial &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	m_degree = copy.m_degree;
	m_type = copy.m_type;
	m_terms = copy.m_terms;
	return *this;
}

//evaluate the polynomial at t
Complex Polynomial::operator()(const Complex &t) const
{
	Complex c = Complex::ZERO;
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		c += (i->second)(t);
		++i;
	}
	return c;
}

//sum of number (0 degree) and polynomial
Polynomial Polynomial::operator+(const Complex &c) const
{
	Polynomial res = *this;
	if(hasTerm(0))
	{
		res.m_terms[0].c += c;
	}
	return res;
}

//add two polynomials
Polynomial Polynomial::operator+(const Polynomial &right) const
{
	std::vector<Term> terms;
	//get highest degree as this will potentially
	//contain the most terms
	int deg;
	m_degree > right.m_degree ? deg = m_degree : deg = right.m_degree;
	Term t1,t2;
	for(int n=0; n<=deg; n++)
	{
		switch(Polynomial::likeTerms(n,*this,right,t1,t2))
		{
		case Polynomial::BOTH_TERMS:
			terms.push_back(t1+t2);
			break;
		case Polynomial::FIRST_TERM:
			terms.push_back(t1);
			break;
		case Polynomial::SECOND_TERM:
			terms.push_back(t2);
			break;
		}
	}
	return Polynomial(terms);
}

//add number (0 degree) to self
Polynomial &Polynomial::operator+=(const Complex &c)
{
	if(hasTerm(0))
	{
		m_terms[0].c += c;
	}
	return *this;
}

//add polynomial to self
Polynomial &Polynomial::operator+=(const Polynomial &right)
{
	return (*this) = (*this) + right;
}

//negate polynomial
Polynomial Polynomial::operator-() const
{
	std::vector<Term> terms;
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		terms.push_back(-i->second);
		++i;
	}
	return Polynomial(terms);
}

//subtraction of number (0 degree) and polynomial
Polynomial Polynomial::operator-(const Complex &c) const
{
	Polynomial res = *this;
	if(hasTerm(0))
	{
		res.m_terms[0].c -= c;
	}
	return res;
}

//subtract two polynomials
Polynomial Polynomial::operator-(const Polynomial &right) const
{
	std::vector<Term> terms;
	//get highest degree as this will potentially
	//contain the most terms
	int deg;
	m_degree > right.m_degree ? deg = m_degree : deg = right.m_degree;
	Term t1,t2;
	for(int n=0; n<=deg; n++)
	{
		switch(Polynomial::likeTerms(n,*this,right,t1,t2))
		{
		case Polynomial::BOTH_TERMS:
			terms.push_back(t1-t2);
			break;
		case Polynomial::FIRST_TERM:
			terms.push_back(t1);
			break;
		case Polynomial::SECOND_TERM:
			terms.push_back(-t2);
			break;
		}
	}
	return Polynomial(terms);
}

//subtract number (0 degree) from self
Polynomial &Polynomial::operator-=(const Complex &c)
{
	if(hasTerm(0))
	{
		m_terms[0].c -= c;
	}
	return *this;
}

//subtract polynomial from self
Polynomial &Polynomial::operator-=(const Polynomial &right)
{
	return (*this) = (*this) - right;
}

//multiply number (0 degree) and polynomial
Polynomial Polynomial::operator*(const Complex &c) const
{
	Polynomial res = *this;
	if(hasTerm(0))
	{
		res.m_terms[0].c *= c;
	}
	return res;
}

//multiply two polynomials
Polynomial Polynomial::operator*(const Polynomial &right) const
{
	std::vector<Term> terms;
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	std::map<unsigned int,Term>::const_iterator j;
	while(i != m_terms.end())
	{
		j = right.m_terms.begin();
		while(j != right.m_terms.end())
		{
			terms.push_back(i->second * j->second);
			++j;
		}
		++i;
	}
	return Polynomial(terms);
}

//multiply number (0 degree) into self
Polynomial &Polynomial::operator*=(const Complex &c)
{
	std::map<unsigned int,Term>::iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		i->second.c *= c;
		++i;
	}
	return *this;
}

//multiply polynomial into self
Polynomial &Polynomial::operator*=(const Polynomial &right)
{
	return (*this) = (*this) * right;
}

//divide number (0 degree) into polynomial
Polynomial Polynomial::operator/(const Complex &c) const
{
	Polynomial res = *this;
	if(hasTerm(0))
	{
		res.m_terms[0].c /= c;
	}
	return res;
}

//divide number (0 degree) into self
Polynomial &Polynomial::operator/=(const Complex &c)
{
	std::map<unsigned int,Term>::iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		i->second.c /= c;
		++i;
	}
	return *this;
}

//equal operator
bool Polynomial::operator==(const Polynomial &right) const
{
	return m_degree == right.m_degree && m_terms == right.m_terms;
}

//not-equal operator
bool Polynomial::operator!=(const Polynomial &right) const
{
	return m_degree != right.m_degree || m_terms != right.m_terms;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Polynomial &p)
{
	//output type
	if(Polynomial::m_stream_out_types)
	{
		switch(p.m_type)
		{
		case Polynomial::ZERO:
			out << "ZERO: ";
			break;
		case Polynomial::CONSTANT:
			out << "CONSTANT: ";
			break;
		case Polynomial::LINEAR:
			out << "LINEAR: ";
			break;
		case Polynomial::CUBIC:
			out << "CUBIC: ";
			break;
		case Polynomial::QUADRATIC:
			out << "QUADRATIC: ";
			break;
		case Polynomial::QUARTIC:
			out << "QUARTIC: ";
			break;
		case Polynomial::QUINTIC:
			out << "QUINTIC: ";
			break;
		case Polynomial::ARBITRARY:
			out << "DEGREE" << p.m_degree << ": ";
			break;
		}
	}
	//output the polynomial
	bool first = false;
	std::map<unsigned int,Term>::const_iterator i = p.m_terms.begin();
	while(i != p.m_terms.end())
	{
		if(!first)
		{
			first = true;
		}
		else
		{
			out << " + ";
		}
		out << i->second;
		++i;
	}
	return out;
}

//remove terms that are basically zero
void Polynomial::clean()
{
	removeZeroTerms();
}

//get the degree of this polynomial
int Polynomial::degree() const { return m_degree; }
Polynomial::Type Polynomial::type() const { return m_type; }

//get the number of terms in this polynomial
unsigned int Polynomial::terms() const { return (unsigned int)m_terms.size(); }

//find whether nth power term exists in this polynomial
bool Polynomial::hasTerm(unsigned int n) const
{
	std::map<unsigned int,Term>::const_iterator i = m_terms.find(n);
	if(i != m_terms.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//find whether nth power term exists in this polynomial
//and store it in the parameter t
bool Polynomial::hasTerm(unsigned int n,Term &t) const
{
	std::map<unsigned int,Term>::const_iterator i = m_terms.find(n);
	if(i != m_terms.end())
	{
		t = i->second;
		return true;
	}
	else
	{
		return false;
	}
}

//is this a polynomial with all coefficients being real?
bool Polynomial::isReal() const
{
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		if(!i->second.c.isReal())
		{
			return false;
		}
		++i;
	}
	return true;
}

//get this polynomial in monic form
Polynomial Polynomial::monic() const
{
	std::vector<Term> terms;
	Complex c = m_terms.at(m_degree).c; //division by zero checked in the complex class
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		terms.push_back(Term(i->second.c / c,i->second.n));
		++i;
	}
	return Polynomial(terms); //the monic
}

//get the derivative of this polynomial
Polynomial Polynomial::derivative() const
{
	std::vector<Term> terms;
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		terms.push_back(i->second.derivative());
		++i;
	}
	return Polynomial(terms);
}

//////////////////////////////////////////////////////////////
//////////////////// BEGIN POLYNOMIAL::QR ////////////////////
//////////////////////////////////////////////////////////////

Polynomial::QR::QR() : q(0),r(0) {}

Polynomial::QR::QR(const Polynomial &Q,const Polynomial &R)
{
	q = new Polynomial(Q);
	r = new Polynomial(R);
}

Polynomial::QR::QR(const QR &copy)
{
	copy.q ? q = new Polynomial(*copy.q) : q = 0;
	copy.r ? r = new Polynomial(*copy.r) : r = 0;
}

Polynomial::QR::~QR()
{
	if(q) delete q;
	if(r) delete r;
}

Polynomial::QR &Polynomial::QR::operator=(const QR &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	copy.q ? q = new Polynomial(*copy.q) : q = 0;
	copy.r ? r = new Polynomial(*copy.r) : r = 0;
	return *this;
}

bool Polynomial::QR::hasNegativeTerm() const { return q->hasNegativeTerm() || r->hasNegativeTerm(); }

bool Polynomial::QR::signsAlternate() const
{
	if(q->signsAlternate())
	{
		if((*r) == Polynomial())
		{
			return true;
		}
		else
		{
			Term qt = q->m_terms.at(0); //get last term (lowest power) of the quotient
			Term rt = r->m_terms.at(r->m_degree); //get first (highest power) term of the remainder
			if(qt.n-1 == rt.n) //powers of terms descend in synch
			{
				if(Math::signum(qt.c.r) != Math::signum(rt.c.r) && q->signsAlternate())
				{
					//last term of quotient and first term of remainder alternate
					//and all the terms of the remainder alternate, therefore we
					return true;
				}
			}
			else
			{
				//there is a zero in between
				if(q->signsAlternate() && r->signsAlternate())
				{
					//if the signs of both the quotient
					//and remainder alternate then we
					return true;
				}
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////
///////////////////// END POLYNOMIAL::QR /////////////////////
//////////////////////////////////////////////////////////////

//remove all terms that are zero from the polynomial
//when all zero's are removed, set the new degree
void Polynomial::removeZeroTerms()
{
	int d = -1;
	std::map<unsigned int,Term>::iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		if(i->second.c.isZero())
		{
			i = m_terms.erase(i);
			continue;
		}
		if(d < (int)i->second.n) //failure to cast will cause bug
		{
			d = i->second.n;
		}
		++i;
	}
	m_degree = d; //set new degree
	m_degree > 5 ? m_type = Polynomial::ARBITRARY : m_type = static_cast<Polynomial::Type>(m_degree);
}

//find whether two polynomials have like terms of the same degree
//used for addition, subtraction etc.
Polynomial::LikeTerms Polynomial::likeTerms(unsigned int n,const Polynomial &a,const Polynomial &b,Term &at,Term &bt)
{
	bool c1_b,c2_b;
	//gather terms
	c1_b = a.hasTerm(n,at);
	c2_b = b.hasTerm(n,bt);

	//both terms exist
	if(c1_b && c2_b)
	{
		return Polynomial::BOTH_TERMS;
	}
	else if(c1_b && !c2_b) //only first term exists
	{
		return Polynomial::FIRST_TERM;
	}
	else if(!c1_b && c2_b) //only second term exists
	{
		return Polynomial::SECOND_TERM;
	}
	//no terms exist
	return Polynomial::NO_TERMS;
}

//find the number of variations in sign. used for descartes' rule of signs
//only works with polynomials having only real coefficients, that is, the
//method only evaluates the sign of the real portion of the coefficient under
//the assumption that the imaginary part is zero...
//
//Descartes' rule of signs: If P(x) is a polynomial with real coefficients, the
//number of positive roots of P(x) = 0 is either equal to the number of variations
//in sign of P(x) or less than that by an even number.
//
//The number of negative roots of P(x) = 0 is either equal to the number of
//variations in sign of P(-x) or less than that by an even number.
//
//Example: P(x) = 3x^3 - 2x^2 + x - 5 = 0.
//Number of possible positive roots is 3 or 1.
//Number of possible negative roots is 0.
//Number of nonreal roots is 0 if the number of positive roots is 3, or otherwise
//there are 2 complex roots (1 positive root).
//-------------------------------------
//|# pos roots|# neg roots|# com roots|
//-------------------------------------
//|     3     |     0     |     0     |
//|     1     |     0     |     2     |
//-------------------------------------
unsigned int Polynomial::signVariations(bool negate) const
{
	//if negate is true, then if the term has an even power
	//then the sign remains the same, otherwise it becomes the
	//negative of itself.
	unsigned int sign_variations = 0;
	bool first = true;
	int cur_sign,prev_sign;
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		//get the sign of the coefficient
		cur_sign = Math::signum(i->second.c.r);
		if(negate)
		{
			if(i->second.n % 2 != 0) //not an even power
			{
				cur_sign = -cur_sign; //so negate the sign
			}
		}
		if(first)
		{
			first = false;
		}
		else
		{
			if(cur_sign != prev_sign)
			{
				sign_variations++; //got sign variation...
			}
		}
		prev_sign = cur_sign;
		++i;
	}
	return sign_variations;
}

//check whether this polynomial has at least one negative term.
//assumes only real coefficients of the polynomial terms.
bool Polynomial::hasNegativeTerm() const
{
	std::map<unsigned int,Term>::const_iterator i = m_terms.begin();
	while(i != m_terms.end())
	{
		if(Math::signum(i->second.c.r) == -1)
		{
			return true;
		}
		++i;
	}
	return false;
}

//check whether the signs alternate across all the terms
//of the polynomial. needed to compute root bounds.
//if any terms below the highest term are zero then these
//terms can be filled in to make the signs alternate.
//assumes only real coefficients of the polynomial terms.
bool Polynomial::signsAlternate() const
{
	bool first = true;
	bool has_term,zero_term = false;
	int cur_sign,prev_sign;
	Term t;
	for(int n=m_degree; n>=0; n--)
	{
		//get the sign of the coefficient
		has_term = hasTerm(n,t);
		cur_sign = Math::signum(t.c.r);
		if(first)
		{
			first = false;
		}
		else
		{
			if(has_term)
			{
				if(!zero_term)
				{
					if(cur_sign == prev_sign)
					{
						return false;
					}
				}
				else
				{
					zero_term = false;
				}
			}
			else //came across a zero term
			{
				zero_term = true;
			}
		}
		prev_sign = cur_sign;
	}
	return true;
}

//divide 'this' by p. q is the quotient
//and r is the remainder.
void Polynomial::divide(const Polynomial &p,Polynomial &q,Polynomial &r) const
{
	if(m_degree < p.m_degree)
	{
		throw arkhe::base::Exception("cannot divide a polynomial by a higher degree polynomial");
	}
	Polynomial depressed = (*this);
	std::vector<Term> q_terms;
	Term t;
	std::vector<Term> tmp;
	int n = (int)m_degree;
	while(n >= (int)p.m_terms.at(p.m_degree).n)
	{
		if(hasTerm(n))
		{
			t = depressed.m_terms.at(depressed.m_degree) / p.m_terms.at(p.m_degree);
			q_terms.push_back(t);
			tmp.push_back(t);
			depressed -= p * Polynomial(tmp);
			tmp.clear();
		}
		--n;
	}
	//set quotient and remainder
	q = Polynomial(q_terms);
	r = depressed;
}

//divide 'this' by p. q is the quotient
//and r is the remainder.
//return quotient + remainder - used for bounds method.
Polynomial::QR Polynomial::divide(const Polynomial &p) const
{
	Polynomial q,r;
	divide(p,q,r);
	return Polynomial::QR(q,r);
}

//find upper and lower bounds on roots. the polynomial must be
//one with all terms being real numbers, and the leading term
//must have a positive coefficient.
//notes:
//upper bound:
//if we dvivide by a positive number c, and the last row
//of the divsion is entirely non-negative, then the theorem
//guarantees that c is an upper bound of the roots. if the
//division contains some negative values then c could still
//be an upper bound.
//
//lower bound:
//if we divide by a negative number d and the signs of the division
//alternate, then the theorem guarantees that d is a lower bound
//of the roots. if the signs do not alternate, then d could still
//be a lower bound.
//
//the unfortunate thing is that this theorem does not find the
//best bounds for the roots of the equation, but provides a
//starting point...
bool Polynomial::bounds(int u_start,int l_start,int &upper_bound,int &lower_bound)
{
	if(Math::signum(m_terms.at(m_degree).c.r) == -1)
	{
		throw arkhe::base::Exception("leading coefficient is not positive");
	}
	if(!isReal())
	{
		throw arkhe::base::Exception("polynomial has complex coefficients");
	}
	if(Math::signum(u_start) != 1 && Math::signum(l_start) != -1)
	{
		throw arkhe::base::Exception("upper bound must be greater than zero and lower must be less than zero");
	}
	//attempt to find upper bound
	Polynomial q;
	bool found_upper = false;
	bool found_lower = false;
	int c;
	Polynomial::QR qr;
	//find upper bound
	for(int r=u_start; r>0; r--)
	{
		qr = divide(Polynomial(1,-r));
		if(!found_upper)
		{
			if(!qr.hasNegativeTerm())
			{
				upper_bound = r;
				c = r;
				found_upper = true;
			}
		}
		else
		{
			if(qr.hasNegativeTerm())
			{
				//definitely break
				break;
			}
			else
			{
				upper_bound = r; //improved lower bound
				c = r;
			}
		}
	}
	if(found_upper) //find lower bound
	{
		for(int r=l_start; r<0; r++)
		{
			qr = divide(Polynomial(1,-r));
			if(!found_lower)
			{
				if(qr.signsAlternate())
				{
					lower_bound = r;
					found_lower = true;
				}
			}
			else
			{
				if(!qr.signsAlternate())
				{
					//definitely break
					break;
				}
				else
				{
					lower_bound = r; //improved lower bound
				}
			}
		}
	}
	return found_upper && found_lower;
}

//solve the polynomial
std::vector<Complex> Polynomial::solve() const
{
	std::vector<Complex> roots;
	
	if(m_type == Polynomial::ZERO || m_type == Polynomial::CONSTANT)
	{
		//no solutions
	}
	else if(m_type == Polynomial::LINEAR)
	{
		//solve linear equation mx + b = 0
		Complex r = -m_terms.at(0).c / m_terms.at(1).c;
		roots.push_back(r);
	}
	else if(m_type == Polynomial::QUADRATIC)
	{
		//solve quadratic equation ax^2 + bx + c = 0
		//using quadratic formula
		//x = [-b +- sqrt(b^2 - 4ac)]/2a
		Complex a = m_terms.at(2).c;
		Complex b = m_terms.at(1).c;
		Complex c = m_terms.at(0).c;
		Complex a2 = a*2;
		Complex discrim = b*b - a*c*4; //get the discriminant
		Complex c1,c2;
		//solve roots using quadratic formula
		if(discrim.isComplex())
		{
			discrim.sqrt(c1,c2); //get the complex roots of the discriminant
			roots.push_back((-b + c1) / a2);
			roots.push_back((-b - c1) / a2);
			roots.push_back((-b + c2) / a2);
			roots.push_back((-b - c2) / a2);
		}
		else //is a real number
		{
			discrim.sqrt(c1,c2);
			roots.push_back((-b + c1) / a2);
			roots.push_back((-b - c1) / a2);
		}
	}
	else if(m_type == Polynomial::CUBIC)
	{
		//solve cubic equation ax^3 + bx^3 + cx + d = 0
		//for the cubic equation with real coefficients, there exists at least one solution among the real numbers.
		//discriminant cases:
		//> 0: three distinct real roots
		//= 0: multiple root and all roots are real
		//< 0: one real root and two non-real complex conjugate roots
		//
		//the general cubic formula is as follows:
		//
		Complex a = m_terms.at(3).c;
		Complex b = m_terms.at(2).c;
		Complex c = m_terms.at(1).c;
		Complex d = m_terms.at(0).c;
		//compute the discriminant
		//b^2c^2 - 4ac^3 - 4b^3d - 27a^2d^2 + 18abcd
		Complex discrim = (b*b)*(c*c) - a*c.pow(3)*4 - b.pow(3)*d*4 - (a*a)*(d*d)*27 + a*b*c*d*18;
		Complex x1,x2,x3; //roots to find
		//solve roots using the cubic formula
	}
	else if(m_type == Polynomial::QUARTIC)
	{
		//solve quartic equation ax^4 + bx^3 + cx^2 + dx + e = 0
	}
	else
	{
		//no general solutions to polynomials of degree 5 and up
		//use other methods that are restricted by the coefficients
		//if these methods cannot be used then
		throw arkhe::base::Exception("must use an alternative iterative method to solve this polynomial");
	}

	//remove duplicate roots
	std::sort(roots.begin(),roots.end());
	roots.erase(std::unique(roots.begin(),roots.end()),roots.end());
	return roots;
}

//solve two polynomials
std::vector<Complex> Polynomial::solve(const Polynomial &p) const
{
	//solve 'this' = p
	Polynomial q = (*this) - p;
	return q.solve();
}

//////////////////////////////////////////////////////////////
/////////////////////// END POLYNOMIAL ///////////////////////
//////////////////////////////////////////////////////////////

} //namespace math

} //namespace arkhe
