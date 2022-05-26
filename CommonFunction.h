#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h> 
#include <cstdlib>
#include <ctime>


//hàm xử lý va chạm

bool check_collision( const int x_bird, const int &y_bird, const int &x_pipe1, const int &y_pipe1,
					 const int &x_pipe2, const int &y_pipe2, const bool &pass1, const bool &pass2);
bool wait_until_space_pressed (SDL_Event event);

bool check_mouse_focus_pause (int xm, int ym, SDL_Rect &rect);
bool check_mouse_focus_mute (int xm, int ym, SDL_Rect &rect);

int random(int min, int max);

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_screen = NULL;  
static SDL_Event g_event;

// bién quản lý âm thanh
static Mix_Chunk *g_wing = NULL;
static Mix_Chunk *g_hit = NULL;
static Mix_Chunk *g_die = NULL;
static Mix_Chunk *g_point = NULL;

// BIRD
#define BIRD_W 34
#define BIRD_H 24
const int START_X_POS = 119;
const int START_Y_POS = 232;

//screen
#define FPS 50

#define SCREEN_W 338
#define SCREEN_H 600
#define	SCREEN_BPP 32

// color key
#define COLORKEY_R 140
#define COLORKEY_G 129
#define COLORKEY_B 141

// physic
#define FALL_SPEED 0.6
#define FLY_UP 6
#define ANGLE_FALL 3


// ground
#define GROUND_H 112
#define GROUND_W 426

#define GROUND_Y_POS 488
// pipe up
#define LOWEST_PIPE_UP 320
#define HIGHEST_PIPE_UP 120
#define PIPE_W 50
#define PIPE_H 320
static int PIPE_VELOCITY = 4;

#define NEW_X_POS 352

//rendom value
#define MIN 120
#define MAX 320

typedef struct input
{
	int jump_;
	int left_;
	int right_;
};