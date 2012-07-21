#ifndef __ARKHE_MATH_POINTN_H__
#define __ARKHE_MATH_POINTN_H__

//arkhe math includes
#include "ArkheTupleN.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//forward declarations
template<unsigned int N> class VectorN;

template<unsigned int N>
class PointN : public TupleN<N>
{
public:
	//constructors
	PointN();
	PointN(const PointN &copy);
	PointN(const TupleN<N> &t);
	PointN(const VectorN<N> &v);
	//operators
	PointN operator+(const VectorN<N> &v) const;
	PointN &operator+=(const VectorN<N> &v);
	PointN operator-(const VectorN<N> &v) const;
	PointN &operator-=(const VectorN<N> &v);
	//methods
	double dist(const PointN &p) const;
	double distSq(const PointN &p) const;
	//static variables
	static const PointN ZERO;
private:
	//
protected:
	//
}; //PointN

template<unsigned int N> PointN<N>::PointN() : TupleN<N>() {}
template<unsigned int N> PointN<N>::PointN(const PointN<N> &copy) : TupleN<N>(copy) {}
template<unsigned int N> PointN<N>::PointN(const TupleN<N> &t) : TupleN<N>(t) {}
template<unsigned int N> PointN<N>::PointN(const VectorN<N> &v) : TupleN<N>(v) {}

template<unsigned int N>
PointN<N> PointN<N>::operator+(const VectorN<N> &v) const
{
	return PointN<N>(vector_ops::add(N,m_tuple,v.m_tuple));
}

template<unsigned int N>
PointN<N> &PointN<N>::operator+=(const VectorN<N> &v)
{
	double *tuple = vector_ops::add(N,m_tuple,v.m_tuple);
	destroy();
	m_tuple = tuple;
	return this;
}

template<unsigned int N>
PointN<N> PointN<N>::operator-(const VectorN<N> &v) const
{
	return PointN<N>(vector_ops::subtract(N,m_tuple,v.m_tuple));
}

template<unsigned int N>
PointN<N> &PointN<N>::operator-=(const VectorN<N> &v)
{
	double *tuple = vector_ops::subtract(N,m_tuple,v.m_tuple);
	destroy();
	m_tuple = tuple;
	return this;
}

//distance between two points
template<unsigned int N>
double PointN<N>::dist(const PointN<N> &p) const
{
	return vector_ops::dist(N,m_tuple,p.m_tuple);
}

//squared distance between two points
template<unsigned int N>
double PointN<N>::distSq(const PointN<N> &p) const
{
	return vector_ops::dist_sq(N,m_tuple,p.m_tuple);
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_POINTN_H__
