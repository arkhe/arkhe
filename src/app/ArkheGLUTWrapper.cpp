//arkhe app includes
#include "ArkheGLUTWrapper.h"
#include "ArkheApp.h"

//std dependencies
#include <cstdlib> //must be included before GLUT

//glut includes
#include <gl/glut.h>

namespace arkhe
{

namespace app
{

//static variable declaritions
App *GLUTWrapper::app = 0;

GLUTWrapper::~GLUTWrapper()
{
	delete GLUTWrapper::app;
}

void GLUTWrapper::setApplication(App *app)
{
	if(GLUTWrapper::app)
	{
		delete GLUTWrapper::app;
	}
	GLUTWrapper::app = app;
}

App *GLUTWrapper::getApplication()
{
	return GLUTWrapper::app;
}

void GLUTWrapper::run(int argc,char **argv)
{
	//first check if we have a valid application instance
	if(!app)
	{
		//error!
		abort();
	}

	//initialize GLUT
	glutInit(&argc,argv);

	//create window
	GLUTWrapper::createWindow(app->getTitle());

	//set up the appropriate handler functions
	glutReshapeFunc(&GLUTWrapper::resize);
	glutKeyboardFunc(&GLUTWrapper::keyboard);
	glutDisplayFunc(&GLUTWrapper::display);
	glutIdleFunc(&GLUTWrapper::update);
	glutMouseFunc(&GLUTWrapper::mouse);
	glutMotionFunc(&GLUTWrapper::mouseDrag);

	//run the application
	app->initializeGraphics();
	glutMainLoop();

	//clean up
	app->deinitialize();
}

void GLUTWrapper::createWindow(const char *title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(app->getWidth(),app->getHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow(title);
}

void GLUTWrapper::update()
{
	//update the applications clock
	//
	//update the application
	app->update();
}

void GLUTWrapper::display()
{
	app->display();
	//update the OpenGL state
	glFlush();
	glutSwapBuffers();
}

void GLUTWrapper::mouse(int button,int state,int x,int y)
{
	app->mouse(button,state,x,y);
}

void GLUTWrapper::mouseDrag(int x,int y)
{
	app->mouseDrag(x,y);
}

void GLUTWrapper::resize(int width,int height)
{
	app->resize(width,height);
}

void GLUTWrapper::keyboard(unsigned char key,int x,int y)
{
	app->key(key);
}

} //namespace app

} //namespace arkhe
