#include "stdafx.h"
#include "BaseObject.h"
#include "CommonFunction.h"
#include "MainObject.h"
#include "Timer.h"
#include "PipeObject.h"
#include "GroundObject.h"
#include "TextObject.h"
#include "GameMenu.h"


//khởi tạo g_background để lưu trữ dữ liệu background cho game
BaseObject g_background;
TTF_Font *score_font = NULL;


bool init_audio();
bool init();
bool load_background(std::string path);
void close();


int main(int argc, char* argv[])
{
	bool is_mute = false;
	bool is_pause = false;
	bool space_pressed = false;
	int pipe_vel = 4;
	bool is_collision = false;
	int y = 0;
	unsigned short int score = 0;
	bool pipe1_pass = false;
	bool pipe2_pass = false;

	Timer fps_time;

	// khởi tạo
	if (init() == false)
		return -1;
	if (load_background("img/background_night.png") == false)
		return -1;
	if (init_audio() == false)
	{
		return -1;
	}

	//load background ban đầu
	GroundObject ground;
	
	//mute
	BaseObject mute;
	mute.load_image("img/mute.png", g_screen);
	mute.set_rect(276, 5);

	//pause
	BaseObject pause;
	pause.load_image("img/pause.png", g_screen);
	pause.set_rect(318, 0);

	// PIPE SETUP////////////////////////////
	//y = random(MIN, MAX);
	PipeOject p_pipe_up1;
	//p_pipe_up1.load_image("img/pipe_up.png", g_screen);
	p_pipe_up1.set_val(800, -100);


	PipeOject p_pipe_down1;
	//p_pipe_down1.load_image("img/pipe_down.png", g_screen);
	p_pipe_down1.set_val(800, 320);

	PipeOject p_pipe_up2;
	//p_pipe_up2.load_image("img/pipe_up.png", g_screen);
	p_pipe_up2.set_val(1000, -80);


	PipeOject p_pipe_down2;
	//p_pipe_down2.load_image("img/pipe_down.png", g_screen);
	p_pipe_down2.set_val(1000, 340 );


	/////////////////////////////////////////

	MainObject p_player;
	p_player.load_image("img/bird.png", g_screen);
	p_player.set_clip();

	// text
	TextObject score_text;




	// vòng lặp GAME
	bool is_fly = true;
	bool is_quit = false;
	bool is_play_game = false;

	GameMenu start_menu;
	GameMenu die_menu;
	
	bool is_play = start_menu.show_menu_start(g_screen);
	if (is_play == false)
		is_quit = true;
	

	// vòng lặp chính khi chơi game

	while (!is_quit)
	{

		bool is_die = false;
		fps_time.start();
		while (SDL_PollEvent(&g_event))
		{
			
			switch (g_event.type)
			{
			case SDL_QUIT:
				{
					is_quit = true;
					break;
				}
			case SDL_KEYDOWN:
				{
					if (g_event.key.keysym.sym == SDLK_SPACE)
					{
						space_pressed = true;
					}

					break;
				}
			

			default:
				break;
			}

 			p_player.handle_input(g_event, g_screen, g_wing);
			
		}
		

		// reset màu cho màn hình
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		//xóa màn hình cũ
		SDL_RenderClear(g_screen);

 		g_background.render(g_screen, NULL);

		//main object
		p_player.show(g_screen);
		//pipe
		int pos_x1 = p_pipe_up1.get_x_pos();
		if (pos_x1 == -52)
		{
			y = random(MIN, MAX);
			p_pipe_up1.set_val(NEW_X_POS, y - 320);
			p_pipe_down1.set_val(NEW_X_POS, y + 100);
			pipe1_pass = false;
		}
		p_pipe_up1.show_pipe_up( g_screen, pipe_vel) ;
		p_pipe_down1.show_pipe_down( g_screen, pipe_vel);

		 
		int pos_x2 = p_pipe_up2.get_x_pos();
		if (pos_x2 == -52)
		{
			y = random(MIN ,MAX);
			p_pipe_up2.set_val(NEW_X_POS, y - 320);
			p_pipe_down2.set_val(NEW_X_POS, y + 100);
			pipe2_pass = false;
		}
		p_pipe_up2.show_pipe_up(g_screen, pipe_vel);
		p_pipe_down2.show_pipe_down(g_screen, pipe_vel);

		//ground
		ground.show_ground( "img/ground.png", g_screen );


		// show điểm cho game
		if (p_pipe_up1.get_x_pos() + 52 <= p_player.get_x_pos() && pipe1_pass == false)
		{
			score++;
			pipe1_pass = true;
			Mix_PlayChannel( -1, g_point, 0 );
		}
		if (p_pipe_up2.get_x_pos() + 52 <= p_player.get_x_pos() && pipe2_pass == false)
		{
			score++; 
			pipe2_pass = true;
			Mix_PlayChannel( -1, g_point, 0 );
		}

		std::string str_score = std::to_string(score);

		score_text.set_text(str_score);
		score_text.load_text_texture(g_screen, score_font);

		score_text.render_text(g_screen, 150, 50, NULL, 0, NULL);
		
		//int w_text = score_text.get_w_text();
		//=========================

		if ( (score > 1) && (score % 5 == 0) && ((score / 5) % 2 == 1))
			load_background("img/background.png");
		else if ( (score > 1) && (score % 5 == 0) && ( (score % 5) % 2 == 0 ) )
		{
			load_background("img/background_night.png");
		}
		//space_pressed = wait_until_space_pressed(g_event);

		if (space_pressed == true)
			p_player.do_player();


		// Update render
		SDL_RenderPresent(g_screen);

		int real_time = fps_time.get_ticks();
		int	time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame)
		{
			SDL_Delay(time_per_frame - real_time);
		}

		// kiểm tra va chạm
		is_die = check_collision( 119, p_player.get_y_pos(), p_pipe_up1.get_x_pos(), p_pipe_up1.get_y_pos(),
						 p_pipe_up2.get_x_pos(), p_pipe_up2.get_y_pos(), pipe1_pass, pipe2_pass);
		if (is_die == true)
		{
			
			
 			Mix_PlayChannel( -1, g_hit, 0 );
			Sleep(400);
			Mix_PlayChannel( -1, g_die, 0 );
			//PIPE_VELOCITY = 0;
			pipe_vel = 0;
			SDL_Delay(1200);

			//SDL_RenderPresent(g_screen);
			bool play_again = die_menu.show_menu_die(g_screen, score);
			if (play_again == true)
			{
				pipe_vel = 4;
				p_pipe_up1.set_val(800, -100);
				p_pipe_down1.set_val(800, 320);
				p_pipe_up2.set_val(1000, -80);
				p_pipe_down2.set_val(1000, 340 );
				score = 0;
				p_player.set_rect_main_object(START_X_POS, START_Y_POS);

				space_pressed = false;
				p_player.set_angle(0);

			}
			else
			{
				is_quit = true;
			}

		}


	}

	close();

	return 0;
}


