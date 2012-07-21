//arkhe math includes
#include "ArkhePVNM.h"
#include "ArkheVectorOps.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN POINT2 ///////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Point2 Point2::ZERO(0.0,0.0);
const Point2 Point2::X_AXIS(1.0,0.0);
const Point2 Point2::Y_AXIS(0.0,1.0);

Point2::Point2() : PointN<2>() {}

Point2::Point2(double x,double y) : PointN<2>()
{
	m_tuple[0] = x;
	m_tuple[1] = y;
}

Point2::Point2(const PointN<2> &p) : PointN<2>(p) {}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN POINT3 ///////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Point3 Point3::ZERO(0.0,0.0,0.0);
const Point3 Point3::X_AXIS(1.0,0.0,0.0);
const Point3 Point3::Y_AXIS(0.0,1.0,0.0);
const Point3 Point3::Z_AXIS(0.0,0.0,1.0);

Point3::Point3() : PointN<3>() {}

Point3::Point3(double x,double y,double z) : PointN<3>()
{
	m_tuple[0] = x;
	m_tuple[1] = y;
	m_tuple[2] = z;
}

Point3::Point3(const PointN<3> &p) : PointN<3>(p) {}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN VECTOR2 //////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Vector2 Vector2::ZERO(0.0,0.0);
const Vector2 Vector2::X_AXIS(1.0,0.0);
const Vector2 Vector2::Y_AXIS(0.0,1.0);

Vector2::Vector2() : VectorN<2>() {}

Vector2::Vector2(double x,double y) : VectorN<2>()
{
	m_tuple[0] = x;
	m_tuple[1] = y;
}

Vector2::Vector2(const VectorN<2> &v) : VectorN<2>(v) {}

Vector2 Vector2::perp() const
{
	Vector2 v;
	v.m_tuple = vector_ops::perp(m_tuple);
	return v;
}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN VECTOR3 //////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Vector3 Vector3::ZERO(0.0,0.0,0.0);
const Vector3 Vector3::X_AXIS(1.0,0.0,0.0);
const Vector3 Vector3::Y_AXIS(0.0,1.0,0.0);
const Vector3 Vector3::Z_AXIS(0.0,0.0,1.0);

Vector3::Vector3() : VectorN<3>() {}

Vector3::Vector3(double x,double y,double z) : VectorN<3>()
{
	m_tuple[0] = x;
	m_tuple[1] = y;
	m_tuple[2] = z;
}

Vector3::Vector3(const VectorN<3> &v) : VectorN<3>(v) {}

Vector3 Vector3::cross(const Vector3 &v) const
{
	Vector3 res;
	res.m_tuple = vector_ops::cross(3,m_tuple,v.m_tuple);
	return res;
}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN NORMAL2 //////////////////////
//////////////////////////////////////////////////////////////

Normal2::Normal2() : Vector2() {}
Normal2::Normal2(double x,double y) : Vector2(x,y) {}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN NORMAL3 //////////////////////
//////////////////////////////////////////////////////////////

Normal3::Normal3() : Vector3() {}
Normal3::Normal3(double x,double y,double z) : Vector3(x,y,z) {}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN MATRIX22 /////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Matrix22 Matrix22::ZERO(0.0,0.0,0.0,0.0);
const Matrix22 Matrix22::IDENTITY(1.0,0.0,0.0,1.0);

Matrix22::Matrix22() : TMatrixMM<2,double>() {}

Matrix22::Matrix22(double m00,double m01,double m10,double m11) : TMatrixMM<2,double>()
{
	m_matrix[0] = m00;
	m_matrix[1] = m01;
	m_matrix[2] = m10;
	m_matrix[3] = m11;
}

Matrix22::Matrix22(const TMatrixMM<2,double> &m) : TMatrixMM<2,double>(m) {}

