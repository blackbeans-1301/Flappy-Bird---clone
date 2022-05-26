#pragma once

#include "CommonFunction.h"
//#include "MainObject.h"
#include "BaseObject.h"

class PipeOject : public BaseObject
{
public:
	PipeOject();
	~PipeOject();

	//khởi tạo giá trị cho pos_x và pos_y
	void set_val(int pos_x, int pos_y);
	// lấy vị trí của ống
	int get_x_pos() const { return x_pos_; }
	int get_y_pos() const { return y_pos_; }
	//hàm load ảnh của ống
	bool load_image(std::string path, SDL_Renderer *screen);

	//hàm show ảnh của ống trên
	void show_pipe_up(SDL_Renderer *des, int pipe_vel); 
	//hàm show hình ảnh của ống dưới
	void show_pipe_down(SDL_Renderer *des, int pipe_vel);

	//xử lý va chạm của bird và ống
	void check_to_map();

private:

	//tốc độ di chuyển sang trái của ống
	float x_val_;

	//vị trí hiện tại của ống
	float x_pos_;
	float y_pos_;

	//kích thước ống
	int w_frame_;
	int h_frame_;


};
