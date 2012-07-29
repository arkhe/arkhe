//arkhe math includes
#include "ArkheRootFinding.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//////////////////////////////////////////////////////////////
////////////////// BEGIN ROOTFINDING::ROOTS //////////////////
//////////////////////////////////////////////////////////////

RootFinding::Roots::Roots() : set(RootFinding::Roots::EMPTY) {}

RootFinding::Roots::Roots(const std::vector<Complex> &r)
{
	roots = r;
	bool got_real = false;
	bool got_complex = false;
	if(r.empty())
	{
		set = RootFinding::Roots::EMPTY;
	}
	else
	{
		std::vector<Complex>::const_iterator i = r.begin();
		while(i != r.end())
		{
			if(i->isReal() && !got_real)
			{
				got_real = true;
			}
			if(i->isComplex() && !got_complex)
			{
				got_complex = true;
			}
			if(got_real && got_complex)
			{
				break;
			}
			++i;
		}
	}
	if(got_real && got_complex)
	{
		set = RootFinding::Roots::REAL_AND_COMPLEX;
	}
	else got_real ? set = RootFinding::Roots::REAL : set = RootFinding::Roots::COMPLEX;
}

RootFinding::Roots::Roots(const RootFinding::Roots &copy)
{
	roots = copy.roots;
	set = copy.set;
}

RootFinding::Roots &RootFinding::Roots::operator=(const RootFinding::Roots &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	roots = copy.roots;
	set = copy.set;
	return *this;
}

std::ostream &operator<<(std::ostream &out,const RootFinding::Roots &r)
{
	std::vector<Complex>::const_iterator i = r.roots.begin();
	out << '{';
	while(i != r.roots.end())
	{
		if(i+1 != r.roots.end())
		{
			out << *i << ',';
		}
		else
		{
			out << *i;
		}
		++i;
	}
	out << '}';
	return out;
}

bool RootFinding::Roots::hasRealRoots() const
{
	return set == RootFinding::Roots::REAL || set == RootFinding::Roots::REAL_AND_COMPLEX;
}

bool RootFinding::Roots::hasComplexRoots() const
{
	return set == RootFinding::Roots::COMPLEX || set == RootFinding::Roots::REAL_AND_COMPLEX;
}

bool RootFinding::Roots::getRealRoots(std::vector<Complex> &r) const
{
	if(!hasRealRoots())
	{
		return false;
	}
	r.clear(); //make sure list of roots is empty
	std::vector<Complex>::const_iterator i = roots.begin();
	while(i != roots.end())
	{
		if(i->isReal())
		{
			r.push_back(*i);
		}
	}
	return true;
}

bool RootFinding::Roots::getComplexRoots(std::vector<Complex> &c) const
{
	if(!hasComplexRoots())
	{
		return false;
	}
	c.clear(); //make sure list of roots is empty
	std::vector<Complex>::const_iterator i = roots.begin();
	while(i != roots.end())
	{
		if(i->isComplex())
		{
			c.push_back(*i);
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////
/////////////////// END ROOTFINDING::ROOTS ///////////////////
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
///////////////////// BEGIN ROOTFINDING //////////////////////
//////////////////////////////////////////////////////////////

RootFinding::Roots RootFinding::solve(const Polynomial &p)
{
	return RootFinding::Roots(p.solve());
}

RootFinding::Roots RootFinding::solve(const Polynomial &p,const Polynomial &q)
{
	return RootFinding::Roots(p.solve(q));
}

//get the nth root of x
double RootFinding::nthroot(unsigned int n,double x,double ep,unsigned int max_it)
{
	if(Math::isZero(x))
	{
		throw arkhe::base::Exception("division by zero");
	}
	if(n == 0)
	{
		return x;
	}
	double x0 = x / 2; //guess start value
	double x1;
	double recip = 1.0 / n;
	unsigned int n1 = n-1;
	bool converged = false;

	//iterate
	for(int i=0; i<(int)max_it; i++)
	{
		x1= recip * (n1*x0 + x/Math::pow(x0,n1));
		if(Math::abs(x0-x1) < ep)
		{
			//converged within suitable tolerance
			converged = true;
			break;
		}
		x0 = x1;
	}

	//if we did not converge, then we consider this a problem
	if(!converged)
	{
		throw arkhe::base::Exception("nth root algorithm did not converge");
	}

	return x1;
}

RootFinding::Roots RootFinding::bisection(const Polynomial &p,double x0,double x1,double ep)
{
	return RootFinding::Roots(); //empty set
}

RootFinding::Roots RootFinding::secant(const Polynomial &p,double x0,double x1,double ep,unsigned int max_it)
{
	return RootFinding::Roots(); //empty set
}

RootFinding::Roots RootFinding::falseposition(const Polynomial &p,double x0,double x1,double ep,unsigned int max_it)
{
	return RootFinding::Roots(); //empty set
}

RootFinding::Roots RootFinding::newton(const Polynomial &p,const Polynomial &pd,double x,double ep,unsigned int max_it)
{
	return RootFinding::Roots(); //empty set
}

//////////////////////////////////////////////////////////////
////////////////////// END ROOTFINDING ///////////////////////
//////////////////////////////////////////////////////////////

} //namespace math

} //namespace arkhe
