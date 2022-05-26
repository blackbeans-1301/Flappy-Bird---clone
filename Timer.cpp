#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_pause_ = false;
	is_start_ = false;
}

Timer::~Timer()
{
	
}

//==========================

void Timer::start()
{
	is_start_ = true;
	is_pause_ = false;

	start_tick_ = SDL_GetTicks();
}

//============================

void Timer::stop()
{
	is_pause_ = false;
	is_start_ = false;
}

//============================

void Timer::pause()
{
	if (is_start_ == true && is_pause_ == false)
	{
		is_pause_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;
	}
}

//==============================

void Timer::resume()
{
	if (is_pause_ == true)
	{
		is_pause_ = false;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int	Timer::get_ticks()
{
	if (is_start_ == true)
	{
		if (is_pause_ == true)
			return pause_tick_;
		else
			return SDL_GetTicks() - start_tick_;
	}
	return 0;

}

bool Timer::is_started()
{	
	return is_start_;
}

bool Timer::is_paused()
{
	return is_pause_;
}