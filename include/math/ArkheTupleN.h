#ifndef __ARKHE_MATH_TUPLEN_H__
#define __ARKHE_MATH_TUPLEN_H__

//arkhe math includes
#include "ArkheVectorOps.h"
#include "ArkheMath.h"

//std includes
#include <ostream>

namespace arkhe
{

namespace math
{

//+,+=,-.-= operators not implemented
//as these have to be handled
//specifically by the derived classes
//ie. point + point is illegal etc.
template<unsigned int N>
class TupleN
{
public:
	//constructors
	TupleN(bool init=true);
	TupleN(double *tuple);
	TupleN(const TupleN &copy);
	//destructor
	virtual ~TupleN();
	//operators
	TupleN &operator=(const TupleN &copy);
	operator double*();
	double operator[](unsigned int i) const;
	double &operator[](unsigned int i);
	TupleN operator-() const;
	TupleN operator*(const double scalar) const;
	TupleN &operator*=(const double scalar);
	TupleN operator/(const double scalar) const;
	TupleN &operator/=(const double scalar);
	bool operator==(const TupleN &right) const;
	bool operator!=(const TupleN &right) const;
	//friend operators
	template<unsigned int N> friend std::ostream &operator<<(std::ostream &out,const TupleN<N> &t);
	//methods
	void clean();
	bool isZero() const;
private:
	//
protected:
	//methods
	void destroy();
	//variables
	double *m_tuple;
}; //class TupleN

template<unsigned int N>
TupleN<N>::TupleN(bool init)
{
	if(init)
	{
		m_tuple = vector_ops::create(N);
	}
	else
	{
		m_tuple = 0;
	}
}

//construct tuple from array
//tuple takes ownership of the data
//note that the array passed in is assumed
//to be of size N.
template<unsigned int N>
TupleN<N>::TupleN(double *tuple)
{
	if(tuple == 0)
	{
		throw arkhe::base::Exception("cannot construct vector with zero elements");
	}
	m_tuple = tuple;
}

template<unsigned int N>
TupleN<N>::TupleN(const TupleN<N> &copy)
{
	m_tuple = vector_ops::copy(N,copy.m_tuple);
}

template<unsigned int N>
TupleN<N>::~TupleN()
{
	if(m_tuple)
	{
		delete[] m_tuple;
	}
}

template<unsigned int N>
TupleN<N> &TupleN<N>::operator=(const TupleN<N> &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	destroy();
	m_tuple = vector_ops::copy(N,copy.m_tuple);
	return *this;
}

template<unsigned int N>
TupleN<N>::operator double*()
{
	return &m_tuple[0];
}

template<unsigned int N>
double TupleN<N>::operator[](unsigned int i) const
{
	if(i >= N)
	{
		throw arkhe::base::Exception("out of range");
	}
	return *((&m_tuple[i]) + i);
}

template<unsigned int N>
double &TupleN<N>::operator[](unsigned int i)
{
	if(i >= N)
	{
		throw arkhe::base::Exception("out of range");
	}
	return *((&m_tuple[i]) + i);
}

template<unsigned int N>
TupleN<N> TupleN<N>::operator-() const
{
	return TupleN<N>(vector_ops::negate(N,m_tuple));
}

template<unsigned int N>
TupleN<N> TupleN<N>::operator*(const double scalar) const
{
	return TupleN<N>(vector_ops::multiply(N,m_tuple,scalar));
}

template<unsigned int N>
TupleN<N> &TupleN<N>::operator*=(const double scalar)
{
	double *tuple = vector_ops::multiply(N,m_tuple,scalar);
	destroy();
	m_tuple = tuple;
	return *this;
}

template<unsigned int N>
TupleN<N> TupleN<N>::operator/(const double scalar) const
{
	return TupleN<N>(vector_ops::divide(N,m_tuple,scalar));
}

template<unsigned int N>
TupleN<N> &TupleN<N>::operator/=(const double scalar)
{
	double *tuple = vector_ops::divide(N,m_tuple,scalar);
	destroy();
	m_tuple = tuple;
	return *this;
}

template<unsigned int N>
bool TupleN<N>::operator==(const TupleN<N> &right) const
{
	return vector_ops::equal(m_tuple,right.m_tuple);
}

template<unsigned int N>
bool TupleN<N>::operator!=(const TupleN<N> &right) const
{
	return !vector_ops::equal(m_tuple,right.m_tuple);
}

template<unsigned int N>
std::ostream &operator<<(std::ostream &out,const TupleN<N> &t)
{
	return vector_ops::stream_out(N,t.m_tuple,out);
}

template<unsigned int N>
void TupleN<N>::clean()
{
	vector_ops::clean(N,m_tuple);
}

template<unsigned int N>
bool TupleN<N>::isZero() const
{
	return vector_ops::is_zero();
}

template<unsigned int N>
void TupleN<N>::destroy()
{
	if(m_tuple)
	{
		delete[] m_tuple;
		m_tuple = 0;
	}
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_TUPLEN_H__