Matrix22 &Matrix22::operator=(const TMatrixMM<2,double> &m)
{
	if(this == &m)
	{
		return *this;
	}
	this->destroy();
	m_matrix = matrix_ops::copy(2,2,m.m_matrix);
	return *this;
}

Matrix22 Matrix22::operator*(double x) const
{
	return Matrix22(matrix_ops::multiply(2,2,m_matrix,x));
}

Matrix22 Matrix22::operator*(const Matrix22 &right) const
{
	return Matrix22(matrix_ops::multiply(2,2,m_matrix,2,2,right.m_matrix));
}

Point2 Matrix22::operator*(const Point2 &p) const
{
	return Point2
	(
		m_matrix[0]*p[0] + m_matrix[1]*p[1],
		m_matrix[2]*p[0] + m_matrix[3]*p[1]
	);
}

Vector2 Matrix22::operator*(const Vector2 &v) const
{
	return Vector2
	(
		m_matrix[0]*v[0] + m_matrix[1]*v[1],
		m_matrix[2]*v[0] + m_matrix[3]*v[1]
	);
}

Normal2 Matrix22::operator*(const Normal2 &n) const
{
	double *tr_inv = matrix_ops::transpose(2,2,m_matrix);
	Normal2 res
	(
		tr_inv[0]*n[0] + tr_inv[1]*n[1],
		tr_inv[2]*n[0] + tr_inv[3]*n[1]
	);
	delete[] tr_inv;
	return res;
}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN MATRIX33 /////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Matrix33 Matrix33::ZERO
(
	0.0,0.0,0.0,
	0.0,0.0,0.0,
	0.0,0.0,0.0
);
const Matrix33 Matrix33::IDENTITY
(
	1.0,0.0,0.0,
	0.0,1.0,0.0,
	0.0,0.0,1.0
);

Matrix33::Matrix33() : TMatrixMM<3,double>() {}

Matrix33::Matrix33
(
	double m00,double m01,double m02,
	double m10,double m11,double m12,
	double m20,double m21,double m22
) : TMatrixMM<3,double>()
{
	m_matrix[0] = m00;
	m_matrix[1] = m01;
	m_matrix[2] = m02;
	m_matrix[3] = m10;
	m_matrix[4] = m11;
	m_matrix[5] = m12;
	m_matrix[6] = m20;
	m_matrix[7] = m21;
	m_matrix[8] = m22;
}

Matrix33::Matrix33(const TMatrixMM<3,double> &m) : TMatrixMM<3,double>(m) {}

Matrix33 &Matrix33::operator=(const TMatrixMM<3,double> &m)
{
	if(this == &m)
	{
		return *this;
	}
	this->destroy();
	m_matrix = matrix_ops::copy(3,3,m.m_matrix);
	return *this;
}

Matrix33 Matrix33::operator*(double x) const
{
	return Matrix33(matrix_ops::multiply(3,3,m_matrix,x));
}

Matrix33 Matrix33::operator*(const Matrix33 &right) const
{
	return Matrix33(matrix_ops::multiply(3,3,m_matrix,3,3,right.m_matrix));
}

Point3 Matrix33::operator*(const Point3 &p) const
{
	return Point3
	(
		m_matrix[0]*p[0] + m_matrix[1]*p[1] + m_matrix[2]*p[2],
		m_matrix[3]*p[0] + m_matrix[4]*p[1] + m_matrix[5]*p[2],
		m_matrix[6]*p[0] + m_matrix[7]*p[1] + m_matrix[8]*p[2]
	);
}

Vector3 Matrix33::operator*(const Vector3 &v) const
{
	return Vector3
	(
		m_matrix[0]*v[0] + m_matrix[1]*v[1] + m_matrix[2]*v[2],
		m_matrix[3]*v[0] + m_matrix[4]*v[1] + m_matrix[5]*v[2],
		m_matrix[6]*v[0] + m_matrix[7]*v[1] + m_matrix[8]*v[2]
	);
}

