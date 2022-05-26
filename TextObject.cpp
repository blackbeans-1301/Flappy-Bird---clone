#include "stdafx.h"
#include "TextObject.h"

TextObject ::TextObject ()
{
	text_w_ = 0;
	text_h_ = 0;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;

	text_texture_ = NULL;

}

TextObject ::~TextObject ()
{
	free();
}


bool TextObject ::load_text_texture(SDL_Renderer *des, TTF_Font *font)
{
	// Tạo text surface
	free();
	SDL_Surface *text_surface = TTF_RenderText_Solid ( font, str_val_.c_str(), text_color_);
	 
	if (text_surface)
	{
		text_texture_ = SDL_CreateTextureFromSurface(des, text_surface);
		text_w_ = text_surface->w;
		text_h_ = text_surface->h;
	}

	SDL_FreeSurface(text_surface);

	return text_texture_ != NULL;
}


//=======================


void TextObject::set_color(Uint8 r, Uint8 g, Uint8 b)
{
	text_color_.r = r;
	text_color_.g = g;
	text_color_.b = b;
}

//==========================

void TextObject::free()
{
	if (text_texture_ != NULL)
	{
		SDL_DestroyTexture(text_texture_);
		text_texture_ = NULL;
	}
}

//=====================

void TextObject ::render_text ( SDL_Renderer *screen,
					   int x_pos, int y_pos,
					   SDL_Rect *clip,
					   double angle /* độ nghiêng text */,
					   SDL_Point *center,
					   SDL_RendererFlip flip)
{
	SDL_Rect renderquad = { x_pos, y_pos, text_w_, text_h_ };
	if (clip != NULL)
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, text_texture_, clip, &renderquad, angle, center, flip); 

}