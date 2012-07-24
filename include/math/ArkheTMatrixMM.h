#ifndef __ARKHE_MATH_TMATRIXMM_H__
#define __ARKHE_MATH_TMATRIXMM_H__

//arkhe math includes
#include "ArkheMatrixOps.h"

namespace arkhe
{

namespace math
{

//forward declarations
class Matrix22;
class Matrix33;
class Matrix44;

//square MxM (row-column order) matrix
template<unsigned int M,typename T>
class TMatrixMM
{
public:
	//enums
	enum Inverse
	{
		COFACTOR,
		GAUSS_JORDAN
	}; //enum Inverse
	//friends
	friend Matrix22;
	friend Matrix33;
	friend Matrix44;
	//constructors
	TMatrixMM();
	TMatrixMM(T *matrix);
	TMatrixMM(const std::vector<std::vector<T>> &elements);
	TMatrixMM(const TMatrixMM &copy);
	//destructor
	virtual ~TMatrixMM();
	//operators
	TMatrixMM &operator=(const TMatrixMM &copy);
	operator T*();
	T operator()(unsigned int i,unsigned int j) const;
	T &operator()(unsigned int i,unsigned int j);
	TMatrixMM operator+(const TMatrixMM &right) const;
	TMatrixMM &operator+=(const TMatrixMM &right);
	TMatrixMM operator-() const;
	TMatrixMM operator-(const TMatrixMM &right) const;
	TMatrixMM &operator-=(const TMatrixMM &right);
	TMatrixMM operator*(const T &t) const;
	TMatrixMM operator*(const TMatrixMM &right) const;
	TMatrixMM &operator*=(const T &t);
	TMatrixMM &operator*=(const TMatrixMM &right);
	TMatrixMM operator/(const T &t) const;
	TMatrixMM &operator/=(const T &t);
	bool operator==(const TMatrixMM &right) const;
	bool operator!=(const TMatrixMM &right) const;
	//friend operators
	template<unsigned int M,typename T> friend std::ostream &operator<<(std::ostream &out,const TMatrixMM<M,T> &m);
	//methods
	void clean();
	bool zero() const;
	T min_element() const;
	T max_element() const;
	TMatrixMM transpose() const;
	T trace() const;
	TMatrixMM lower() const;
	TMatrixMM upper() const;
	T determinant() const;
	TMatrixMM adjugate() const;
	TMatrixMM inverse(Inverse i=COFACTOR) const;
private:
	//
protected:
	//methods
	void destroy();
	//variables
	T *m_matrix;
}; //class TMatrixMM

//construct MxM zero matrix
template<unsigned int M,typename T>
TMatrixMM<M,T>::TMatrixMM()
{
	m_matrix = matrix_ops::create<T>(M,M);
}

//construct matrix from array
//matrix takes ownership of the data
//note that the array passed in is assumed
//to be of size m_rows*m_cols.
template<unsigned int M,typename T>
TMatrixMM<M,T>::TMatrixMM(T *matrix)
{
	if(matrix == 0)
	{
		throw arkhe::base::Exception("cannot construct matrix with zero elements");
	}
	m_matrix = matrix;
}

//construct a matrix from the given vector of vectors
//the outer vector contains the rows
//so it is in order row/column
template<unsigned int M,typename T>
TMatrixMM<M,T>::TMatrixMM(const std::vector<std::vector<T> > &elements)
{
	m_matrix = matrix_ops::create(elements,m_rows,m_cols);
}

//copy constructor
template<unsigned int M,typename T>
TMatrixMM<M,T>::TMatrixMM(const TMatrixMM<M,T> &copy)
{
	m_matrix = matrix_ops::copy(M,M,copy.m_matrix);
}

//destructor
template<unsigned int M,typename T>
TMatrixMM<M,T>::~TMatrixMM()
{
	if(m_matrix)
	{
		delete[] m_matrix;
	}
}

//assignment operator
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator=(const TMatrixMM<M,T> &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	destroy();
	m_matrix = matrix_ops::copy(M,M,copy.m_matrix);
	return *this;
}

//get pointer to matrix array
template<unsigned int M,typename T>
TMatrixMM<M,T>::operator T*()
{
	return &m_matrix[0];
}

//get element at index (i,j)
template<unsigned int M,typename T>
T TMatrixMM<M,T>::operator()(unsigned int i,unsigned int j) const
{
	return *(&m_matrix[matrix_ops::index<T>(i,j,M,M)]);
}

//get element at index (i,j)
template<unsigned int M,typename T>
T &TMatrixMM<M,T>::operator()(unsigned int i,unsigned int j)
{
	return *(&m_matrix[matrix_ops::index<T>(i,j,M,M)]);
}

//add two matrices
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator+(const TMatrixMM<M,T> &right) const
{
	return TMatrixMM<M,T>(matrix_ops::add(M,M,m_matrix,M,M,right.m_matrix));
}

//add matrix to self
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator+=(const TMatrixMM<M,T> &right)
{
	T *matrix = matrix_ops::add(M,M,m_matrix,M,M,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//negate matrix
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator-() const
{
	return TMatrixMM<M,T>(matrix_ops::negate(M,M,m_matrix));
}

//subtract two matrices
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator-(const TMatrixMM<M,T> &right) const
{
	return TMatrixMM<M,T>(matrix_ops::subtract(M,M,m_matrix,M,M,right.m_matrix));
}

//subtract matrix from self
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator-=(const TMatrixMM<M,T> &right)
{
	T *matrix = matrix_ops::subtract(M,M,m_matrix,M,M,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//multiply matrix by value
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator*(const T &t) const
{
	return TMatrixMM<M,T>(matrix_ops::multiply(M,M,m_matrix,t));
}

//multiply two matrices
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator*(const TMatrixMM<M,T> &right) const
{
	return TMatrixMM<M,T>(matrix_ops::multiply(M,M,m_matrix,M,M,right.m_matrix));
}

//multiply self by value
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator*=(const T &t)
{
	T *matrix = matrix_ops::multiply(M,M,m_matrix,t);
	destroy();
	m_matrix = matrix;
	return *this;
}

//multiply self by matrix
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator*=(const TMatrixMM<M,T> &right)
{
	T *matrix = matrix_ops::multiply(M,M,m_matrix,M,M,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//divide matrix by value
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::operator/(const T &t) const
{
	return TMatrixMM<M,T> m(matrix_ops::divide(M,M,m_matrix,t));
}

//divide self by value
template<unsigned int M,typename T>
TMatrixMM<M,T> &TMatrixMM<M,T>::operator/=(const T &t)
{
	T *matrix = matrix_ops::divide(M,M,m_matrix,t);
	destroy();
	m_matrix = matrix;
	return *this;
}

//are two matrices equal
template<unsigned int M,typename T>
bool TMatrixMM<M,T>::operator==(const TMatrixMM<M,T> &right) const
{
	return matrix_ops::equal(M,M,m_matrix,right.m_matrix);
}

//are two matrices not equal
template<unsigned int M,typename T>
bool TMatrixMM<M,T>::operator!=(const TMatrixMM<M,T> &right) const
{
	return !matrix_ops::equal(M,M,m_matrix,right.m_matrix);
}

//stream output
template<unsigned int M,typename T>
std::ostream &operator<<(std::ostream &out,const TMatrixMM<M,T> &m)
{
	return matrix_ops::stream_out(M,M,m.m_matrix,out);
}

//set near-zero elements to zero
template<unsigned int M,typename T>
void TMatrixMM<M,T>::clean()
{
	matrix_ops::clean(M,M,m_matrix);
}

//is this a zero matrix?
template<unsigned int M,typename T>
bool TMatrixMM<M,T>::zero() const
{
	return matrix_ops::zero<T>(M,M,m_matrix);
}

template<unsigned int M,typename T> T TMatrixMM<M,T>::min_element() const { return matrix_ops::min_element<T>(M,M,m_matrix); }
template<unsigned int M,typename T> T TMatrixMM<M,T>::max_element() const { return matrix_ops::max_element<T>(M,M,m_matrix); }

//get transpose
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::transpose() const
{
	return TMatrixMM<M,T>(matrix_ops::transpose(M,M,m_matrix));
}

//get trace
template<unsigned int M,typename T>
T TMatrixMM<M,T>::trace() const
{
	return matrix_ops::trace(M,m_matrix);
}

//get lower trianglular matrix
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::lower() const
{
	return TMatrixMM<M,T>(matrix_ops::LU_decomposition<T>(M,m_matrix,matrix_ops::LU_LOWER));
}

//get upper triangular matrix
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::upper() const
{
	return TMatrixMM<M,T>(matrix_ops::LU_decomposition<T>(M,m_matrix,matrix_ops::LU_UPPER));
}

//get determinant
template<unsigned int M,typename T>
T TMatrixMM<M,T>::determinant() const
{
	return matrix_ops::determinant<T>(M,m_matrix);
}

//get adjugate
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::adjugate() const
{
	return TMatrixMM<M,T>(matrix_ops::adjugate(M,m_matrix));
}

//get inverse
template<unsigned int M,typename T>
TMatrixMM<M,T> TMatrixMM<M,T>::inverse(Inverse i) const
{
	if(i == TMatrixMM<M,T>::COFACTOR)
	{
		return TMatrixMM<M,T>(matrix_ops::inverse<T>(M,m_matrix));
	}
	//use Gauss-Jordan elimination
	return TMatrixMM<M,T>(matrix_ops::gauss_jordan_elimination<T>(M,m_matrix));
}

//destroy this matrix
template<unsigned int M,typename T>
void TMatrixMM<M,T>::destroy()
{
	if(m_matrix)
	{
		delete[] m_matrix;
		m_matrix = 0;
	}
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_TMATRIXMM_H__
