#ifndef __ARKHE_MATH_RAYN_H__
#define __ARKHE_MATH_RAYN_H__

//arkhe math includes
#include "ArkhePointN.h"
#include "ArkheVectorN.h"

//std includes
#include <ostream>

namespace arkhe
{

namespace math
{

template<unsigned int N>
class RayN
{
public:
	//constructors
	RayN();
	RayN(const PointN<N> &origin,const VectorN<N> &direction);
	RayN(const RayN &copy);
	//destructor
	~RayN();
	//operators
	RayN &operator=(const RayN &copy);
	PointN<N> operator()(double t) const;
	//friend operators
	template<unsigned int N> friend std::ostream &operator<<(std::ostream &out,const RayN<N> &r);
	//methods
	//variables
	PointN<N> o;
	VectorN<N> d;
private:
	//
protected:
	//
}; //class RayN

template<unsigned int N>
RayN<N>::RayN() {}

template<unsigned int N>
RayN<N>::RayN(const PointN<N> &origin,const VectorN<N> &direction) : o(origin),d(direction) {}

template<unsigned int N>
RayN<N>::RayN(const RayN &copy)
{
	o = copy.o;
	d = copy.d;
}

template<unsigned int N>
RayN<N>::~RayN() {}

template<unsigned int N>
RayN<N> &RayN<N>::operator=(const RayN<N> &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	o = copy.o;
	d = copy.d;
	return *this;
}

template<unsigned int N>
PointN<N> RayN<N>::operator()(double t) const
{
	return o + (d * t);
}

template<unsigned int N>
std::ostream &operator<<(std::ostream &out,const RayN<N> &r)
{
	out << '(' << r.o << "), (" << r.d << ')';
	return out;
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_RAYN_H__
