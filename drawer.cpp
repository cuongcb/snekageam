#include <iostream>

#include "drawer.h"
#include "object.h"
#include "pixel.h"

namespace snake {

Drawer::Drawer(uint32_t r, uint32_t c)
	: row_(r),
	  col_(c) {
	for (uint32_t r_i = 0; r_i < row_; ++r_i) {
		std::vector<Pixel> pixels;
		for (uint32_t c_i = 0; c_i < col_; ++c_i) {
			pixels.push_back(Pixel(r_i, c_i));
		}

		image_buffer_.push_back(pixels);
	}
}

void Drawer::Add(const Object &obj) {
	objects_.push_back(obj);
}

void Drawer::Start() const {
	ClearScreen();
	NewLine();
	for (const auto obj: objects_) {
		Rewind();
		obj.Float(image_buffer_);
	}

	DrawInternal();
}

void Drawer::ClearScreen() const {
	std::cout << "\x1B[2J";
}

void Drawer::NewLine() const {
	std::cout << "\n";
}

void Drawer::Rewind() const {
	std::cout << "\x1B[H";
}

void Drawer::DrawInternal() {
	for (uint32_t r_i = 0; r_i < row_; ++r_i) {
		for (uint32_t c_i = 0; c_i < col_; ++c_i) {
			std::cout << image_buffer_[r_i][c_i].symbol();
		}
		NewLine();
	}
}

} // snake