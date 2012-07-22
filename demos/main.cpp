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
#include <iomanip>
#include <conio.h> //windows only

int main(int argc,char **argv)
{
	//GLUTWrapper::setApplication(new TestApp);
	//GLUTWrapper::run(argc,argv);	

	try
	{
		/*{
			std::cout << "BENCHMARK:" << std::endl;
			unsigned int BENCH_LOOP = 21;
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
					
					double dot2 = v21.dot(v22);
					double dot3 = v31.dot(v32);

					v31.normalize();
					v21.normalize();
					

					Matrix44 m7,m8,m9;
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
		}*/

		/*//Matrix44 m(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),U,L;
		Matrix44 m(6,3,5,78,0,1,2,54,78,3,45,24,91,0,1,34),U,L;
		std::cout << m << std::endl;
		std::cout << "TRACE: " << m.trace() << std::endl;

		std::cout << "TESTING LU DECOMPOSITION:" << std::endl;
		std::cout << "MATRIX:\n" << m << std::endl;
		L = m.lower();
		L.clean();
		std::cout << "LOWER MATRIX:\n" << L << std::endl;
		U = m.upper();
		U.clean();
		std::cout << "UPPER MATRIX:\n" << U << std::endl;

		std::cout << "LOWER x UPPER:\n" << L * U << std::endl;

		Matrix22 m2(1,2,3,4);
		std::cout << m2 << std::endl;
		double det = m2.determinant();
		std::cout << "2x2 DETERMINANT: " << det << std::endl;
		std::cout << "2x2 ADJUGATE:\n" << m2.adjugate() << std::endl;
		det = m.determinant(); 
		std::cout << "4x4 DETERMINANT: " << det << std::endl;
		std::cout << "4x4 ADJUGATE:\n" << m.adjugate() << std::endl;

		Matrix33 m3 = Matrix33(1,2,3,0,1,4,5,6,0);
		std::cout << m3 << std::endl;
		//m3 = m3.transpose();
		std::cout << "3x3 DETERMINANT: " << m3.determinant() << std::endl;
		std::cout << "3x3 ADJUGATE:\n" << m3.adjugate() << std::endl;

		std::cout << "=====================================" << std::endl;
		TMatrixMM<5,double> M;
		M[0] = 25;
		M[1] = 512;
		M[2] = 15;
		M[3] = 15;
		M[4] = 155;

		M[5] = 51;
		M[6] = 541;
		M[7] = 54;
		M[8] = 0;
		M[9] = 51;

		M[10] = 48;
		M[11] = 21;
		M[12] = 25;
		M[13] = 5;
		M[14] = 48;

		M[15] = 0;
		M[16] = 7;
		M[17] = 4;
		M[18] = 596;
		M[19] = 69;

		M[20] = 16;
		M[21] = 26;
		M[22] = 64;
		M[23] = 65;
		M[24] = 9;
		//std::cout << std::fixed << std::endl;
		std::cout << M << std::endl;
		std::cout << "5x5 DETERMINANT: " << M.determinant() << std::endl;
		std::cout << "5x5 ADJUGATE:\n" << M.adjugate() << std::endl;
		TMatrixMM<5,double> MxI = M * M.inverse();
		MxI.clean();
		std::cout << "5x5 MATRIX * INVERSE:\n" << MxI << std::endl;*/
		
		/*Matrix33 M2(1,0,3,4,0,6,0,8,9);
		std::cout << M2 << std::endl;
		std::cout << "3x3 DETERMINANT: " << M2.determinant() << std::endl;
		std::cout << "3x3 ADJUGATE:\n" << M2.adjugate() << std::endl;
		std::cout << "3x3 INVERSE:\n" << M2.inverse() << std::endl;
		std::cout << "3x3 MATRIX * INVERSE:\n" << M2 * M2.inverse() << std::endl;*/

		unsigned int LOOP = 100000;
		unsigned int STEP = LOOP * 0.1;
		const unsigned int DIM = 16;
		unsigned int INVERTIBLE = 0;
		unsigned int NON_INVERTIBLE = 0;
		double TOTAL_TIME = 0.0;
		TMatrixMM<DIM,double> identity;
		for(unsigned int i=0; i<DIM; i++)
			for(unsigned int j=0; j<DIM; j++)
				if(i == j)
					identity(i,j) = 1.0;
				else
					identity(i,j) = 0.0;
		TMatrixMM<DIM,double> test;
		for(unsigned int j=0; j<DIM*DIM; j++)
		{
			test[j] = ::rand() % 50;
		}
		
		//std::cout << test << std::endl;
		//std::cout << std::fixed << std::endl;
		//std::cout << test.inverse() << std::endl;
		//std::cout << std::scientific << std::endl;
		TMatrixMM<DIM,double> res = test * test.inverse();
		res.clean();
		//std::cout << res << std::endl;

		//std::cout << identity << std::endl;

		std::cout << "PERFORMING " << LOOP << " ITERATIONS WITH " << DIM << "x" << DIM << " MATRICES:" << std::endl;
		std::cout << "GENERATE MATRIX WITH RANDOM ELEMENTS, AND COMPUTE IT'S INVERSE." << std::endl;
		std::cout << "KEEP TRACK OF THE NUMBER OF NON-INVERTIBLE MATRICES." << std::endl;
		std::cout << "-----------------------------------------------------------------" << std::endl;
		unsigned int i = 0;
		Timer timer;
		timer.start();
		while(INVERTIBLE < LOOP)
		{
			if(i % STEP == 0)
			{
				std::cout << "On loop " << i << " of " << LOOP << " ..." << std::endl;
			}
			TMatrixMM<DIM,double> m,mi,mxi,zero;
			//init
			for(unsigned int j=0; j<DIM*DIM; j++)
			{
				m[j] = ::rand() % 100;
			}
			mi = m.inverse();
			mi.clean();
			mxi = m * mi;
			mxi.clean();
			if(mi == zero)
			{
				NON_INVERTIBLE++;
			}
			else
			{
				INVERTIBLE++;
			}
			i++;
		}
		timer.stop();
		double t = timer.time();
		std::cout << std::fixed << std::endl;
		std::cout << "TOTAL TIME: " << t << " seconds." << std::endl;
		std::cout << INVERTIBLE << " WERE INVERTIBLE" << std::endl;
		std::cout << NON_INVERTIBLE << " WERE NON-INVERTIBLE" << std::endl;
		TOTAL_TIME += t;
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
