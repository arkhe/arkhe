#ifndef __ARKHE_MATH_PVNM_H__
#define __ARKHE_MATH_PVNM_H__

//arkhe math includes
#include "ArkhePointN.h"
#include "ArkheVectorN.h"
#include "ArkheTMatrixMM.h"

namespace arkhe
{

namespace math
{

class Point2 : public PointN<2>
{
public:
	//constructors
	Point2();
	Point2(double x,double y);
	Point2(const PointN<2> &p);
	//static variables
	static const Point2 ZERO;
	static const Point2 X_AXIS;
	static const Point2 Y_AXIS;
}; //class Point2

class Point3 : public PointN<3>
{
public:
	//constructors
	Point3();
	Point3(double x,double y,double z);
	Point3(const PointN<3> &p);
	//static variables
	static const Point3 ZERO;
	static const Point3 X_AXIS;
	static const Point3 Y_AXIS;
	static const Point3 Z_AXIS;
}; //class Point3

class Vector2 : public VectorN<2>
{
public:
	//constructors
	Vector2();
	Vector2(double x,double y);
	Vector2(const VectorN<2> &v);
	//methods
	Vector2 perp() const;
	//static variables
	static const Vector2 ZERO;
	static const Vector2 X_AXIS;
	static const Vector2 Y_AXIS;
}; //class Vector2

class Vector3 : public VectorN<3>
{
public:
	//constructors
	Vector3();
	Vector3(double x,double y,double z);
	Vector3(const VectorN<3> &v);
	//methods
	Vector3 cross(const Vector3 &v) const;
	//static variables
	static const Vector3 ZERO;
	static const Vector3 X_AXIS;
	static const Vector3 Y_AXIS;
	static const Vector3 Z_AXIS;
}; //class Vector3

class Normal2 : public Vector2
{
public:
	//constructors
	Normal2();
	Normal2(double x,double y);
}; //class Normal2

class Normal3 : public Vector3
{
public:
	//constructors
	Normal3();
	Normal3(double x,double y,double z);
}; //class Normal2

class Matrix22 : public TMatrixMM<2,double>
{
public:
	//constructor
	Matrix22();
	Matrix22(double m00,double m01,double m10,double m11);
	Matrix22(const TMatrixMM<2,double> &m);
	//operators
	Matrix22 &operator=(const TMatrixMM<2,double> &m);
	Matrix22 operator*(double x) const;
	Matrix22 operator*(const Matrix22 &right) const;
	Point2 operator*(const Point2 &p) const;
	Vector2 operator*(const Vector2 &v) const;
	Normal2 operator*(const Normal2 &n) const;
	//static variables
	static const Matrix22 ZERO;
	static const Matrix22 IDENTITY;
}; //class Matrix22

class Matrix33 : public TMatrixMM<3,double>
{
public:
	//constructor
	Matrix33();
	Matrix33
	(
		double m00,double m01,double m02,
		double m10,double m11,double m12,
		double m20,double m21,double m22
	);
	Matrix33(const TMatrixMM<3,double> &m);
	//operators
	Matrix33 &operator=(const TMatrixMM<3,double> &m);
	Matrix33 operator*(double x) const;
	Matrix33 operator*(const Matrix33 &right) const;
	Point3 operator*(const Point3 &p) const;
	Vector3 operator*(const Vector3 &v) const;
	Normal3 operator*(const Normal3 &n) const;
	//static variables
	static const Matrix33 ZERO;
	static const Matrix33 IDENTITY;
}; //class Matrix33

class Matrix44 : public TMatrixMM<4,double>
{
public:
	//constructor
	Matrix44();
	Matrix44
	(
		double m00,double m01,double m02,double m03,
		double m10,double m11,double m12,double m13,
		double m20,double m21,double m22,double m23,
		double m30,double m31,double m32,double m33
	);
	Matrix44(const TMatrixMM<4,double> &m);
	//operators
	Matrix44 &operator=(const TMatrixMM<4,double> &m);
	Matrix44 operator*(double x) const;
	Matrix44 operator*(const Matrix44 &right) const;
	Point3 operator*(const Point3 &p) const;
	Vector3 operator*(const Vector3 &v) const;
	Normal3 operator*(const Normal3 &n) const;
	//static variables
	static const Matrix44 ZERO;
	static const Matrix44 IDENTITY;
}; //class Matrix44

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_PVNM_H__
