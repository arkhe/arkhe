#ifndef __ARKHE_MATH_MATH_INTEGRITY_TESTS_H__
#define __ARKHE_MATH_MATH_INTEGRITY_TESTS_H__

namespace arkhe
{

namespace math
{

//the reason for putting all the integrity tests into a class
//is so that the class can be declared a friend of any class
//that we want to test, and when this is done we have access
//to all the non-public data, so it is a convenient means of
//testing hidden methods and data.
class MathIntegrityTests
{
public:
	//
	//methods
	//individual tests
	static void Math_tests();
	static void Angle_tests();
	static void Complex_tests();
	static void Tuple2_tests();
	static void Vector2_tests();
	static void Point2_tests();
	static void Polynomial_tests();
	//all tests
	static void run_all_tests();
private:
	//
protected:
	//
}; //class MathIntegrityTests

} //namespace math

} //namespace arkhe

#endif //__ARKHE_MATH_MATH_INTEGRITY_TESTS_H__
