//demo includes
#include "exception_tests.h"

//arkhe base includes
#include "ArkheException.h"
#include "ArkheTimer.h"
#include "ArkheTArray.hpp"
#include "ArkheT2dArray.hpp"
using namespace arkhe::base;

//arkhe math includes
#include "ArkheMathAPI.h"
using namespace arkhe::math;

//std includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h> //windows only

int main(int argc,char **argv)
{
	//GLUTWrapper::setApplication(new TestApp);
	//GLUTWrapper::run(argc,argv);	

	try
	{
		Vector2 v1,v2(1,1);
		std::cout << v1 << std::endl;
		std::cout << v2 << std::endl;

		std::cout << Vector3::X_AXIS.cross(Vector3::Y_AXIS) << std::endl;

		Normal3 n(1,2,3);
		std::cout << n << std::endl;
		n.normalize();
		std::cout << n << std::endl;

		Vector2 v3 = v1+v2;

		Ray2 r(Point2(1,2),Vector2(3,4));
		std::cout << r << std::endl;
		Point2 p(1,2);
		Point2 pr = p + v1;
		std::cout << r(1) << std::endl;

		Matrix22 m22;
		std::cout << m22 << std::endl;
		//Matrix22 n22 = m22.inverse();

		Matrix22 m2 = Matrix22::IDENTITY;
		Matrix33 m3 = Matrix33::IDENTITY;
		Matrix44 m4 = Matrix44::IDENTITY;
		std::cout << m2 << std::endl;
		std::cout << m3 << std::endl;
		std::cout << m4 << std::endl;

		{
			std::cout << "BENCHMARK:" << std::endl;
			unsigned int BENCH_LOOP = 25;
			unsigned int COUNT = 2;
			unsigned int POWER = 2;
			double t;
			double TOTAL_TIME = 0.0;
			unsigned int TOTAL_COUNT = 0;
			for(unsigned int i=1; i<=BENCH_LOOP; i++)
			{
				std::cout << "INNER LOOP COUNT: " << COUNT << " TOOK: ";
				arkhe::base::Timer timer;
				timer.start();
				for(unsigned int j=1; j<=COUNT; j++)
				{
					Vector2 v21,v22;
					Vector3 v31,v32;
					v21 = Vector2(i,j);
					v22 = Vector2(j,i);
					v31 = Vector3(i,j,(i+j));
					v32 = Vector3((i+j),j,i);
					Vector2 tmp2 = v21.parallelTo(v22);
					tmp2.normalize();
					double dot2 = v21.dot(v22);
					Vector3 tmp3 = v31.parallelTo(v32);
					tmp3.normalize();
					double dot3 = v31.dot(v32);

					Matrix22 m1,m2,m3;
					Matrix33 m4,m5,m6;
					Matrix44 m7,m8,m9;
					m1 = m2;
					m2 = m3 + m1;
					m3 = m1 * m2;
					m1 = m2.transpose();
					m4 = m5;
					m5 = m6 + m5;
					m6 = m5 * m6;
					m4 = m5.transpose();
					m7 = m8;
					m8 = m9 + m7;
					m9 = m7 * m8;
					m7 = m8.transpose();
				}
				timer.stop();
				t = timer.time();
				std::cout << t << " seconds." << std::endl;
				TOTAL_TIME += t;
				TOTAL_COUNT += COUNT;
				COUNT *= POWER;
			}
			std::cout << "--------------------------------------------" << std::endl;
			std::cout << TOTAL_COUNT << " ITERATIONS TOOK " << TOTAL_TIME << " SECONDS" << std::endl;
		}

		Matrix33 m = Matrix33::IDENTITY;
		std::cout << m << std::endl;
		//double det = m.determinant();
		//std::cout << "DETERMINANT: " << det << std::endl;
	}
	catch(arkhe::base::Exception e)
	{
		std::cout << e.what() << std::endl;
	}

	//DO NOT ERASE

	std::cout << std::endl;
	std::cout << "Running integrity tests..." << std::endl;
	try
	{
		std::cout << "Running arkhe math integrity tests..." << std::endl;
		MathIntegrityTests::run_all_tests();
		std::cout << "Integrity of all math tests verified..." << std::endl;
	}
	catch(arkhe::base::Exception e)
	{
		std::cout << e.what() << std::endl;
	}

	while(!_kbhit()) ;

	return 0;
}
