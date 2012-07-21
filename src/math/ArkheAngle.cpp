//arkhe math includes
#include "ArkheAngle.h"
#include "ArkheMath.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//static variable definitions
const Angle Angle::ZERO(0.0);
const Angle Angle::PI(Math::PI);
const Angle Angle::HALF_PI(Math::HALF_PI);
const Angle Angle::TWO_PI(Math::TWO_PI);

Angle::Angle(const Angle &copy)
{
	m_angle = copy.m_angle;
	m_unit = copy.m_unit;
}

Angle &Angle::operator=(const Angle &copy)
{
	if(this == &copy)
	{
		return *this;
	}
	m_angle = copy.m_angle;
	m_unit = copy.m_unit;
	return *this;
}

Angle Angle::operator+(const double scalar) const { return Angle(m_angle + scalar,m_unit); }

Angle Angle::operator+(const Angle &right) const
{
	return Angle(m_angle + right.as(m_unit),m_unit);
}

Angle &Angle::operator+=(const double scalar)
{
	m_angle += scalar;
	return *this;
}

Angle &Angle::operator+=(const Angle &right)
{
	m_angle += right.as(m_unit);
	return *this;
}

Angle Angle::operator-() const
{
	return Angle(-m_angle,m_unit);
}

Angle Angle::operator-(const double scalar) const { return Angle(m_angle - scalar,m_unit); }

Angle Angle::operator-(const Angle &right) const
{
	return Angle(m_angle - right.as(m_unit),m_unit);
}

Angle &Angle::operator-=(const double scalar)
{
	m_angle -= scalar;
	return *this;
}

Angle &Angle::operator-=(const Angle &right)
{
	m_angle -= right.as(m_unit);
	return *this;
}

Angle Angle::operator*(const double scalar) const { return Angle(m_angle * scalar,m_unit); }

Angle Angle::operator*(const Angle &right) const
{
	return Angle(m_angle * right.as(m_unit),m_unit);
}

Angle &Angle::operator*=(const double scalar)
{
	m_angle *= scalar;
	return *this;
}

Angle &Angle::operator*=(const Angle &right)
{
	m_angle *= right.as(m_unit);
	return *this;
}

Angle Angle::operator/(const double scalar) const
{
	if(Math::isZero(scalar))
	{
		throw arkhe::base::Exception("division by zero");
	}
	return Angle(m_angle / scalar,m_unit);
}

Angle Angle::operator/(const Angle &right) const
{
	double val = right.as(m_unit);
	if(Math::isZero(val))
	{
		throw arkhe::base::Exception("division by zero");
	}
	return Angle(m_angle / val,m_unit);
}

Angle &Angle::operator/=(const double scalar)
{
	if(Math::isZero(scalar))
	{
		throw arkhe::base::Exception("division by zero");
	}
	m_angle /= scalar;
	return *this;
}

Angle &Angle::operator/=(const Angle &right)
{
	double val = right.as(m_unit);
	if(Math::isZero(val))
	{
		throw arkhe::base::Exception("division by zero");
	}
	m_angle /= val;
	return *this;
}

bool Angle::operator==(const double scalar) const { return Math::equal(m_angle,scalar); }

bool Angle::operator==(const Angle &right) const
{
	return Math::equal(m_angle,right.as(m_unit));
}

bool Angle::operator!=(const double scalar) const { return !Math::equal(m_angle,scalar); }

bool Angle::operator!=(const Angle &right) const
{
	return !Math::equal(m_angle,right.as(m_unit));
}

bool Angle::operator<(const double scalar) const { return m_angle < scalar; }

bool Angle::operator<(const Angle &right) const
{
	return m_angle < right.as(m_unit);
}

bool Angle::operator<=(const double scalar) const { return m_angle <= scalar; }

bool Angle::operator<=(const Angle &right) const
{
	return m_angle <= right.as(m_unit);
}

bool Angle::operator>(const double scalar) const { return m_angle > scalar; }

bool Angle::operator>(const Angle &right) const
{
	return m_angle > right.as(m_unit);
}

bool Angle::operator>=(const double scalar) const { return m_angle >= scalar; }

bool Angle::operator>=(const Angle &right) const
{
	return m_angle >= right.as(m_unit);
}

std::ostream &operator<<(std::ostream &out,const Angle &a)
{
	out << a.m_angle;
	switch(a.m_unit)
	{
		case Angle::RADIANS:
			out << " radians";
			break;
		case Angle::DEGREES:
			out << " degrees";
	}
	return out;
}

void Angle::clean() { Math::clean(m_angle); }

bool Angle::isZero() const { return Math::isZero(m_angle); }

//get/set methods that do not take the internal units into account
//useful if we only work with one unit. i.e. only radians
double Angle::get() const { return m_angle; }
void Angle::set(const double scalar) { m_angle = scalar; }

Angle::Unit Angle::getUnit() const
{
	return m_unit;
}

void Angle::setUnit(Unit unit)
{
	m_unit = unit;
}

inline double Angle::as(Unit unit) const
{
	return unit == Angle::RADIANS ? asRadians() : asDegrees();
}

double Angle::asRadians() const
{
	return (m_unit == Angle::RADIANS ? m_angle : m_angle * Math::DEG_TO_RAD);
}

double Angle::asDegrees() const
{
	return (m_unit == Angle::DEGREES ? m_angle : m_angle * Math::RAD_TO_DEG);
}

} //namespace math

} //namespace arkhe
