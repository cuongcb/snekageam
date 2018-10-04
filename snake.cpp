#include "snake.h"

namespace snake {

Snake::Snake(Part head) {
    snake_.push_back(head);
}

Snake::Part Snake::head() const {
    return snake_.front();
}

}