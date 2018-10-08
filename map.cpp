#include <iostream>
#include "pixel.h"
#include "map.h"
#include "snake.h"

namespace snake {

Map::Map(uint32_t w, uint32_t h)
    : width_(w),
      height_(h) {
    Create();
}

void Map::Create() {
    std::cout << "Creating Map width(" 
    << width_ << "), height(" 
    << height_ << ")" << std::endl;

    for (uint32_t h_i = 0; h_i < height_; ++h_i) {
        for (uint32_t w_i = 0; w_i < width_; ++w_i) {
            if (h_i == 0 || h_i == (height_ - 1)
                || w_i == 0 || w_i == (width_ - 1)) {
                object_.push_back(Pixel(h_i, w_i, '+'));
            }
            else {
                object_.push_back(Pixel(h_i, w_i, ' '));
            }
        }
    }
}

}
