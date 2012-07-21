#ifndef __ARKHE_BASE_TARRAY_H__
#define __ARKHE_BASE_TARRAY_H__

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace base
{

//1d array. indices start at zero.
template<typename T>
class TArray
{
public:
	//constructors
	TArray() : m_data(0),m_size(0) {};
	TArray(unsigned int size);
	TArray(const TArray<T> &copy);
	//destructor
	virtual ~TArray();
	//operators
	TArray<T> &operator=(const TArray<T> &copy);
	virtual T operator()(unsigned int i) const;
	virtual T &operator()(unsigned int i);
	//methods
	virtual void clear();
	virtual unsigned int size() const { return m_size; }
private:
	//
protected:
	//variables
	T *m_data;
	unsigned int m_size;
}; //class TArray

template<typename T> TArray<T>::TArray(unsigned int size)
{
	if(size > 0)
	{
		m_data = new T[size];
		m_size = size;
	}
	else
	{
		m_data = 0;
		m_size = 0;
	}
}

template<typename T> TArray<T>::TArray(const TArray<T> &copy)
{
	if(copy.m_data != 0)
	{
		this->m_data = new T[copy.m_size];
		this->m_size = copy.m_size;
		for(unsigned int i=0; i<m_size; i++)
		{
			*(this->m_data[i]) = *(copy.m_data[i]);
		}
	}
	else
	{
		this->m_data = 0;
		this->m_size = 0;
	}
}

template<typename T> TArray<T>::~TArray()
{
	if(m_data != 0)
	{
		delete[] m_data;
	}
	m_data = 0;
	m_size = 0;
}

template<typename T> TArray<T> &TArray<T>::operator=(const TArray<T> &copy)
{
	delete [] m_data;
	if(copy.m_data != 0)
	{
		this->m_data = new T[copy.m_size];
		this->m_size = copy.m_size;
		for(unsigned int i=0; i<m_size; i++)
		{
			*(this->m_data[i]) = *(copy.m_data[i]);
		}
	}
	else
	{
		this->m_data = 0;
		this->m_size = 0;
	}
	return *this;
}

template<typename T> T TArray<T>::operator()(unsigned int i) const
{
	if(i >= m_size)
	{
		throw Exception("index out of range");
	}
	return *(&m_data[i]);
}

template<typename T> T &TArray<T>::operator()(unsigned int i)
{
	if(i >= m_size)
	{
		throw Exception("index out of range");
	}
	return *(&m_data[i]);
}

//clear the contents of the array
template<typename T> void TArray<T>::clear()
{
	if(m_data != 0)
	{
		delete[] m_data;
		m_data = 0;
		m_size = 0;
	}
}

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_TARRAY_H__
