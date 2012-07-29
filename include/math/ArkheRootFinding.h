#ifndef __ARKHE_MATH_ROOT_FINDING_H__
#define __ARKHE_MATH_ROOT_FINDING_H__

//arkhe math includes
#include "ArkhePolynomial.h"

//std includes
#include <vector>
#include <ostream>

namespace arkhe
{

namespace math
{

//single class used to find roots of anything
//for which roots can be found.
class RootFinding
{
public:
	//classes
	class Roots
	{
	public:
		//enum
		enum Set
		{
			EMPTY, //no roots
			REAL, //all real roots
			REAL_AND_COMPLEX, //both real and complex roots
			COMPLEX //all complex roots
		}; //enum Set
		//constructors
		Roots();
		Roots(const std::vector<Complex> &r);
		Roots(const Roots &copy);
		//destructor
		~Roots() {}
		//operators
		Roots &operator=(const Roots &copy);
		//friend operators
		friend std::ostream &operator<<(std::ostream &out,const Roots &r);
		//methods
		bool hasRealRoots() const;
		bool hasComplexRoots() const;
		bool getRealRoots(std::vector<Complex> &r) const;
		bool getComplexRoots(std::vector<Complex> &c) const;
		//variables
		std::vector<Complex> roots;
		Set set;
	private:
		//
	protected:
		//
	}; //class Roots
	//static methods
	//methods that use native root finding methods
	static Roots solve(const Polynomial &p);
	static Roots solve(const Polynomial &p,const Polynomial &q);
	//iterative methods
	static double nthroot(unsigned int n,double x,double ep=1E-10,unsigned int max_it=1000);
	static Roots bisection(const Polynomial &p,double x0=-1E+7,double x1=1E+7,double ep=1E-10);
	static Roots secant(const Polynomial &p,double x0=-1E+7,double x1=1E+7,double ep=1E-10,unsigned int max_it=1000);
	static Roots falseposition(const Polynomial &p,double x0=-1E+7,double x1=1E+7,double ep=1E-10,unsigned int max_it=1000);
	static Roots newton(const Polynomial &p,const Polynomial &pd,double x=0,double ep=1E-10,unsigned int max_it=1000);
private:
	//
protected:
	//
}; //class RootFinding

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_ROOT_FINDING_H__
