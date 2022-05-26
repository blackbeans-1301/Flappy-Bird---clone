#include "stdafx.h"
#include "GameMenu.h"
#include "GroundObject.h"
#include "TextObject.h"
#include "Timer.h"
#include <fstream>



GameMenu::GameMenu()
{
	x_ = 112;
	y_ = 122;
	
	xm = 0;
	ym = 0;

	width_ = 0;
	height_ = 0;
}
GameMenu::~GameMenu()
{
	
}

bool GameMenu::load_image(std::string path, SDL_Renderer *screen)
{
	    BaseObject ::load_image( path, screen );
		width_ = rect_.w;
		height_ = rect_.h;

		return true;
}

//========================================

bool GameMenu::show_menu_die(SDL_Renderer *des, unsigned short int &score) 
{
	load_image("img/restart.png", des);
	rect_.x = 115;
	rect_.y = 320;

	TTF_Font *score_font = NULL;
	BaseObject game_over;
	game_over.load_image("img/Game_Over.png", des);
	game_over.set_rect(75, 150);
	game_over.render(des, NULL);

	BaseObject best_score;
	best_score.load_image("img/best.png", des);
	best_score.set_rect(130, 36);
	best_score.render(des, NULL);

	BaseObject restart;
	restart.load_image("img/restart.png", des);
	restart.set_rect(115, 320);
	restart.render(des, NULL);

	TextObject score_text;
	Timer fps_time;
	
	
	// show high score
	TextObject highScore;
	int high_score;
	std::ifstream score_input("highscore.txt");
	if (score_input.is_open() == true)
	{
		
		score_input >> high_score;
		if (high_score < score)
		{
			high_score = score;
			std::ofstream score_delete("highscore.txt");
			score_delete.close();
			std::ofstream score_write("highscore.txt");
			score_write << high_score;
		}
	}
	std::string high_sc = std::to_string(high_score);
	score_font = TTF_OpenFont("font/ARCADE_N.ttf", 30);
	highScore.set_text(high_sc);
	highScore.load_text_texture(des, score_font);
	if (high_score < 10)
	{
		highScore.render_text(des, 155, 85, NULL, 0, NULL);
	}
	else
	{
		highScore.render_text(des, 140, 85, NULL, 0, NULL);
	}

	// show score when you dead
	score_font = TTF_OpenFont("font/ARCADE_N.ttf", 60);
	std::string score_die = std::to_string(score);
	score_text.set_text(score_die);
	score_text.load_text_texture(des, score_font);
	if (score < 10)
	{
		score_text.render_text(des, 140, 230, NULL, 0, NULL);
	}
	else
	{
		score_text.render_text(des, 105, 230, NULL, 0, NULL);
	}
	int w_text = score_text.get_w_text();
	SDL_Event mouse;
	//SDL_Rect renderquad = { 0, 0, 0, 0 };
	SDL_RenderPresent(des);
	
	bool re_play = false;
	while (!re_play)
	{
		fps_time.start();
		
		while (SDL_PollEvent(&mouse) != 0)
		{
			if (mouse.type == SDL_QUIT)
				return false;

			if (mouse.type == SDL_MOUSEBUTTONDOWN)
			{
				xm = mouse.button.x;
				ym = mouse.button.y;

				if ( check_mouse_focus_die(xm, ym, rect_) )
					return true;

			}
			//SDL_RenderCopy(des, p_object_, NULL, &renderquad);
			

		}


		int real_time = fps_time.get_ticks();
		int	time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame)
		{
			SDL_Delay(time_per_frame - real_time);
		}
		
		
	}
	
	return false;
}
//========================================


bool GameMenu::show_menu_start(SDL_Renderer *des)
{
	
	load_image("img/play_menu.png", des);
	rect_.x = x_;
	rect_.y = y_;

	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_Event m_event;
	// Back cho menu start
	BaseObject back_ground;
	//back_ground.load_image( "img/background_night.png" , des);
	//back_ground.render(des, NULL);
	BaseObject flappy_bird;
	BaseObject get_ready;
	//get_ready.load_image( "img/get_ready.png", des);
	//get_ready.set_rect( 72, 70);
	//get_ready.render( des, NULL );
	// ground cho menu start

	GroundObject ground_start;
	//ground_start.load_image ( "img/ground.png", des );
	
	get_ready.load_image( "img/get_ready.png", des);
	back_ground.load_image( "img/background_night.png" , des);
	flappy_bird.load_image("img/flappy_bird.png", des);

	flappy_bird.set_rect (75, 30);
	get_ready.set_rect( 72, 390);

	Timer fps_time;
	
	bool is_play = false;
	
	while (!is_play)
	{
		fps_time.start();
		SDL_SetRenderDrawColor(des, 255, 255, 255, 255);
		SDL_RenderClear(des);

		back_ground.render(des, NULL);
		ground_start.show_ground ( "img/ground.png", des );

		get_ready.render( des, NULL );
		flappy_bird.render(des, NULL);
		
		SDL_RenderCopy(des, p_object_, NULL, &renderquad);


		while (SDL_PollEvent(&m_event) != 0)
		{
			
			switch (m_event.type)
			{
			case SDL_QUIT:
				{
					return false;
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;

					if (check_mouse_focus_start(xm, ym, rect_))
					{
						//SDL_Delay(50);
						return true;
					}

					break;
					
				}
			
			default:
				break;
			}
			
			
		}

		

		int real_time = fps_time.get_ticks();
		int	time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame)
		{
			SDL_Delay(time_per_frame - real_time);
		}
		SDL_RenderPresent(des);
		
	}
	
	
	return false;
}


bool GameMenu::check_mouse_focus_start(int x, int y, SDL_Rect &rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y + 158 && y <= rect.y + 158 + 58)
	{
		return true;
	}

	return false;
}

bool GameMenu::check_mouse_focus_die( int x, int y, SDL_Rect &rect )
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h )
	{
		return true;
	}
	return false;
}