//-----------------------------------------------------
bool init()
{

	bool success = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return false;
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	g_window = SDL_CreateWindow( "Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
		return false;
	//tạo render cho biến g_screen
	g_screen = SDL_CreateRenderer(g_window, 1, SDL_RENDERER_ACCELERATED);

	if (g_screen == NULL)
		return false;
	SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

	int img_flag = IMG_INIT_PNG;
	if ( !(IMG_Init(img_flag) && img_flag))
		return false;
	if (TTF_Init() == -1)
		return false;

	score_font = TTF_OpenFont("font/ARCADE_N.ttf", 35);

	if (score_font == NULL)
		return false;

	return true;
}

//============================

bool init_audio()
{

	if ( Mix_OpenAudio( 48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1 ) == -1)
		return false;

	// đọc file wav
	g_hit = Mix_LoadWAV( "sound/hit.wav" );
	g_wing = Mix_LoadWAV( "sound/wing.wav" );
	g_die = Mix_LoadWAV( "sound/die.wav" );
	g_point = Mix_LoadWAV( "sound/point.wav" );
	Mix_Volume(-1, 8);

	return true;
}

//------------------------------------------------------
bool load_background(std::string path)
{
	bool ret = g_background.load_image(path.c_str(), g_screen);
	if (ret == false)
		return false;
	return true;
}

//------------------------------------------------

void close()
{
	g_background.free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

