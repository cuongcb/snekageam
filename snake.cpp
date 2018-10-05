#include "pixel.h"
#include "snake.h"

namespace snake {

Snake::Snake() {
	Snake_Part_t head = make_head(kDefaultX, kDefaultY);
    snake_.push_back(std::move(head));
}

void Snake::Eat() {
	Snake_Part_t tail = make_body(kDefaultX, kDefaultY);
	snake_.push_back(std::move(tail));
}

void Snake::MoveLeft(uint32_t leftborder) {
	auto it = snake_.begin();
	auto lastIt = it;
	(*it)->MoveLeftWithCare(kVelocity, leftborder);
	while (++it != snake_.end()) {
		(*it)->JumpTo((*lastIt));
		lastIt = it;
	}
}

void Snake::MoveRight(uint32_t rightborder) {
	auto it = snake_.begin();
	auto lastIt = it;
	(*it)->MoveRightWithCare(kVelocity, rightborder);
	while (++it != snake_.end()) {
		(*it)->JumpTo((*lastIt));
		lastIt = it;
	}
}

void Snake::MoveUp(uint32_t topborder) {
	auto it = snake_.begin();
	auto lastIt = it;
	(*it)->MoveUpWithCare(kVelocity, topborder);
	while (++it != snake_.end()) {
		(*it)->JumpTo((*lastIt));
		lastIt = it;
	}
}

void Snake::MoveDown(uint32_t bottomborder) {
	auto it = snake_.begin();
	auto lastIt = it;
	(*it)->MoveDownWithCare(kVelocity, bottomborder);
	while (++it != snake_.end()) {
		(*it)->JumpTo((*lastIt));
		lastIt = it;
	}
}

Snake_Part_t Snake::make_head(uint32_t x, uint32_t y, char symbol) const {
	return Snake_Part_t(new Pixel(x, y, symbol));
}

Snake_Part_t Snake::make_body(uint32_t x, uint32_t y, char symbol) const {
	return Snake_Part_t(new Pixel(x, y, symbol));
}

}