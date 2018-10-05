#include <iostream>
#include "map.h"
#include "snake.h"

using namespace snake;

int main() {
    Map basic_map(32, 16);
    Snake snake(Snake::Part(2, 2));

    basic_map.Draw(snake);

    char c;
    bool isQuit = false;
    while (!isQuit && std::cin >> c) {
	    switch(c) {
		case 'a':
		    snake.MoveLeft();
		    basic_map.Draw(snake);
		    break;
		case 'd':
		    snake.MoveRight();
		    basic_map.Draw(snake);
		    break;
		case 'w':
		    snake.MoveUp();
		    basic_map.Draw(snake);
		    break;
		case 's':
		    snake.MoveDown();
		    basic_map.Draw(snake);
		    break;
		case 'q':
		    isQuit = true;
		    break;
	    }

    }
    // basic_map.Create();    

    return 0;
}
