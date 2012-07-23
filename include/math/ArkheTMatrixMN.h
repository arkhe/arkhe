#ifndef __ARKHE_MATH_TMATRIXMN_H__
#define __ARKHE_MATH_TMATRIXMN_H__

//arkhe math includes
#include "ArkheMatrixOps.h"

//std includes
#include <vector>
#include <ostream>

namespace arkhe
{

namespace math
{

//MxN (row-column order) matrix
template<typename T>
class TMatrixMN
{
public:
	//constructors
	TMatrixMN() : m_rows(0),m_cols(0),m_matrix(0) {}
	TMatrixMN(unsigned int rows,unsigned int cols);
	TMatrixMN(T *matrix);
	TMatrixMN(T *matrix,unsigned int rows,unsigned int cols);
	TMatrixMN(const std::vector<std::vector<T>> &elements);
	TMatrixMN(const TMatrixMN &copy);
	//destructor
	virtual ~TMatrixMN();
	//operators
	TMatrixMN &operator=(const TMatrixMN &copy);
	operator T*();
	T operator()(unsigned int i,unsigned int j) const;
	T &operator()(unsigned int i,unsigned int j);
	TMatrixMN operator+(const TMatrixMN &right) const;
	TMatrixMN &operator+=(const TMatrixMN &right);
	TMatrixMN operator-() const;
	TMatrixMN operator-(const TMatrixMN &right) const;
	TMatrixMN &operator-=(const TMatrixMN &right);
	TMatrixMN operator*(const T &t) const;
	TMatrixMN operator*(const TMatrixMN &right) const;
	TMatrixMN &operator*=(const T &t);
	TMatrixMN &operator*=(const TMatrixMN &right);
	TMatrixMN operator/(const T &t) const;
	TMatrixMN &operator/=(const T &t);
	bool operator==(const TMatrixMN &right) const;
	bool operator!=(const TMatrixMN &right) const;
	//friend operators
	template<typename T> friend std::ostream &operator<<(std::ostream &out,const TMatrixMN<T> &m);
	//methods
	TMatrixMN transpose() const;
private:
	//
protected:
	//methods
	void destroy();
	//variables
	T *m_matrix;
	unsigned int m_rows;
	unsigned int m_cols;
}; //class TMatrixMN

//construct MxM zero matrix
template<typename T>
TMatrixMN<T>::TMatrixMN(unsigned int rows,unsigned int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_matrix = matrix_ops::create<T>(rows,cols);
}

//construct matrix from array
//matrix takes ownership of the data
//note that the array passed in is assumed
//to be of size m_rows*m_cols.
template<typename T>
TMatrixMN<T>::TMatrixMN(T *matrix)
{
	if(matrix == 0)
	{
		throw arkhe::base::Exception("cannot construct matrix with zero elements");
	}
	m_matrix = matrix;
}

//same as above, except we also set the number of rows
//and columns of the matrix
template<typename T>
TMatrixMN<T>::TMatrixMN(T *matrix,unsigned int rows,unsigned int cols)
{
	if(matrix == 0)
	{
		throw arkhe::base::Exception("cannot construct matrix with zero elements");
	}
	m_matrix = matrix;
	m_rows = rows;
	m_cols = cols;
}

//construct a matrix from the given vector of vectors
//the outer vector contains the rows
//so it is in order row/column
template<typename T>
TMatrixMN<T>::TMatrixMN(const std::vector<std::vector<T> > &elements)
{
	m_matrix = matrix_ops::create(elements,m_rows,m_cols);
}

//copy constructor
template<typename T>
TMatrixMN<T>::TMatrixMN(const TMatrixMN<T> &copy)
{
	m_rows = copy.m_rows;
	m_cols = copy.m_cols;
	m_matrix = matrix_ops::copy(m_rows,m_cols,copy.m_matrix);
}

//destructor
template<typename T>
TMatrixMN<T>::~TMatrixMN()
{
	if(m_matrix)
	{
		delete[] m_matrix;
	}
}

//assignment operator
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator=(const TMatrixMN<T> &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	destroy();
	m_rows = copy.m_rows;
	m_cols = copy.m_cols;
	m_matrix = matrix_ops::copy(m_rows,m_cols,copy.m_matrix);
	return *this;
}

//get pointer to matrix array
template<typename T>
TMatrixMN<T>::operator T*()
{
	return &m_matrix[0];
}

//get element at index (i,j)
template<typename T>
T TMatrixMN<T>::operator()(unsigned int i,unsigned int j) const
{
	return *(&m_matrix[matrix_ops::index<T>(i,j,m_rows,m_cols)]);
}

//get element at index (i,j)
template<typename T>
T &TMatrixMN<T>::operator()(unsigned int i,unsigned int j)
{
	return *(&m_matrix[matrix_ops::index<T>(i,j,m_rows,m_cols)]);
}

//add two matrices
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator+(const TMatrixMN<T> &right) const
{
	TMatrixMN<T> m(matrix_ops::add(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix));
	m.m_rows = m_rows;
	m.m_cols = m_cols;
	return m;
}

//add matrix to self
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator+=(const TMatrixMN<T> &right)
{
	T *matrix = matrix_ops::add(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//negate matrix
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator-() const
{
	TMatrixMN<T> m(matrix_ops::negate(m_rows,m_cols,m_matrix));
	m.m_rows = m_rows;
	m.m_cols = m_cols;
	return m;
}

//subtract two matrices
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator-(const TMatrixMN<T> &right) const
{
	TMatrixMN<T> m(matrix_ops::subtract(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix));
	m.m_rows = m_rows;
	m.m_cols = m_cols;
	return m;
}

//subtract matrix from self
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator-=(const TMatrixMN<T> &right)
{
	T *matrix = matrix_ops::subtract(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//multiply matrix by value
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator*(const T &t) const
{
	TMatrixMN<T> m(matrix_ops::multiply(m_rows,m_cols,m_matrix,t));
	m.m_rows = m_rows;
	m.m_cols = m_cols;
	return m;
}

//multiply two matrices
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator*(const TMatrixMN<T> &right) const
{
	TMatrixMN<T> m(matrix_ops::multiply(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix));
	m.m_rows = m_rows;
	m.m_cols = right.m_cols;
	return m;
}

//multiply self by value
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator*=(const T &t)
{
	T *matrix = matrix_ops::multiply(m_rows,m_cols,m_matrix,t);
	destroy();
	m_matrix = matrix;
	return *this;
}

//multiply self by matrix
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator*=(const TMatrixMN<T> &right)
{
	T *matrix = matrix_ops::multiply(m_rows,m_cols,m_matrix,right.m_rows,right.m_cols,right.m_matrix);
	destroy();
	m_matrix = matrix;
	return *this;
}

//divide matrix by value
template<typename T>
TMatrixMN<T> TMatrixMN<T>::operator/(const T &t) const
{
	TMatrixMN<T> m(matrix_ops::divide(m_rows,m_cols,m_matrix,t));
	m.m_rows = m_rows;
	m.m_cols = m_cols;
	return m;
}

//divide self by value
template<typename T>
TMatrixMN<T> &TMatrixMN<T>::operator/=(const T &t)
{
	T *matrix = matrix_ops::divide(m_rows,m_cols,m_matrix,t);
	destroy();
	m_matrix = matrix;
	return *this;
}

//are two matrices equal
template<typename T>
bool TMatrixMN<T>::operator==(const TMatrixMN<T> &right) const
{
	return matrix_ops::equal(m_rows,m_cols,m_matrix,right.m_matrix);
}

//are two matrices not equal
template<typename T>
bool TMatrixMN<T>::operator!=(const TMatrixMN<T> &right) const
{
	return !matrix_ops::equal(m_rows,m_cols,m_matrix,right.m_matrix);
}

//stream output
template<typename T>
std::ostream &operator<<(std::ostream &out,const TMatrixMN<T> &m)
{
	return matrix_ops::stream_out(m.m_rows,m.m_cols,m.m_matrix,out);
}

//get transpose
template<typename T>
TMatrixMN<T> TMatrixMN<T>::transpose() const
{
	return TMatrixMN<T>(matrix_ops::transpose(m_rows,m_cols,m_matrix),m_cols,m_rows);
}

//destroy this matrix
template<typename T>
void TMatrixMN<T>::destroy()
{
	if(m_matrix)
	{
		delete[] m_matrix;
		m_matrix = 0;
		m_rows = m_cols = 0;
	}
}

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_TMATRIXMN_H__
