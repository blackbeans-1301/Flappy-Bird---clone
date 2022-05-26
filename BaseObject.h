#pragma once
#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();



	// set vị trí cho rect_
	void set_rect( const int &x, const int &y) {rect_.x = x; rect_.y = y; }

	//lấy vị trí của rect_
	SDL_Rect get_rect() const { return rect_; }

	// get object
	SDL_Texture *get_object() const { return p_object_; }
	
	// Hàm load ảnh vào đối tượng p_object_
	virtual bool load_image ( std::string path, SDL_Renderer *screen );

	// render 
	void render( SDL_Renderer *des /*renderer đến đâu(destination)*/, const SDL_Rect *clip);
	void free();

protected:
	// biến lưu trữ hình ảnh trong game
	SDL_Texture *p_object_;
	//biến lưu trữ kích thước và vị trí ảnh
	SDL_Rect	rect_;
};
