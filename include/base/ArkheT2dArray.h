#ifndef __ARKHE_BASE_T2DARRAY_H__
#define __ARKHE_BASE_T2DARRAY_H__

//arkhe base includes
#include "ArkheTArray.h"
#include "ArkheException.h"

namespace arkhe
{

namespace base
{

//2d array. indices start at zero.
template<typename T>
class T2dArray : public TArray<T>
{
public:
	//constructors
	T2dArray() : m_rows(0),m_cols(0),TArray<T>() {}
	T2dArray(unsigned int rows,unsigned int cols) : m_rows(rows),m_cols(cols),TArray<T>(rows*cols) {}; //if rows and/or cols is zero, then we have an empty array
	//destructor
	~T2dArray() {}
	//operators
	T operator()(unsigned int i,unsigned int j) const;
	T &operator()(unsigned int i,unsigned int j);
private:
	//variables
	unsigned int m_rows;
	unsigned int m_cols;
protected:
	//
}; //class T2dArray

template<typename T> T T2dArray<T>::operator()(unsigned int i,unsigned int j) const
{
	if(i >= m_rows || j >= m_cols) //unsigned int so cannot be < 0
	{
		throw Exception("index out of range");
	}
	return *(&m_data[(i * m_cols) + j]);
}

template<typename T> T &T2dArray<T>::operator()(unsigned int i,unsigned int j)
{
	if(i >= m_rows || j >= m_cols) //unsigned int so cannot be < 0
	{
		throw Exception("index out of range");
	}
	return *(&m_data[(i * m_cols) + j]);
}

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_T2DARRAY_H__
