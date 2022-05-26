#include "stdafx.h"
#include "GroundObject.h"


GroundObject::GroundObject()
{
	x_val = PIPE_VELOCITY;
	x_pos_ = 0;
	y_pos_ = 488;
	width = 0;
	heigh = 0;
}

GroundObject::~GroundObject()
{

}

bool GroundObject::load_image(std::string path, SDL_Renderer *des)
{
	bool ret = BaseObject::load_image(path, des);
	if (ret == true)
	{
		width = rect_.w;
		heigh = rect_.h;
	}
	return ret;
}

void GroundObject::show_ground( std::string path, SDL_Renderer *des)
{
	load_image(path, des);

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	x_pos_ -= x_val;

	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_RenderCopy(des, p_object_, NULL, &renderquad);

	if (x_pos_ == -88)
	{
		x_pos_ = 0;
	}
}