Normal3 Matrix33::operator*(const Normal3 &n) const
{
	double *tr_inv = matrix_ops::transpose(3,3,m_matrix);
	Normal3 res
	(
		tr_inv[0]*n[0] + tr_inv[1]*n[1] + tr_inv[2]*n[2],
		tr_inv[3]*n[0] + tr_inv[4]*n[1] + tr_inv[5]*n[2],
		tr_inv[6]*n[0] + tr_inv[7]*n[1] + tr_inv[8]*n[2]
	);
	delete[] tr_inv;
	return res;
}

//////////////////////////////////////////////////////////////
///////////////////////// BEGIN MATRIX44 /////////////////////
//////////////////////////////////////////////////////////////

//static variable definitions
const Matrix44 Matrix44::ZERO
(
	0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0
);
const Matrix44 Matrix44::IDENTITY
(
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0
);

Matrix44::Matrix44() : TMatrixMM<4,double>() {}

Matrix44::Matrix44
(
	double m00,double m01,double m02,double m03,
	double m10,double m11,double m12,double m13,
	double m20,double m21,double m22,double m23,
	double m30,double m31,double m32,double m33
) : TMatrixMM<4,double>()
{
	m_matrix[0] = m00;
	m_matrix[1] = m01;
	m_matrix[2] = m02;
	m_matrix[3] = m03;
	m_matrix[4] = m10;
	m_matrix[5] = m11;
	m_matrix[6] = m12;
	m_matrix[7] = m13;
	m_matrix[8] = m20;
	m_matrix[9] = m21;
	m_matrix[10] = m22;
	m_matrix[11] = m23;
	m_matrix[12] = m30;
	m_matrix[13] = m31;
	m_matrix[14] = m32;
	m_matrix[15] = m33;
}

Matrix44::Matrix44(const TMatrixMM<4,double> &m) : TMatrixMM<4,double>(m) {}

Matrix44 &Matrix44::operator=(const TMatrixMM<4,double> &m)
{
	if(this == &m)
	{
		return *this;
	}
	this->destroy();
	m_matrix = matrix_ops::copy(4,4,m.m_matrix);
	return *this;
}

Matrix44 Matrix44::operator*(double x) const
{
	return Matrix44(matrix_ops::multiply(4,4,m_matrix,x));
}

Matrix44 Matrix44::operator*(const Matrix44 &right) const
{
	return Matrix44(matrix_ops::multiply(4,4,m_matrix,4,4,right.m_matrix));
}

Point3 Matrix44::operator*(const Point3 &p) const
{
	return Point3
	(
		m_matrix[0]*p[0] + m_matrix[1]*p[1] + m_matrix[2]*p[2] + m_matrix[3],
		m_matrix[4]*p[0] + m_matrix[5]*p[1] + m_matrix[6]*p[2] + m_matrix[7],
		m_matrix[8]*p[0] + m_matrix[9]*p[1] + m_matrix[10]*p[2] + m_matrix[11]
	);
}

Vector3 Matrix44::operator*(const Vector3 &v) const
{
	return Vector3
	(
		m_matrix[0]*v[0] + m_matrix[1]*v[1] + m_matrix[2]*v[2],
		m_matrix[4]*v[0] + m_matrix[5]*v[1] + m_matrix[6]*v[2],
		m_matrix[8]*v[0] + m_matrix[9]*v[1] + m_matrix[10]*v[2]
	);
}

Normal3 Matrix44::operator*(const Normal3 &n) const
{
	double *tr_inv = matrix_ops::transpose(4,4,m_matrix);
	Normal3 res
	(
		tr_inv[0]*n[0] + tr_inv[1]*n[1] + tr_inv[2]*n[2],
		tr_inv[4]*n[0] + tr_inv[5]*n[1] + tr_inv[6]*n[2],
		tr_inv[8]*n[0] + tr_inv[9]*n[1] + tr_inv[10]*n[2]
	);
	delete[] tr_inv;
	return res;
}

} //namespace math

} //namespace arkhe
