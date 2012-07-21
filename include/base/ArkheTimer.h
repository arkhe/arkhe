#ifndef __ARKHE_BASE_TIMER_H__
#define __ARKHE_BASE_TIMER_H__

#if defined(_MSC_VER)
#pragma once
#endif

#if defined WIN32 || WINDOWS
#include <windows.h>
#else //LINUX
#include <sys/time.h>
#endif

namespace arkhe
{

namespace base
{

class Timer
{
public:
	//constructor
	Timer();
	//methods
	void start();
	void stop();
	void reset();
	double time();
private:
	//prevent copies
	Timer(const Timer &);
	Timer &operator=(const Timer &);
	//methods
	double getTime();
	//variables
	double m_time,m_elapsed;
	bool m_running;
	//cross platform variables
	#if defined WIN32 || WINDOWS
		LARGE_INTEGER m_perf_count,m_perf_freq;
		double m_recip_freq;
	#else //LINUX
		struct timeval m_timeofday;
	#endif
protected:
	//
}; //class Timer

} //namespace base

} //namespace arkhe

#endif //__ARKHE_BASE_TIMER_H__
