#pragma once

#include "CommonFunction.h"

class TextObject 
{
public:
	TextObject ();
	~TextObject ();

	bool load_text_texture(SDL_Renderer *des, TTF_Font *font);
	void free();

	void set_color ( Uint8 r, Uint8 g, Uint8 b);
	void render_text ( SDL_Renderer *screen,
					   int x_pos, int y_pos,
					   SDL_Rect *clip = NULL,
					   double angle = 0.0,
					   SDL_Point *center = NULL,
					   SDL_RendererFlip flip = SDL_FLIP_NONE);

	int get_w_text() const { return text_w_; }
	int get_h_text() const { return text_h_; }
	void set_text(std::string &text) { str_val_ = text; }
	std::string get_text() const { return str_val_; }

private:
	std::string str_val_;
	SDL_Color text_color_;
	SDL_Texture *text_texture_;

	int text_w_;
	int text_h_;
};




