//arkhe math includes
#include "ArkheVectorOps.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

namespace vector_ops
{

//these methods assume that the dynamically allocated memory that they
//create will be claimed by their callers and so do not keep track of this memory.

double *create(unsigned int N)
{
	double *A = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		A[i] = 0.0;
	}
	return A;
}
	
double *copy(unsigned int N,const double *A)
{
	double *B = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		B[i] = A[i];
	}
	return B;
}

double *add(unsigned int N,const double *A,const double *B)
{
	double *C = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		C[i] = A[i] + B[i];
	}
	return C;
}

double *negate(unsigned int N,const double *A)
{
	double *B = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		B[i] = -A[i];
	}
	return B;
}

double *subtract(unsigned int N,const double *A,const double *B)
{
	double *C = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		C[i] = A[i] - B[i];
	}
	return C;
}

double *multiply(unsigned int N,const double *A,double x)
{
	double *B = new double[N];
	for(unsigned int i=0; i<N; i++)
	{
		B[i] = A[i] * x;
	}
	return B;
}

double *divide(unsigned int N,const double *A,double x)
{
	if(Math::isZero(x))
	{
		throw arkhe::base::Exception("division by zero");
	}
	double *B = new double[N];
	double recip = Math::recip(x);
	for(unsigned int i=0; i<N; i++)
	{
		B[i] = A[i] * recip;
	}
	return B;
}

bool equal(unsigned int N,const double *A,const double *B)
{
	for(unsigned int i=0; i<N; i++)
	{
		if(!Math::equal(A[i],B[i]))
		{
			return false;
		}
	}
	return true;
}

std::ostream &stream_out(unsigned int N,const double *A,std::ostream &out)
{
	for(unsigned int i=0; i<N; i++)
	{
		out << A[i];
		if(i != N-1)
		{
			out << ',';
		}
	}
	return out;
}

void clean(unsigned int N,double *A)
{
	for(unsigned int i=0; i<N; i++)
	{
		Math::clean(A[i]);
	}
}

bool is_zero(unsigned int N,double *A)
{
	for(unsigned int i=0; i<N; i++)
	{
		if(Math::isZero(A[i]))
		{
			return false;
		}
	}
	return true;
}

double dot(unsigned int N,const double *A,const double *B)
{
	double d = 0.0;
	for(unsigned int i=0; i<N; i++)
	{
		d += A[i] * B[i];
	}
	return d;
}

double len_sq(unsigned int N,const double *A)
{
	double dot = 0.0;
	for(unsigned int i=0; i<N; i++)
	{
		dot += A[i] * A[i];
	}
	return dot;
}

double len(unsigned int N,const double *A)
{
	return Math::sqrt(len_sq(N,A));
}

double *normalize(unsigned int N,const double *A)
{
	double mag = len(N,A);
	if(Math::isZero(mag))
	{
		throw arkhe::base::Exception("division by zero");
	}
	double recip = Math::recip(mag);
	return multiply(N,A,recip);
}

double *perp(const double *A)
{
	double *B = new double[2];
	B[0] = -A[1];
	B[1] = A[0];
	return B;
}

double *perpendicular_to(unsigned int N,const double *A,const double *B)
{
	double lsq = len_sq(N,A);
	if(Math::isZero(lsq))
	{
		throw arkhe::base::Exception("division by zero");
	}
	return subtract(N,A,multiply(N,B,dot(N,A,B)/lsq));
}

double *parallel_to(unsigned int N,const double *A,const double *B)
{
	double lsq = len_sq(N,A);
	if(Math::isZero(lsq))
	{
		throw arkhe::base::Exception("division by zero");
	}
	return multiply(N,B,dot(N,A,B)/lsq);
}

double dist_sq(unsigned int N,const double *A,const double *B)
{
	double d = 0.0;
	for(unsigned int i=0; i<N; i++)
	{
		d += (A[i] - B[i]) * (A[i] - B[i]);
	}
	return d;
}

double dist(unsigned int N,const double *A,const double *B)
{
	return Math::sqrt(dist_sq(N,A,B));
}

double *cross(unsigned int N,const double *A,const double *B)
{
	double *C = new double[N];
	C[0] = A[1]*B[2] - A[2]*B[1];
	C[1] = A[2]*B[0] - A[0]*B[2];
	C[2] = A[0]*B[1] - A[1]*B[0];
	return C;
}

} //namespace vector_ops

} //namespace math

} //namespace arkhe
