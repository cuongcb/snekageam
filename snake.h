#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace snake {

class Pixel;

class Snake {
public:
    Snake();

    // motion
    void MoveLeft(uint32_t leftborder);
    void MoveRight(uint32_t rightborder);
    void MoveUp(uint32_t topborder);
    void MoveDown(uint32_t bottomborder);

    // action
    void Eat();
private:
    static constexpr uint32_t kVelocity = 1;
    static constexpr uint32_t kDefaultX = 1;
    static constexpr uint32_t kDefaultY = 1;

    typedef std::unique_ptr<Pixel> Snake_Part_t;
    typedef std::vector<Snake_Part_t> Snake_t;

    Snake_Part_t make_head(uint32_t x, uint32_t y, char symbol = 'o') const;

    Snake_Part_t make_body(uint32_t x, uint32_t y, char symbol = '.') const;

    Snake_t snake_;
};

}
