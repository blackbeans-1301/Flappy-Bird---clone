#include "stdafx.h"
#include "BaseObject.h"
//---------------------------------------------
BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject( )
{
	free();
}

//---------------------------------------------

bool BaseObject::load_image(std::string path, SDL_Renderer *screen )
{
	free();
	//biến kết quả
	SDL_Texture *new_texture = NULL;

	// load_surface được load bởi IMG_load
	SDL_Surface *load_surface = IMG_Load(path.c_str());

	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface -> format, COLORKEY_R, COLORKEY_G, COLORKEY_B));
		
		// new_texture được thừa hưởng tất cả thuộc tính của tấm ảnh từ load_surface
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);

		if (new_texture != NULL)
		{
			// gán chiều rộng của bức ảnh vào rect_.w
			rect_.w = load_surface->w;

			// gán chiều cao của bức ảnh vào rect_.h
			rect_.h = load_surface->h;
		}

		// giải phóng dung lượng load_surface
		SDL_FreeSurface( load_surface );
	}
	
	p_object_ = new_texture;
	
	/*nếu p_object_ = NULL thì return true
	!= NULL thì return false*/
	return p_object_ != NULL;
}
//------------------------------------------

void BaseObject::render( SDL_Renderer *des, const SDL_Rect *clip )
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

	//đẩy các thông số của p_object vào des
	SDL_RenderCopy( des, p_object_, clip, &renderquad ); 
}

//------------------------------------------------

void BaseObject::free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}