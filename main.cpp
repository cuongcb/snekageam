#include <iostream>
#include "map.h"
#include "snake.h"

using namespace snake;

class Drawer;

int main() {
	Drawer drawer = Drawer();	
    Map map(32, 16);
    Snake snake(Snake::Part(2, 2));

	drawer.Add(map);
	drawer.Add(snake);
	drawer.Add(food);
	drawer.Start();

    char c;
    bool isQuit = false;
    while (!isQuit && std::cin >> c) {
	    switch(c) {
		case 'a':
		    snake.MoveLeft();
		    map.Draw(snake);
		    break;
		case 'd':
		    snake.MoveRight();
		    map.Draw(snake);
		    break;
		case 'w':
		    snake.MoveUp();
		    map.Draw(snake);
		    break;
		case 's':
		    snake.MoveDown();
		    map.Draw(snake);
		    break;
		case 'q':
		    isQuit = true;
		    break;
	    }
    }
    // map.Create();    

    return 0;
}
