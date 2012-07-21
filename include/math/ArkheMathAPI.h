#ifndef __ARKHE_MATH_MATHAPI_H__
#define __ARKHE_MATH_MATHAPI_H__

//arkhe math includes
//general math
#include "ArkheMath.h"
#include "ArkheAngle.h"
//complex math
#include "ArkheComplex.h"
//linear algebra
//points, vectors etc.
#include "ArkheTupleN.h"
#include "ArkhePointN.h"
#include "ArkheVectorN.h"
#include "ArkhePVNM.h"
//matrices
#include "ArkheMatrixOps.h"
#include "ArkheTMatrixMN.h"
#include "ArkheTMatrixMM.h"
//lines, rays etc.
#include "ArkheRayN.h"
//polynomials etc.
#include "ArkhePolynomial.h"
//tests
#include "math_integrity_tests.h"

namespace arkhe
{

namespace math
{

//typedefs
//rays
typedef RayN<2> Ray2;
typedef RayN<3> Ray3;

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_MATHAPI_H__
