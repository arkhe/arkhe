#ifndef __ARKHE_MATH_ANGLE_H__
#define __ARKHE_MATH_ANGLE_H__

//std includes
#include <ostream>

namespace arkhe
{

namespace math
{

//Angle class. Helpful for quick unit
//conversions (radians/degrees).
//Defaults to radian units
//Whenever a scalar is used, it is assumed
//it is the same as the internal units
//i.e. radians or degrees
class Angle
{
public:
	//angle unit
	enum Unit
	{
		RADIANS,
		DEGREES
	};
	//constructors
	Angle() : m_angle(0.0),m_unit(Angle::RADIANS) {};
	Angle(double angle,Unit unit=RADIANS) : m_angle(angle),m_unit(unit) {};
	Angle(const Angle &copy);
	//destructor
	~Angle() {}
	//operator overloads
	//'this' always takes precedence - in other words we will always
	//use the units of 'this' over the units of the right operand
	Angle &operator=(const Angle &copy);
	Angle operator+(const double scalar) const;
	Angle operator+(const Angle &right) const;
	Angle &operator+=(const double scalar);
	Angle &operator+=(const Angle &right);
	Angle operator-() const;
	Angle operator-(const double scalar) const;
	Angle operator-(const Angle &right) const;
	Angle &operator-=(const double scalar);
	Angle &operator-=(const Angle &right);
	Angle operator*(const double scalar) const;
	Angle operator*(const Angle &right) const;
	Angle &operator*=(const double scalar);
	Angle &operator*=(const Angle &right);
	Angle operator/(const double scalar) const;
	Angle operator/(const Angle &right) const;
	Angle &operator/=(const double scalar);
	Angle &operator/=(const Angle &right);
	bool operator==(const double scalar) const;
	bool operator==(const Angle &right) const;
	bool operator!=(const double scalar) const;
	bool operator!=(const Angle &right) const;
	bool operator<(const double scalar) const;
	bool operator<(const Angle &right) const;
	bool operator<=(const double scalar) const;
	bool operator<=(const Angle &right) const;
	bool operator>(const double scalar) const;
	bool operator>(const Angle &right) const;
	bool operator>=(const double scalar) const;
	bool operator>=(const Angle &right) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Angle &a);
	//methods
	void clean();
	bool isZero() const;
	double get() const;
	void set(const double scalar);
	Unit getUnit() const;
	void setUnit(Unit unit);
	double as(Unit unit) const;
	double asRadians() const;
	double asDegrees() const;
	//static variables
	static const Angle ZERO;
	static const Angle PI;
	static const Angle HALF_PI;
	static const Angle TWO_PI;
private:
	//variables
	double m_angle;
	Unit m_unit;
protected:
	//
}; //class Angle

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_ANGLE_H__
