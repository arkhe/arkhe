//arkhe base includes
#include "ArkheTimer.h"
#include "ArkheException.h"

namespace arkhe
{

namespace base
{

Timer::Timer()
{
	#if defined WIN32 || WINDOWS
		QueryPerformanceFrequency(&m_perf_freq);
		m_recip_freq = 1.0 / (double)m_perf_freq.QuadPart;
	#endif
		m_time = m_elapsed = 0;
		m_running = false;
}

void Timer::start()
{
	m_running = true;
	m_time = getTime();
}

void Timer::stop()
{
	m_running = false;
	m_elapsed += getTime() - m_time;
}

void Timer::reset()
{
	m_running = false;
	m_elapsed = 0;
}

double Timer::time()
{
	if(m_running)
	{
		stop();
		start();
	}
	return m_elapsed;
}

double Timer::getTime()
{
	#if defined WIN32 || WINDOWS
		QueryPerformanceCounter(&m_perf_count);
		return (double)m_perf_count.QuadPart * m_recip_freq;
	#else //LINUX
		gettimeofday(&m_timeofday,NULL);
		return m_timeofday.tv_sec + m_timeofday.tv_usec / 1000000.0;
	#endif
}

} //namespace base

} //namespace arkhe
