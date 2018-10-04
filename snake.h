#pragma once

#include <cstdint>
#include <vector>

namespace snake {

class Snake {
public:
    struct Part {
        Part(uint32_t pos_x, uint32_t pos_y)
            : pos_x_(pos_x),
              pos_y_(pos_y) {}

        uint32_t pos_x_;
        uint32_t pos_y_;
    };

    Snake(Part head);
    Part head() const;
private:
    static constexpr uint32_t kVelocity = 1;
    std::vector<Part> snake_;
};

}