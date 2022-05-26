#include "stdafx.h"
#include "MainObject.h"



MainObject::MainObject()
{
	delay_frame_ = 0;
	frame_ = 0;
	x_pos_ = 119;
	y_pos_ = 232;
	x_val_ = 0;
	y_val_ = 0;
	w_frame_ = 0;
	h_frame_ = 0;
	status_ = -1;
	angle = 0;
}

MainObject::~MainObject()
{}

bool MainObject::load_image(std::string path, SDL_Renderer *screen)
{
	bool ret = BaseObject::load_image(path, screen);

	if (ret == true)
	{
		w_frame_ = rect_.w / 3;
		h_frame_ = rect_.h;
	}
	return ret;
}

void MainObject::set_clip()
{
	if (w_frame_ > 0 && h_frame_ > 0)
	{
		 frame_clip_[0].x = 0;
		 frame_clip_[0].y = 0;
		 frame_clip_[0].w = w_frame_;
		 frame_clip_[0].h = h_frame_;

		 frame_clip_[1].x = w_frame_;
		 frame_clip_[1].y = 0;
		 frame_clip_[1].w = w_frame_;
		 frame_clip_[1].h = h_frame_;

		 frame_clip_[2].x = w_frame_ * 2;
		 frame_clip_[2].y = 0;
		 frame_clip_[2].w = w_frame_;
		 frame_clip_[2].h = h_frame_;

	}
}

// hàm show animation
void MainObject::show(SDL_Renderer *des)
{
	/*
	if ( status_ == JUMP )
	{
		load_image("img/bird.png", des);
	}
	
   	if (input_type_.jump_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	} 
	*/
	load_image("img/bird.png", des);

	frame_ = delay_frame_ / 7;
	delay_frame_++;
	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect *current_clip = &frame_clip_[frame_];

	SDL_Rect renderquad = { rect_.x, rect_.y, w_frame_, h_frame_ };

	//SDL_RenderCopy( des, p_object_, current_clip, &renderquad );
	SDL_RenderCopyEx ( des, p_object_, current_clip, &renderquad, angle, NULL, SDL_FLIP_NONE );
	if (delay_frame_ == 21)
	{
		delay_frame_ = 0;
	}
}

// hàm xử lý hình ảnh animation

void MainObject::handle_input( SDL_Event events, SDL_Renderer *screen, Mix_Chunk *wing )
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_SPACE:
			{
				status_ = JUMP;
				input_type_.jump_ = 1;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				
				Mix_PlayChannel( -1, wing, 0 );
				
				break;
			}
		
		default:
			break;
		}
	}

	if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_SPACE:
			{
				input_type_.jump_ = 0;
				break;
			}
		default:
			break;
		}

	}

}

//===============================================

void MainObject::do_player()
{ 
	x_val_ = 0;
	y_val_ += FALL_SPEED;

	y_pos_ += y_val_;
	angle += ANGLE_FALL;
	if (angle >= 50)
	{
		angle = 50;
	}

	if (input_type_.jump_ == 1)
	{
		angle = -30;
		y_val_ = -FLY_UP;
		//y_pos_ += y_val_;
		//y_val_ = 0;
	}
	check_to_map();
}

//===============================================

void MainObject::check_to_map()
{
	if ( y_pos_ > GROUND_Y_POS )
	{
		  y_pos_ = 488 - 22;
	}
}