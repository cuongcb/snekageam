#include <iostream>
#include "map.h"
#include "snake.h"

namespace snake {

Map::Map(uint32_t w, uint32_t h)
    : width_(w),
      height_(h) {}

void Map::Create() {
    std::cout << "Creating Map width(" 
    << width_ << "), height(" 
    << height_ << ")" << std::endl;

    for (auto h_i = 0; h_i < height_; ++h_i) {
        for (auto w_i = 0; w_i < width_; ++w_i) {
            if (h_i == 0 || h_i == (height_ - 1)) {
                std::cout << "+";
            }
            else if (w_i == 0 || w_i == (width_ - 1)) {
                std::cout << "+";
            }
            else {
                std::cout << " ";
            }

            if (w_i == width_ - 1) {
                std::cout << std::endl;
            }
        }
    }
}

void Map::Draw(uint32_t x, uint32_t y) {
    for (auto h_i = 0; h_i < height_; ++h_i) {
        for (auto w_i = 0; w_i < width_; ++w_i) {
            if (h_i == 0 || h_i == (height_ - 1)) {
                std::cout << "+";
            }
            else if (w_i == 0 || w_i == (width_ - 1)) {
                std::cout << "+";
            }
            else if (x == w_i && y == h_i) {
                std::cout << "o";
            }
            else {
                std::cout << " ";
            }

            if (w_i == width_ - 1) {
                std::cout << std::endl;
            }
        }
    }
}

void Map::Draw(const Snake &snake) {
    Snake::Part head = snake.head();
    Draw(head.pos_x_, head.pos_y_);
}

}