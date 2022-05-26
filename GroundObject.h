#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"



class GroundObject : public BaseObject
{
public:
	GroundObject();
	~GroundObject();

	// lấy vị trí của ground
	int get_x() const { return x_pos_; }
	int get_y() const { return y_pos_; }

	bool load_image( std::string path, SDL_Renderer *des );
	void show_ground( std::string path, SDL_Renderer *des );

	void set_pos(int x, int y) { x_pos_ = x; y_pos_ = y; }

private:
	// tốc độ di chuyển sang trái của ground
	float x_val;
	// vị trí của ground
	float x_pos_;
	float y_pos_;

	// kích thước của ground
	float width;
	float heigh;

};