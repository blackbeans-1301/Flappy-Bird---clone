#include "stdafx.h"
#include "CommonFunction.h"

int random(int min, int max)
{

	return rand() % (MAX - MIN + 1) + MIN;
}


//==================================================
bool check_collision( const int x_bird, const int &y_bird, const int &x_pipe1, const int &y_pipe1,
					 const int &x_pipe2, const int &y_pipe2, const bool &pass1, const bool &pass2)


{
	bool is_collision = false;

	if (y_bird > GROUND_Y_POS - 22)
	{
		return true;
	}

	if ( pass1 == false )
	{
		if ( (x_bird + 32 >= x_pipe1 && y_bird - 2 <= y_pipe1 + 320) || ( x_bird + 32 >= x_pipe1 && y_bird + 22 >= y_pipe1 + 320 + 100 ) )
		{
 			is_collision = true;
		}
		
	}

	if ( pass2 == false )
	{
		if ( ( x_bird + 32 >= x_pipe2 && y_bird - 2 <= y_pipe2 + 320) || ( x_bird + 32 >= x_pipe2 && y_bird + 22 >= y_pipe2 + 320 + 100 ) )
		{   
 			is_collision = true;
		}
	}


	return is_collision;
}

//======================================================

bool wait_until_space_pressed(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym = SDLK_SPACE)
		{
			return true;
		}
	}
	return false;
}


//========================

bool check_mouse_focus_pause (int xm, int ym, SDL_Rect &rect)
{
	if (( xm >= rect.x ) && ( xm <= rect.x + rect.w ) 
		  && ( ym >= rect.y ) && ( ym <= rect.y + rect.h ) )
	{
		return true;
	}
	return false;
}

//=======================

bool check_mouse_focus_mute (int xm, int ym, SDL_Rect &rect)
{
	if ( ( xm >= rect.x ) && ( xm <= rect.x + rect.w )
		&& ( ym >= rect.y ) && ( ym <= rect.y + rect.h ) )
	{
		return true;
	}

	return false;
}