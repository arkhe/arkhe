#ifndef __ARKHE_APP_APP_H__
#define __ARKHE_APP_APP_H__

//arkhe base includes
#include "ArkheTimer.h"

namespace arkhe
{

namespace app
{

//Base class for implementing applications.
class App
{
	public:
		//constructor
		App();
		//destructor
		virtual ~App();
		//methods
		const unsigned int getWidth() const;
		void setWidth(unsigned int width);
		const unsigned int getHeight() const;
		void setHeight(unsigned int height);
		virtual const char *getTitle();
		virtual void initializeGraphics();
		virtual void setView();
		virtual void deinitialize();
		virtual void display();
		virtual void update();
		virtual void key(unsigned char key);
		virtual void resize(unsigned int width,unsigned int height);
		virtual void mouse(int button,int state,int x,int y);
		virtual void mouseDrag(int x,int y);
		void renderText(double x,double y,const char *text,void *font=0);
	private:
		//
	protected:
		//methods
		virtual void drawGrid();
		virtual void drawFPS();
		//variables
		unsigned int width,height;
		arkhe::base::Timer timer;
		double cachedFPS,timeStep,fpsUpdate;
}; //class App

} //namespace app

} //namespace arkhe

#endif //__ARKHE_APP_APP_H__
