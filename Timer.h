#pragma once
#include "CommonFunction.h"

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void resume();

	int get_ticks();

	bool is_started();
	bool is_paused();

private:

	int start_tick_;
	int pause_tick_;


	bool is_pause_;
	bool is_start_;

};