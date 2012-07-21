//arkhe math includes
#include "math_integrity_tests.h"
#include "ArkheMathAPI.h"

//arkhe base includes
#include "ArkheException.h"

namespace arkhe
{

namespace math
{

//Math tests
void MathIntegrityTests::Math_tests()
{
	/*//epsilon comparisions etc.
	if(!Math::isZero((1.0 + Math::SMALLER_EPSILON) - 1.0))
		throw arkhe::base::Exception("arkhe::math::Math error: (1.0 +  Math::SMALLER_EPSILON) - 1.0 != 0 (within epsilon limit)");
	if(Math::isZero((1.0 + (Math::EPSILON * 2.0)) - 1.0))
		throw arkhe::base::Exception("arkhe::math::Math error: (1.0 +  (Math::EPSILON * 2.0)) - 1.0 == 0 (within epsilon limit)");
	if(!Math::equal(Math::SMALLER_EPSILON,Math::SMALLER_EPSILON * 0.5))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::SMALLER_EPSILON != (Math::SMALLER_EPSILON/2) - essentially equal for all practical purposes");
	if(Math::equal(Math::EPSILON,Math::EPSILON * 2.0))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::EPSILON == Math::EPSILON * 2.0 - definitely not equal");
	if(Math::sqr(2) != 4)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sqr(2) != 4");
	if(Math::sqrt(25) != 5)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sqrt(25) != 5");
	//trig functions
	//sin
	if(Math::sin(0) != 0)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sin(0) != 0");
	if(Math::sin(Math::HALF_PI) != 1)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sin(Pi/2) != 1");
	//arc sin and NaN
	if(!Math::isNaN(Math::aSin(Math::HALF_PI)))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::aSin(Pi/2) != NaN");
	//cos
	if(Math::cos(0) != 1)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::cos(0) != 1");
	if(!Math::isZero(Math::cos(Math::HALF_PI)))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::cos(Pi/2) != 0");
	//aCos and NaN
	if(Math::aCos(0) != Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::aCos(0) != Pi/2");
	if(!Math::isNaN(Math::aCos(Math::HALF_PI)))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::aCos(Pi/2) != NaN");
	//sin/cos
	double sx,cx;
	Math::sinCos(Math::HALF_PI,sx,cx);
	if(sx != 1.0)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sinCos(Pi/2,sx,cx), sx != 1");
	if(!Math::isZero(cx))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::sinCos(Pi/2,sx,cx), cx != 0");
	//tan
	if(!Math::isZero(Math::tan(0.0)))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::tan(0) != 0");
	if(!Math::isZero(Math::tan(Math::PI)))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::tan(Pi) != 0");
	//note that tan(Pi/2) does not return infinity
	//aTan
	if(!Math::equal(Math::aTan(100000000),Math::HALF_PI))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::aTan(100000000) != Pi/2");
	//signum
	if(Math::signum(-55) != -1)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::signum(-55) != -1");
	if(Math::signum(0) != 0)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::signum(0) != 0");
	if(Math::signum(Math::PI) != 1)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::signum(Pi) != 1");
	//min/max
	if(min<int>(55,33) != 33)
		throw arkhe::base::Exception("arkhe::math::Math error: Math::min(55,33) != 33");
	if(!Math::equal(max<double>(Math::E,Math::HALF_PI),Math::E))
		throw arkhe::base::Exception("arkhe::math::Math error: Math::max(Math::E,Math::HALF_PI) != e");*/
}

//Angle tests
void MathIntegrityTests::Angle_tests()
{
	//conversion tests
	if(Angle(90.0,Angle::DEGREES).asRadians() != Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - 90 degrees != Pi/2 radians");
	if(Angle(Math::PI/4,Angle::RADIANS).asDegrees() != 45.0)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - Pi/4 radians != 45.0 degrees");
	if(Angle(Math::TWO_PI,Angle::RADIANS).asDegrees() != 360.0)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - 2Pi radians != 360.0 degrees");
	if(Angle(180.0,Angle::DEGREES).asRadians() != Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - 180 degrees != Pi radians");
	if(Angle(720.0,Angle::DEGREES).as(Angle::RADIANS) != Math::PI * 4)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - 720 degrees != 4Pi radians");
	if(Angle(Math::PI/10,Angle::RADIANS).as(Angle::DEGREES) != 18.0)
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - Pi/10 != 18 degrees");
	if(!Math::equal(Angle(Math::PI/3,Angle::RADIANS).as(Angle::DEGREES),60.0))
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - Pi/3 != 60 degrees");
	if(!Math::equal(Angle(Math::PI/6,Angle::RADIANS).as(Angle::DEGREES),30.0))
		throw arkhe::base::Exception("arkhe::math::Angle conversion error - Pi/6 != 30 degrees");

	//operator tests
	//+ operator
	if(Angle(Math::PI,Angle::RADIANS) + Math::PI != Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians + Pi != 2Pi");
	if(Angle(360,Angle::DEGREES) + 90 != 450.0)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 360 degrees - 90 != 450");
	if(Angle(Math::PI,Angle::RADIANS) + Angle(Math::HALF_PI,Angle::RADIANS) != Math::PI + Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - the sum of the following two radian angles: Pi + Pi/2 != Pi + Pi/2");
	if((Angle(Math::PI,Angle::RADIANS) + Angle(180.0,Angle::DEGREES)).asRadians() != Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - the sum of Pi rad and 180 degrees as radians != 2Pi radians");
	//+=
	Angle a(Math::PI,Angle::RADIANS);
	a += Math::PI;
	if(a.asRadians() != Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians += Pi != 2Pi");
	a.set(1.0); //still working with radians
	a += Angle(90,Angle::DEGREES);
	if(a.asDegrees() != 90 + Math::RAD_TO_DEG)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 1 radian + 90 degrees != ~147.3 degrees");
	//- operator
	if(-Angle(Math::TWO_PI,Angle::RADIANS).as(Angle::RADIANS) != -Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - the negation of 2Pi != -2Pi");
	if(Angle(Math::TWO_PI,Angle::RADIANS) - Math::PI != Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 2Pi radians - Pi != Pi");
	if((Angle(Math::PI,Angle::RADIANS) - Angle(90.0,Angle::DEGREES)).asDegrees() != 90.0)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians - 90 degrees != 90");
	//-=
	a = Angle(270.0,Angle::DEGREES);
	a -= 90.0;
	if(a.asDegrees() != 180.0)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 270 degrees -= 90.0 != 180 degrees");
	a.set(90.0); //still working with degrees
	a -= Angle(Math::HALF_PI,Angle::RADIANS);
	if(!Math::isZero(a.asRadians()))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 90 degrees - Pi/2 radians != 0.0 radians/degrees");
	//*
	if((Angle(90.0,Angle::DEGREES) * 2.0).asRadians() != Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 90 degrees * 2 != Pi radians");
	if((Angle(Math::PI,Angle::RADIANS) * Angle(180.0,Angle::DEGREES).asRadians() != Math::sqr(Math::PI)))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - the product of Pi radians and 180 degrees as radians != Pi^2 radians");
	//*=
	a = Angle(90,Angle::DEGREES);
	a *= 4.0;
	if(a.asRadians() != Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 90 degrees *= 4.0 != 2Pi radians");
	a.set(45.0); //still degrees
	a *= Angle(Math::HALF_PI*0.5,Angle::RADIANS);
	if(a.asDegrees() != 2025)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 45 degrees *= Pi/4 != 2025 degrees");
	// /
	if((Angle(360.0,Angle::DEGREES) / 4.0).asRadians() != Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 360 degrees / 4 != Pi/2 radians");
	if((Angle(Math::PI * 2.0,Angle::RADIANS) / Angle(90,Angle::DEGREES)).asDegrees() != Math::RAD_TO_DEG * 4.0)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 2Pi radians / 90 degrees != ~229.2 degrees");
	// /=
	a = Angle(360.0,Angle::DEGREES);
	a /= 4.0;
	if(a.asRadians() != Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 360 degrees / 4 != Pi/2 radians");
	a.set(1440.0); //still degrees
	a /= Angle(Math::PI,Angle::RADIANS);
	if(a.asDegrees() != 8.0)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 1440 degrees / Pi radians != 8 degrees");

	//equality operators
	//==
	if(Angle(Math::PI,Angle::RADIANS) == Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians == Pi/2");
	if(Angle(Math::HALF_PI,Angle::RADIANS) == Angle(360.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi/2 radians == 360 degrees");
	//!=
	if(Angle(Math::PI,Angle::RADIANS) != Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians != Pi");
	if(Angle(Math::HALF_PI,Angle::RADIANS) != Angle(90.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi/2 radians != 90 degrees");
	//<
	if(Angle(Math::PI,Angle::RADIANS) < Math::HALF_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians < Pi/2");
	if(Angle(Math::HALF_PI,Angle::RADIANS) < Angle(45.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi/2 radians < 45 degrees");
	//<=
	if(Angle(Math::TWO_PI,Angle::RADIANS) <= Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - 2Pi radians <= Pi");
	if(Angle(Math::PI,Angle::RADIANS) <= Angle(18.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians <= 18 degrees");
	//>
	if(Angle(Math::PI,Angle::RADIANS) > Math::TWO_PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians > 2Pi");
	if(Angle(Math::HALF_PI,Angle::RADIANS) > Angle(180.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi/2 radians > 180 degrees");
	//>=
	if(Angle(Math::HALF_PI,Angle::RADIANS) >= Math::PI)
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi/2 radians > Pi");
	if(Angle(Math::PI,Angle::RADIANS) >= Angle(450.0,Angle::DEGREES))
		throw arkhe::base::Exception("arkhe::math::Angle operator error - Pi radians > 450 degrees");
}

//Complex tests
void MathIntegrityTests::Complex_tests()
{
	//todo
}

//Tuple2 tests
void MathIntegrityTests::Tuple2_tests()
{
	//todo
}

//Vector2 tests
void MathIntegrityTests::Vector2_tests()
{
	//todo
}

//Point2 tests
void MathIntegrityTests::Point2_tests()
{
	//todo
}

//Polynomial tests
void MathIntegrityTests::Polynomial_tests()
{
	//todo
}

//run all math tests
void MathIntegrityTests::run_all_tests()
{
	Math_tests();
	Angle_tests();
	Complex_tests();
	Tuple2_tests();
	Vector2_tests();
	Point2_tests();
}

} //namespace math

} //namespace arkhe
