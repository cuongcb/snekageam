#pragma once
#include <cstdint>

#include "object.h"

namespace snake {

class Snake;

class Map: public Object {
public:
    explicit Map(uint32_t w, uint32_t h);
    void Create();
    void Draw();
private:
    uint32_t width_;
    uint32_t height_;
};

}
