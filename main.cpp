#include <iostream>
#include "map.h"
#include "snake.h"

using namespace snake;

int main() {
    Map basic_map(32, 16);
    Snake snake(Snake::Part(1, 1));

    basic_map.Draw(snake);
    // basic_map.Create();    

    return 0;
}