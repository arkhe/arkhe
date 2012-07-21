#ifndef __ARKHE_MATH_VECTOROPS_H__
#define __ARKHE_MATH_VECTOROPS_H__

//std includes
#include <ostream>

namespace arkhe
{

namespace math
{

namespace vector_ops
{

//these methods assume that the dynamically allocated memory that they
//create will be claimed by their callers and so do not keep track of this memory.

double *create(unsigned int N);
double *copy(unsigned int N,const double *A);
double *add(unsigned int N,const double *A,const double *B);
double *negate(unsigned int N,const double *A);
double *subtract(unsigned int N,const double *A,const double *B);
double *multiply(unsigned int N,const double *A,double x);
double *divide(unsigned int N,const double *A,double x);
bool equal(unsigned int N,const double *A,const double *B);
std::ostream &stream_out(unsigned int N,const double *A,std::ostream &out);
void clean(unsigned int N,double *A);
bool is_zero(unsigned int N,double *A);
double dot(unsigned int N,const double *A,const double *B);
double len_sq(unsigned int N,const double *A);
double len(unsigned int N,const double *A);
double *normalize(unsigned int N,const double *A);
double *perp(const double *A);
double *perpendicular_to(unsigned int N,const double *A,const double *B);
double *parallel_to(unsigned int N,const double *A,const double *B);
double dist_sq(unsigned int N,const double *A,const double *B);
double dist(unsigned int N,const double *A,const double *B);
double *cross(unsigned int N,const double *A,const double *B);

} //namespace vector_ops

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_VECTOROPS_H__
