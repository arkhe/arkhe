#ifndef __ARKHE_MATH_VECTORN_H__
#define __ARKHE_MATH_VECTORN_H__

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
template<unsigned int N> class PointN;

template<unsigned int N>
class VectorN : public TupleN<N>
{
public:
	//friends
	friend PointN<N>;
	//constructors
	VectorN();
	VectorN(const VectorN &copy);
	VectorN(const TupleN<N> &t);
	VectorN(const PointN<N> &p);
	//operators
	VectorN operator+(const VectorN &right) const;
	VectorN &operator+=(const VectorN &right);
	VectorN operator-(const VectorN &right) const;
	VectorN &operator-=(const VectorN &right);
	//methods
	double dot(const VectorN &right) const;
	double len() const;
	double lenSq() const;
	void normalize();
	VectorN perpTo(const VectorN &v) const;
	VectorN parallelTo(const VectorN &v) const;
	//static variables
	static const VectorN ZERO;
	static const VectorN X_AXIS;
	static const VectorN Y_AXIS;
private:
	//
protected:
	//
}; //class VectorN

template<unsigned int N> VectorN<N>::VectorN() : TupleN<N>() {}
template<unsigned int N> VectorN<N>::VectorN(const VectorN &copy) : TupleN<N>(copy) {}
template<unsigned int N> VectorN<N>::VectorN(const TupleN<N> &t) : TupleN<N>(t) {}
template<unsigned int N> VectorN<N>::VectorN(const PointN<N> &p) : TupleN<N>(p) {}

template<unsigned int N>
VectorN<N> VectorN<N>::operator+(const VectorN<N> &right) const
{
	return VectorN<N>(vector_ops::add(N,m_tuple,right.m_tuple));
}

template<unsigned int N>
VectorN<N> &VectorN<N>::operator+=(const VectorN<N> &right)
{
	double *tuple = vector_ops::add(N,m_tuple,right.m_tuple);
	destroy();
	m_tuple = tuple;
	return this;
}

template<unsigned int N>
VectorN<N> VectorN<N>::operator-(const VectorN<N> &right) const
{
	return VectorN<N>(vector_ops::subtract(N,m_tuple,right.m_tuple));
}

template<unsigned int N>
VectorN<N> &VectorN<N>::operator-=(const VectorN<N> &right)
{
	double *tuple = vector_ops::subtract(N,m_tuple,right.m_tuple);
	destroy();
	m_tuple = tuple;
	return this;
}

template<unsigned int N>
double VectorN<N>::dot(const VectorN<N> &right) const
{
	return vector_ops::dot(N,m_tuple,right.m_tuple);
}

template<unsigned int N>
double VectorN<N>::len() const
{
	return return vector_ops::len(N,m_tuple);
}

template<unsigned int N>
double VectorN<N>::lenSq() const
{
	return vector_ops::len_sq(N,m_tuple);
}

template<unsigned int N>
void VectorN<N>::normalize()
{
	double *tuple = vector_ops::normalize(N,m_tuple);
	destroy();
	m_tuple = tuple;
}

template<unsigned int N>
VectorN<N> VectorN<N>::perpTo(const VectorN<N> &v) const
{
	return VectorN<N>(vector_ops::perpendicular_to(N,m_tuple,v.m_tuple));
}

template<unsigned int N>
VectorN<N> VectorN<N>::parallelTo(const VectorN<N> &v) const
{
	return VectorN<N>(vector_ops::parallel_to(N,m_tuple,v.m_tuple));
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_VECTORN_H__
