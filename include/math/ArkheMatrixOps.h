#ifndef __ARKHE_MATH_MATRIXOPS_H__
#define __ARKHE_MATH_MATRIXOPS_H__

//arkhe math includes
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

//std includes
#include <vector>
#include <sstream>

namespace arkhe
{

namespace math
{

namespace matrix_ops
{

//these methods assume that the dynamically allocated memory that they
//create will be claimed by their callers and so do not keep track of this memory.

//create and initialize MxN matrix
template<typename T>
T *create(unsigned int M,unsigned int N)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T *A = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		A[i] = T(); //call default constructor
	}
	return A;
}

//create MxN matrix from vector of vector of elements.
template<typename T>
T *create(unsigned int M,unsigned int N,const std::vector<std::vector<T>> &elements)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0 || elements.empty())
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	//check the dimensions of the elements
	//create iterators
	std::vector<std::vector<T> >::const_iterator i = elements.begin(); //iterator to the outer vector
	std::vector<T>::const_iterator j; //set this in the loop
	unsigned int outer_size = (unsigned int)elements.size();
	unsigned int inner_size = (unsigned int)i->size();
	if(outer_size != M || inner_size != N)
	{
		std::stringstream sstream;
		sstream << "cannot construct a " << M << 'x' << N << " matrix from a ";
		sstream << outer_size << 'x' << inner_size << " matrix";
		throw arkhe::base::Exception(sstream.str());
	}

	//create matrix
	T *A = new T[num_elements];
	//set matrix elements from given elements vector
	int x = 0;
	while(i != elements.end())
	{
		j = i->begin();
		while(j != i->end())
		{
			A[x++] = *j;
			++j;
		}
		++i;
	}
	return A;
}

//create MxN matrix from vector of vector of elements. we don't specificy the size
//of the matrix as it is constructed from the input element vector of vectors
//for this reason we save the dimensions M and N.
template<typename T>
T *create(const std::vector<std::vector<T>> &elements,unsigned int &M,unsigned int &N)
{
	//check the dimensions of the elements
	//create iterators
	std::vector<std::vector<T> >::const_iterator i = elements.begin(); //iterator to the outer vector
	std::vector<T>::const_iterator j; //set this in the loop
	unsigned int outer_size = (unsigned int)elements.size();
	unsigned int inner_size = (unsigned int)i->size();
	unsigned int num_elements = outer_size*inner_size;
	if(num_elements == 0 || elements.empty())
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	//create matrix
	M = outer_size;
	N = inner_size;
	T *A = new T[num_elements];
	//set matrix elements from given elements vector
	int x = 0;
	while(i != elements.end())
	{
		j = i->begin();
		while(j != i->end())
		{
			A[x++] = *j;
			++j;
		}
		++i;
	}
	return A;
}

//set near-zero elements of MxN matrix to zero
template<typename T> void clean(unsigned int M,unsigned int N,T *A)
{
	for(unsigned int i=0; i<M*N; i++)
	{
		if(is_zero(A[i]) || is_nan(A[i]))
		{
			A[i] = T(); //default constructor is assumed to default to zero
		}
	}
}

//create MxN zero matrix using given value for zero
template<typename T>
T *zero(unsigned int M,unsigned int N)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T *A = new T[num_elements];
	unsigned int x = 0;
	T z = get_zero<T>();
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<N; j++)
		{
			A[x++] = z;
		}
	}
	return A;
}

//is NxM matrix zero?
template<typename T>
bool zero(unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	for(unsigned int i=0; i<num_elements; i++)
	{
		if(is_zero<T>(A[i]))
		{
			return false;
		}
	}
	return true;
}

//get min element
template<typename T>
T min_element(unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T B = A[0];
	for(unsigned int i=1; i<num_elements; i++)
	{
		if(A[i] < B)
		{
			B = A[i];
		}
	}
	return B;
}

//get max element
template<typename T>
T max_element(unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T B = A[0];
	for(unsigned int i=1; i<num_elements; i++)
	{
		if(A[i] > B)
		{
			B = A[i];
		}
	}
	return B;
}

//create MxM identity matrix using the given values
//for entries of zero and one
template<typename T>
T *identity(unsigned int M)
{
	unsigned int num_elements = M*M;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T *A = new T[num_elements];
	unsigned int x = 0;
	T z = get_zero<T>();
	T u = get_unit<T>();
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<M; j++)
		{
			i == j ? A[x++] = u : A[x++] = z;
		}
	}
	return A;
}

