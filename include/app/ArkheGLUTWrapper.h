#ifndef __ARKHE_APP_GLUTWRAPPER_H__
#define __ARKHE_APP_GLUTWRAPPER_H__

namespace arkhe
{

namespace app
{

//forward declarations
class App;

//Wrapper class for GLUT. Provides callback functions
//for GLUT that are linked the the application instance.
//This class implements a function to setup GLUT and
//run the application.
//
//The standard way to use GLUTWrapper is:
//
//int main(int argc,char **argv)
//{
//	GLUTWrapper::setApplication(new MyTestApp);
//	GLUTWrapper::run(argc,argv);
//	return 0;
//}
//
//Where GLUTWrapper will take care of the heap-allocated
//application instance that was passed to SetApplication().
class GLUTWrapper
{
	public:
		//destructor
		~GLUTWrapper();
		//methods
		static void setApplication(App *app);
		static App *getApplication();
		static void run(int argc,char **argv);
	private:
		//methods
		static void __cdecl createWindow(const char *title=0);
		static void __cdecl update();
		static void __cdecl display();
		static void __cdecl mouse(int button,int state,int x,int y);
		static void __cdecl mouseDrag(int x,int y);
		static void __cdecl resize(int width,int height);
		static void __cdecl keyboard(unsigned char key,int x,int y);
		//variables
		static App *app;
		//prevent instances of this
		//class being instantiated.
		GLUTWrapper();
		GLUTWrapper(const GLUTWrapper &right);
		GLUTWrapper &operator=(const GLUTWrapper &right);
	protected:
		//
}; //class GLUTWrapper

} //namespace app

} //namespace arkhe

#endif //__ARKHE_APP_GLUTWRAPPER_H__
