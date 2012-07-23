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

//arkhe app includes
#include "ArkheApp.h"
#include "ArkheGLUTWrapper.h"
using namespace arkhe::app;

//glut includes
#include <gl/glut.h>

//std includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h> //windows only

class TestApp : public App
{
public:
	TestApp()
	{
		width = 500;
		height = 500;
		inverse = false;
		pixels = new float[width*height*3];
	}
	~TestApp() { if(pixels) delete[] pixels; }
	void initializeGraphics()
	{
		//find an invertible matrix
		unsigned int y = 0;
		int pick[500*500];
		TMatrixMM<500,float> zero;
		while(true)
		{
			for(unsigned int j=0; j<500*500; j++)
			{
				pick[j] = ::rand() % 1024; //(float)((j+y) % (500*500));
			}
			for(unsigned int j=0; j<500*500; j++)
			{
				m[j] = pick[j];
			}
			float det = m.determinant();
			if(!Math::isZero(det))
			{
				break;
			}
			y++;
			std::cout << "ATTEMPT " << y << " TO FIND AN INVERTIBLE MATRIX FAILED." << std::endl;
		}
		std::cout << "GOT INVERTIBLE MATRIX." << std::endl;
		std::cout << "MIN ELEM: " << m.min_element() << std::endl;
		std::cout << "MAX ELEM: " << m.max_element() << std::endl;
		m /= m.max_element();
		unsigned int x = 0;
		for(unsigned int i=0; i<500*500; i++)
		{
			pixels[x++] = m[i];
			pixels[x++] = m[i];
			pixels[x++] = m[i];
		}
		mi = m.inverse();
		id = m * mi;
		if(mi == zero)
		{
			std::cout << "BOTH NON-INVERTIBLE" << std::endl;
		}
		else
		{
			std::cout << "BOTH INVERTIBLE" << std::endl;
		}
	}
	void doit()
	{
		unsigned int x = 0;
		for(unsigned int i=0; i<500*500; i++)
		{
			if(inverse)
			{
				pixels[x++] = mi[i];
				pixels[x++] = mi[i];
				pixels[x++] = mi[i];
			}
			else if(matrix)
			{
				pixels[x++] = m[i];
				pixels[x++] = m[i];
				pixels[x++] = m[i];
			}
			else
			{
				pixels[x++] = id[i];
				pixels[x++] = id[i];
				pixels[x++] = id[i];
			}
		}
	}
	void display()
	{
		glDisable(GL_DEPTH_TEST);

		//temporarily set view to orthographic
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0,(double)width,0.0,(double)height,-1.0,1.0);

		//move to modelview mode
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glDrawPixels(width,height,GL_RGB,GL_FLOAT,pixels);

		//pop the matrices to return to how we were before
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_DEPTH_TEST);
	}
	void key(unsigned char k)
	{
		switch(k)
		{
		case 'i':
			inverse = true;
			matrix = identity = false;
			doit();
			break;
		case 'm':
			matrix = true;
			inverse = identity = false;
			doit();
			break;
		case 'n':
			identity = true;
			inverse = matrix = false;
			doit();
			break;
		case 'q':
			exit(1);
		}
	}
private:
	bool inverse,matrix,identity;
	TMatrixMM<500,float> m,mi,id;
	float *pixels;
};

void inversion_tests()
{
	try
	{
		unsigned int LOOP = 100000;
		unsigned int STEP = LOOP * 0.1;
		const unsigned int DIM = 16;
		unsigned int INVERTIBLE = 0;
		unsigned int NON_INVERTIBLE = 0;
		double TOTAL_TIME = 0.0;

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
}

void big_matrix_inverse()
{		
	//find an invertible matrix
	const unsigned int DIM = 100;
	unsigned int y = 0;
	TMatrixMM<DIM,float> m,mi;
	while(true)
	{
		for(unsigned int j=0; j<DIM*DIM; j++)
		{
			m[j] = ::rand() % 1024;
		}
		float det = m.determinant();
		if(!Math::isZero(det))
		{
			break;
		}
		y++;
		std::cout << "ATTEMPT " << y << " TO FIND AN INVERTIBLE MATRIX FAILED." << std::endl;
	}
	std::cout << "GOT INVERTIBLE MATRIX." << std::endl;
	std::cout << "MIN ELEM: " << m.min_element() << std::endl;
	std::cout << "MAX ELEM: " << m.max_element() << std::endl;

	Timer timer;
	timer.start();

	mi = m.inverse();

	timer.stop();
	std::cout << "INVERSION OF " << DIM << 'x' << DIM << " MATRIX TOOK " << timer.time() << " SECONDS." << std::endl;
}

int main(int argc,char **argv)
{
	GLUTWrapper::setApplication(new TestApp);
	GLUTWrapper::run(argc,argv);

	//inversion_tests();

	//big_matrix_inverse();

	while(!_kbhit()) ;

	return 0;
}