//copy MxN matrix
template<typename T>
T *copy(unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T *B = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		B[i] = A[i];
	}
	return B;
}

//get index of element (i,j) from MxN matrix
template<typename T>
unsigned int index(unsigned int i,unsigned int j,unsigned int M,unsigned int N)
{
	if(i >= M || j >= N) //unsigned int so cannot be < 0
	{
		throw arkhe::base::Exception("index out of range");
	}
	return (i * N) + j;
}

//add MxN matrix A and PxQ matrix B
template<typename T>
T *add(unsigned int M,unsigned int N,const T *A,unsigned int P,unsigned int Q,const T *B)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	if(M != P || N != Q)
	{
		std::stringstream sstream;
		sstream << "cannot add " << M << 'x' << N << " matrix to ";
		sstream << P << 'x' << Q << " matrix";
		throw arkhe::base::Exception(sstream.str());
	}

	T *C = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		C[i] = A[i] + B[i];
	}
	return C;
}

//negate MxN matrix A
template<typename T>
T *negate(unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = M*N;
	T *B = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		B[i] = -A[i];
	}
	return B;
}

//subtract PxQ matrix B from MxN matrix A
template<typename T>
T *subtract(unsigned int M,unsigned int N,const T *A,unsigned int P,unsigned int Q,const T *B)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	if(M != P || N != Q)
	{
		std::stringstream sstream;
		sstream << "cannot subtract " << P << 'x' << Q << " matrix from ";
		sstream << M << 'x' << N << " matrix";
		throw arkhe::base::Exception(sstream.str());
	}

	T *C = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		C[i] = A[i] - B[i];
	}
	return C;
}

//multiply MxN matrix A by value B
template<typename T>
T *multiply(unsigned int M,unsigned int N,const T *A,const T &B)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *C = new T[num_elements];
	for(unsigned int i=0; i<num_elements; i++)
	{
		C[i] = A[i] * B;
	}
	return C;
}

//multiply MxN matrix A by PxQ matrix B
//N must be equal to P
template<typename T>
T *multiply(unsigned int M,unsigned int N,const T *A,unsigned int P,unsigned int Q,const T *B)
{
	if(N != P)
	{
		std::stringstream sstream;
		sstream << "cannot multiply " << M << 'x' << N << " matrix by ";
		sstream << P << 'x' << Q << " matrix";
		throw arkhe::base::Exception(sstream.str());
	}
	unsigned int num_elements = N*P;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *C = new T[num_elements];
	unsigned int x = 0;
	for(unsigned int i=0; i<N; i++)
	{
		for(unsigned int j=0; j<P; j++)
		{
			T tmp = T(); //default to zero value
			for(unsigned int k=0; k<N; k++)
			{
				tmp += A[index<T>(i,k,M,N)] * B[index<T>(k,j,N,P)];
			}
			C[x++] = tmp;
		}
	}
	return C;
}

//divide MxN matrix A by value B
template<typename T>
T *divide(unsigned int M,unsigned int N,const T *A,const T &B)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *C = new T[num_elements];
	if(is_zero<T>(B))
	{
		throw arkhe::base::Exception("division by zero");
	}
	T B_recip = get_recip<T>(B);
	for(unsigned int i=0; i<num_elements; i++)
	{
		C[i] = A[i] * B_recip;
	}
	return C;
}

//are two MxN matrices A and B equal?
template<typename T>
bool equal(unsigned int M,unsigned int N,const T *A,const T *B)
{
	for(unsigned int i=0; i<M*N; i++)
	{
		if(!are_equal<T>(A[i],B[i],Math::LARGER_EPSILON))
		{
			return false;
		}
	}
	return true;
}

//stream out MxN matrix
template<typename T>
std::ostream &stream_out(unsigned int M,unsigned int N,const T *A,std::ostream &out)
{
	unsigned int x = 0;
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<N; j++)
		{
			out << A[x++] << ' ';
		}
		out << '\n';
	}
	return out;
}

//get the matrix formed by removing the ith row and jth column from MxN matrix A
template<typename T>
T *sub_matrix(unsigned int row,unsigned int col,unsigned int M,unsigned int N,const T *A)
{
	unsigned int num_elements = (M-1)*(N-1);
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *B = new T[num_elements];
	unsigned int x = 0;
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<N; j++)
		{
			if(i == row)
			{
				break; //completely skip this row
			}
			if(j != col)
			{
				B[x++] = A[index<T>(i,j,M,N)];
			}
		}
	}
	return B;
}

