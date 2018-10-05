#pragma once

#include <algorithm>
#include <cstdint>

namespace snake {

namespace {
    const uint32_t kMinimumPixel = 1;
}

class Pixel {
public:
    friend bool IsCollision(const Pixel &a, const Pixel &b);

    Pixel(uint32_t x, uint32_t y, char symbol = ' ')
        : pos_x_(x),
          pos_y_(y),
          symbol_(symbol) {}

    virtual char symbol() const {
        return symbol_;
    }

    void MoveLeft(uint32_t velocity) {
        pos_x_ -= velocity;
    }

    void MoveLeftWithCare(uint32_t velocity, uint32_t leftmost) {
        pos_x_ -= velocity;
        pos_x_ = std::max(pos_x_, leftmost + kMinimumPixel);
    }

    void MoveRight(uint32_t velocity) {
        pos_x_ += velocity;
    }

    void MoveRightWithCare(uint32_t velocity, uint32_t rightmost) {
        pos_x_ += velocity;
        pos_x_ = std::min(pos_x_, rightmost - kMinimumPixel);
    }

    void MoveUp(uint32_t velocity) {
        pos_y_ -= velocity;
    }

    void MoveUpWithCare(uint32_t velocity, uint32_t upmost) {
        pos_y_ -= velocity;
        pos_y_ = std::max(pos_y_, upmost + kMinimumPixel);
    }

    void MoveDown(uint32_t velocity) {
        pos_y_ += velocity;
    }

    void MoveDownWithCare(uint32_t velocity, uint32_t downmost) {
        pos_y_ += velocity;
        pos_y_ = std::min(pos_y_, downmost - kMinimumPixel);
    }

    void JumpTo(uint32_t x, uint32_t y) {
        pos_x_ = x;
        pos_y_ = y;
    }

    void JumpTo(const Pixel &target) {
        JumpTo(target.pos_x_, target.pos_y_);
    }

protected:
    uint32_t pos_x_;
    uint32_t pos_y_;
private:
    char symbol_;
};

bool IsCollision(const Pixel &a, const Pixel &b) {
    return (a.pos_x_ == b.pos_x_ &&
            a.pos_y_ == b.pos_y_);
}

}