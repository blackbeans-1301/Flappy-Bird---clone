#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"

//#define FALL_

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum walk_type
	{

		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		JUMP = 2,

	};


	bool load_image( std::string path, SDL_Renderer *screen);
	virtual void show( SDL_Renderer *des );
	void handle_input (SDL_Event events, SDL_Renderer *screen, Mix_Chunk *wing);
	// hàm xử lý hiệu ứng animation
	void set_clip();
	void set_angle(const int angl) { angle = angl; }
	void set_rect_main_object(const int xp, const int yp) { x_pos_ = xp; y_pos_ = yp; }
 	int get_x_pos() const { return x_pos_; }
	int get_y_pos() const { return y_pos_; }
	// hàm xử lý di chuyển
	void do_player();
	// hàm xử lý va chạm
	virtual void check_to_map();

private:
	// xu ly do nghiem cua chim
	int angle;
	// tốc độ di chuyển sang trái phải
	float x_val_;
	// tốc độ di chuyển lên xuống
	float y_val_;

	// vị trí x, y hiện tại
	float x_pos_;
	float y_pos_;

	// kích thước của MainObject
	int w_frame_;
	int h_frame_;

	// mảng dùng để lưu dữ liệu về frame
	SDL_Rect frame_clip_[3];

	//trạng thái khi press key
	input input_type_;

	//biến lưu chỉ số frame của object
	int frame_;
	
	//trạng thái di chuyển (trái, phải)
	int status_;

	int delay_frame_;

};