//get transpose of MxN matrix as NxM matrix
template<typename T>
T *transpose(unsigned int M,unsigned int N,const T *A,unsigned int *P=0,unsigned int *Q=0)
{
	unsigned int num_elements = M*N;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *B = new T[num_elements];
	if(P && Q)
	{
		*P = N;
		*Q = M;
	}
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<N; j++)
		{
			B[index<T>(j,i,N,M)] = A[index<T>(i,j,M,N)];
		}
	}
	return B;
}

//get MxM trace
template<typename T>
T trace(unsigned int M,const T *A)
{
	if(M == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}
	T trace = T();
	for(unsigned int i=0; i<M*M; i+=M+1)
	{
		trace += A[i];
	}
	return trace;
}

//perform LU decomposition and return either
//the lower or upper triangular matrix
enum LU
{
	LU_LOWER,
	LU_UPPER
};
template<typename T>
T *LU_decomposition(unsigned int M,const T *A,LU lu)
{
	if(M == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *L = create<T>(M,M); //create zero matrices L and U
	T *U = create<T>(M,M);
	for(unsigned int k=0; k<M; k++)
	{
		L[index<T>(k,k,M,M)] = 1;

		for(unsigned int j=k; j<M; j++)
		{
			T sum = T();
			for(unsigned int s=0; s<k; s++)
			{
				sum += L[index<T>(k,s,M,M)] * U[index<T>(s,j,M,M)];
			}
			U[index<T>(k,j,M,M)] = A[index<T>(k,j,M,M)] - sum;
		}
		for(unsigned int i=k+1; i<M; i++)
		{
			T sum = T();
			for(unsigned int s=0; s<k; s++)
			{
				sum += L[index<T>(i,s,M,M)] * U[index<T>(s,k,M,M)];
			}
			L[index<T>(i,k,M,M)] = (A[index<T>(i,k,M,M)] - sum) / U[index<T>(k,k,M,M)];
		}
	}
	//return the lower matrix
	if(lu == LU_LOWER)
	{
		delete[] U;
		clean(M,M,L);
		return L;
	}
	//otherwise return the upper matrix
	delete[] L;
	clean(M,M,U);
	return U;
}

//get MxM determinant
template<typename T>
T determinant(unsigned int M,const T *A)
{
	T det = get_unit<T>();
	T *U = LU_decomposition<T>(M,A,LU_UPPER);
	for(unsigned int i=0; i<M; i++)
	{
		det *= U[index<T>(i,i,M,M)];
	}
	delete[] U;
	return det;
}

//get (i,j)'th cofactor
template<typename T>
T cofactor(unsigned int i,unsigned int j,unsigned int M,const T *A)
{
	T *B = sub_matrix<T>(i,j,M,M,A);
	T C = (int)Math::pow(-1,i+j) * determinant<T>(M-1,B);
	delete[] B;
	return C;
}

//get MxM adjugate
template<typename T>
T *adjugate(unsigned int M,const T *A)
{
	if(M == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	T *B = new T[M*M];
	unsigned int x = 0;
	for(unsigned int i=0; i<M; i++)
	{
		for(unsigned int j=0; j<M; j++)
		{
			B[x++] = cofactor<T>(i,j,M,A);
		}
	}
	clean(M,M,B);
	T *C = transpose<T>(M,M,B);
	delete[] B;
	return C;
}

//get MxM inverse
template<typename T>
T *inverse(unsigned int M,const T *A) //,const bool (*zero_func)(const T &t),const T (*recip_func)(const T &t))
{
	unsigned int num_elements = M*M;
	if(num_elements == 0)
	{
		throw arkhe::base::Exception("zero element matrix");
	}

	//compute determinant
	//if determinant is zero, then return zero matrix
	T det = determinant(M,A);
	if(is_zero<T>(det))
	{
		return create<T>(M,M);
	}
	//inverse = adjugate * 1/determinant
	T det_recip = get_recip<T>(det);
	T *adj = adjugate(M,A);
	T *B = multiply<T>(M,M,adj,det_recip);
	delete[] adj;
	clean<T>(M,M,B);
	return B;
}

} //namespace matrix_ops

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_MATRIXOPS_H__
