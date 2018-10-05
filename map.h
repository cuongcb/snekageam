#pragma once
#include <cstdint>

namespace snake {

class Snake;

class Map {
public:
    Map(uint32_t w, uint32_t h);
    void Create();
    void Clear() const;
    void Draw(uint32_t x, uint32_t y);
    void Draw(const Snake &snake);
private:
    uint32_t width_;
    uint32_t height_;
};

}
