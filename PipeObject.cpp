#include "stdafx.h"
#include "PipeObject.h"
#include "CommonFunction.h"

PipeOject::PipeOject()
{
	x_val_ = PIPE_VELOCITY;
	x_pos_ = 400;
	y_pos_ = 0;
	w_frame_ = 0;
	h_frame_ = 0;
}

PipeOject::~PipeOject()
{

}

//================================

void PipeOject::set_val(int pos_x, int pos_y)
{
	x_pos_ = pos_x;
	y_pos_ = pos_y;
}
//================================

bool PipeOject::load_image(std::string path, SDL_Renderer *screen)
{
	bool ret = BaseObject::load_image(path, screen);

	if (ret == true)
	{
		w_frame_ = rect_.w;
		h_frame_ = rect_.h;
	}
	return ret;
}

//==========================================

void PipeOject::show_pipe_up(SDL_Renderer *des, int pipe_vel)
{
	load_image("img/pipe_up.png", des);

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	x_pos_ -= pipe_vel;

	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

	SDL_RenderCopy(des, p_object_, NULL, &renderquad);

	/*
	if (x_pos_ == -52)
	{
		x_pos_ = NEW_X_POS;
	}
*/
}

//=============================================

void PipeOject::show_pipe_down(SDL_Renderer *des, int pipe_vel)
{
	load_image("img/pipe_down.png", des);
	rect_.x = x_pos_;
	rect_.y = y_pos_;

	x_pos_ -= pipe_vel;

	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

	SDL_RenderCopy(des, p_object_, NULL, &renderquad);

	if (x_pos_ == -52)
	{
 		x_pos_ = NEW_X_POS;
	}
}

void PipeOject::check_to_map()
{

}