#pragma once

#include "BaseObject.h"
#include "CommonFunction.h"

class GameMenu : public BaseObject
{
public:
	GameMenu();
	~GameMenu();
	bool load_image(std::string path, SDL_Renderer *screen);
	virtual bool show_menu_start (SDL_Renderer *des);
	virtual bool show_menu_die (SDL_Renderer *des, unsigned short int &score);
	virtual bool check_mouse_focus_start (int x, int y, SDL_Rect &rect);
	virtual bool check_mouse_focus_die (int x, int y, SDL_Rect &rect);

private:

	int x_;
	int y_;

	int width_;
	int height_;

	int xm;
	int ym;
};
