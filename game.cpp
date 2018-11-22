#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

typedef std::vector<std::vector<char> > Map_t;

struct Coord {
	Coord(uint32_t r, uint32_t c)
		: pos_x(r),
		  pos_y(c) {}

	Coord(const Coord &c) {
		pos_x = c.pos_x;
		pos_y = c.pos_y;
	}

	bool operator==(const Coord &c) const {
		return (pos_x == c.pos_x && pos_y == c.pos_y);
	}

	uint32_t pos_x;
	uint32_t pos_y;
};

enum Direction: int32_t {
	DIR_LEFT = -2,
	DIR_UP = -1,
	DIR_NONE = 0,
	DIR_DOWN = 1,
	DIR_RIGHT = 2,
};

Direction gDir = Direction::DIR_NONE;
std::mutex gMutex;

class Random {
public:
	Random() {
		rng_.seed(std::random_device()());
	}		

	int32_t Distribute(int32_t from, int32_t to) {
		std::uniform_int_distribution<std::mt19937::result_type> dist(from, to);

		return dist(rng_);
	}

private:
	std::mt19937 rng_;
};

class Snake;

class Border {
public:
	Border(uint32_t row, uint32_t col)
		: symbol_('+') {
		for (uint32_t c_i = 0; c_i < col; ++c_i) {
			border_.push_back(Coord(0, c_i));
			border_.push_back(Coord(row - 1, c_i));
		}

		for (uint32_t r_i = 0; r_i < row; ++r_i) {
			border_.push_back(Coord(r_i, 0));
			border_.push_back(Coord(r_i, col - 1));	
		}
	}

	void Draw(Map_t &map) const {
		for (const auto &b: border_) {
			map[b.pos_x][b.pos_y] = symbol_;
		}
	}

private:
	char symbol_;
	std::vector<Coord> border_;
};


class Food {
public:
	friend bool IsCollision(const Snake &s, const Food &f);

	Food(uint32_t row, uint32_t col)
		: symbol_('*'),
		coord_(Coord(row, col)) {}

	void Draw(Map_t &map) const {
		map[coord_.pos_x][coord_.pos_y] = symbol_;
	}

private:
	char symbol_;
	Coord coord_;
};

class Snake {
public:
	friend bool IsCollision(const Snake &s, const Food &f);
	friend bool IsHitWall(const Snake &s);
	Snake()
		: dir_(Direction::DIR_NONE),
		symbol_('o'),
		snake_(std::vector<Coord>(1, Coord(1, 1))) {}

	// Action
	void Move(Direction dir) {
		if (!IsValid(dir)) {
			return;
		}
		MoveSnakeBody();
		MoveSnakeHead(dir);
		
		dir_ = dir;
	}

	void Eat() {
		snake_.push_back(Coord(snake_.front()));
	}

	void Draw(Map_t &map) const {
		for (const auto &s: snake_) {
			map[s.pos_x][s.pos_y] = symbol_;
		}
	}
private:
	void MoveSnakeBody() {
		for (auto body = snake_.rbegin(),
			prev = body; ++body != snake_.rend();) {
			*prev = *body;
			prev = body;
		}
	}

	void MoveSnakeHead(Direction dir) {
		auto head = snake_.begin();
		switch (dir) {
			case Direction::DIR_UP:
				head->pos_x -= 1;
				break;
			case Direction::DIR_DOWN:
				head->pos_x += 1;
				break;
			case Direction::DIR_LEFT:
				head->pos_y -= 1;
				break;
			case Direction::DIR_RIGHT:
				head->pos_y += 1;
				break;
			default:
				break;
		}
	}

	bool IsValid(Direction dir) {
		if (dir_ + dir == 0) {
			return false;
		}
		
		return true;
	}

	Direction dir_;
	char symbol_;
	std::vector<Coord> snake_;
};

Map_t CreateMap(uint32_t row, uint32_t col) {
	Map_t map = std::vector<std::vector<char> >(row, std::vector<char>(col, ' '));
	return map;
}

void DrawMap(const Border &b, const Snake &s, const Food &f) {
	Map_t map = CreateMap(16, 16);
	b.Draw(map);
	s.Draw(map);
	f.Draw(map);

	auto row = map.size();
	auto col = map[0].size();	

	for (auto r_i = 0; r_i < row; ++r_i) {
		for (auto c_i = 0; c_i < col; ++c_i) {
			std::cout << map[r_i][c_i];
		}
		std::cout << "\n";
	}
}

bool IsCollision(const Snake &s, const Food &f) {
	if (s.snake_.front() == f.coord_) {
		return true;
	}	

	return false;
}

bool IsHitWall(const Snake &s) {
	auto head = s.snake_.front();
	if (head.pos_x == 0 || head.pos_x == 15
		|| head.pos_y == 0 || head.pos_y == 15) {
			return true;
		}

	return false;
}

void ClearScreen() {
	std::cout << "\x1B[2J\n\x1B[H";
}

void Sleep(uint32_t ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void KeyHandler() {
	char c;
	bool isQuit = false;
	while (!isQuit && std::cin >> c) {
		switch (c) {
			case 'h':
			{
				std::lock_guard<std::mutex> lock(gMutex);
				gDir = Direction::DIR_LEFT;
				break;
			}
			case 'l':
			{
				std::lock_guard<std::mutex> lock(gMutex);
				gDir = Direction::DIR_RIGHT;
				break;
			}
			case 'j':
			{
				std::lock_guard<std::mutex> lock(gMutex);
				gDir = Direction::DIR_DOWN;
				break;
			}
			case 'k':
			{
				std::lock_guard<std::mutex> lock(gMutex);
				gDir = Direction::DIR_UP;
				break;
			}
			case 'q':
				isQuit = true;
				break;
			default:
				break;
		}
	}
}

void GameOver() {
	std::cout << "You Lose!!!" << std::endl;
	std::cout << "Press 'q' to Quit..." << std::endl;
}

int main(void) {
	bool isQuit = false;

	Random r = Random();
	Border border = Border(16, 16);
	Snake snake = Snake();
	Food food = Food(r.Distribute(1, 14), r.Distribute(1, 14));

	std::thread eventHandler(KeyHandler);

	while (!isQuit) {
		ClearScreen();
		if (IsCollision(snake, food)) {
			snake.Eat();
			food = Food(r.Distribute(1, 14), r.Distribute(1, 14));
		}
		{
			std::lock_guard<std::mutex> lock(gMutex);
			snake.Move(gDir);
		}
		DrawMap(border, snake, food);
		if (IsHitWall(snake)) {
			break;
		}
		Sleep(500); // 1s
	}

	GameOver();

	eventHandler.join();

	return 0;
}