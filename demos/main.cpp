//demo includes
#include "exception_tests.h"

//arkhe base includes
#include "ArkheException.h"
#include "ArkheTimer.h"
#include "ArkheTArray.h"
#include "ArkheT2dArray.h"
//#include "ArkhePPMImage.h"
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

typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255

static PPMImage *readPPM(const char *filename)
{
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}

class TestApp : public App
{
public:
	TestApp()
	{
		width = 512;
		height = 512;
		inverse = false;
		pixels = new float[width*height*3];
	}
	~TestApp() { if(pixels) delete[] pixels; }
	void initializeGraphics()
	{
		//find an invertible matrix
		unsigned int y = 0;
		float pick[512*512];
		TMatrixMM<512,float> zero;
		/*while(true)
		{
			for(unsigned int j=0; j<512*512; j++)
			{
				pick[j] = (float)(::rand() % 1024) / 1024.f; //(float)((j+y) % (512*512));
			}
			for(unsigned int j=0; j<512*512; j++)
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
		}*/

		PPMImage *image = readPPM("mandrill.ppm");
		//PPMImage *image = readPPM("abe_natsumi.ppm");
		//PPMImage *image = readPPM("azumi_kawashima2.ppm");
		//PPMImage *image = readPPM("brian_kernighan.ppm");
		//PPMImage *image = readPPM("rie_hasegawa.ppm");
		//PPMImage *image = readPPM("vivian.ppm");
		for(unsigned int i=0; i<512*512; i++)
		{
			float r = (float)image->data[i].red;
			float g = (float)image->data[i].green;
			float b = (float)image->data[i].blue;
			float rgb_av = (r + g + b) / 3;
			m[i] = rgb_av;
		}
		delete image;
		m = m.transpose();
		m.clean();
		float det = m.determinant();
		if(!Math::isZero(det))
		{
			//invertible...
			std::cout << "GOT INVERTIBLE MATRIX." << std::endl;
			std::cout << "MIN ELEM: " << m.min_element() << std::endl;
			std::cout << "MAX ELEM: " << m.max_element() << std::endl;
			m /= m.max_element();
			m.clean();
			unsigned int x = 0;
			for(unsigned int i=0; i<512*512; i++)
			{
				pixels[x++] = m[i];
				pixels[x++] = m[i];
				pixels[x++] = m[i];
			}
			mi = m.inverse(TMatrixMM<512,float>::GAUSS_JORDAN);
			mi.clean();
			id = m * mi;
			id.clean();
			if(mi == zero)
			{
				std::cout << "BOTH NON-INVERTIBLE" << std::endl;
			}
			else
			{
				std::cout << "BOTH INVERTIBLE" << std::endl;
			}
		}
		else
		{
			std::cout << "NOT INVERTIBLE..." << std::endl;
		}
	}
	void doit()
	{
		unsigned int x = 0;
		for(unsigned int i=0; i<512*512; i++)
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
	TMatrixMM<512,float> m,mi,id;
	float *pixels;
};

void inversion_tests()
{
	try
	{
		unsigned int LOOP = 100000;
		unsigned int STEP = LOOP * 0.1;
		const unsigned int DIM = 4;
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
			TMatrixMM<DIM,double> m,mi,mxi,zero,identity(matrix_ops::identity<double>(DIM));
			//init
			for(unsigned int j=0; j<DIM*DIM; j++)
			{
				m[j] = ::rand() % 100;
			}
			if(!Math::isZero(m.determinant()))
			{
				mi = m.inverse(TMatrixMM<DIM,double>::GAUSS_JORDAN);
				mi.clean();
				mxi = m * mi;
				mxi.clean();
				if(mxi != identity)
				{
					//NON_INVERTIBLE++;
				}
				INVERTIBLE++;
			}
			else
			{
				NON_INVERTIBLE++;
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
	const unsigned int DIM = 1024;
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

	mi = m.inverse(TMatrixMM<DIM,float>::GAUSS_JORDAN);

	timer.stop();
	std::cout << "INVERSION OF " << DIM << 'x' << DIM << " MATRIX TOOK " << timer.time() << " SECONDS." << std::endl;
}

void test()
{
	double t;
	unsigned int LOOP = 1000000;

	std::cout << "TEST STARTED:" << std::endl;

	float id[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Timer timer;
	timer.start();

	for(unsigned int i=0; i<LOOP; i++)
	{
		TMatrixMM<4,float> m(id),mi(id),mxi;
		mi = m.inverse(TMatrixMM<4,float>::GAUSS_JORDAN);
		mxi = m * mi;
	}

	timer.stop();
	t = timer.time();
	std::cout << "TOOK " << t << " SECONDS FOR " << LOOP << " ITERATIONS." << std::endl;
}

int main(int argc,char **argv)
{
	GLUTWrapper::setApplication(new TestApp);
	GLUTWrapper::run(argc,argv);

	Matrix33 m(3,1,0,-1,2,2,5,0,-1);
	//Matrix33 m(3,3,6,0,1,2,-2,0,0);
	std::cout << "MATRIX:\n" << m << std::endl;
	std::cout << "MATRIX^-1:\n" << m.inverse() << std::endl;
	Matrix33 mxi = m * m.inverse(Matrix33::GAUSS_JORDAN);
	mxi.clean();
	std::cout << "MATRIX x MATRIX^-1:\n" << mxi << std::endl;

	/*try
	{
		PPMImage img("abe_natsumi.ppm");
	}
	catch(Exception e)
	{
		std::cout << e.what() << std::endl;
	}*/

	//inversion_tests();

	//big_matrix_inverse();

	//test();

	while(!_kbhit()) ;

	return 0;
}
