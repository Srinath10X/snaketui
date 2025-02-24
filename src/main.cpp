#include <handlers/terminal_handler.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>

TerminalHandler terminal;

class SnakeGame {
private:
  bool game_over = false;

  char dir = ' ';
  std::vector<std::string> grid;
  std::vector<std::pair<int, int>> tail;
  int score = 0, height, width, headX, headY, foodX, foodY;

public:
  void run();
  void logic();
  void render();
  void initalize();
  void handleInput();
  void displayResults();
};

void SnakeGame::initalize() {
  srand(static_cast<unsigned>(time(nullptr)));
  width = terminal.width - 2;
  height = terminal.height - 3;

  headX = width / 2;
  headY = height / 2;
  foodX = rand() % width;
  foodY = rand() % height;
}

void SnakeGame::render() {
  terminal.clear();
  grid.clear();
  grid.resize(height, std::string(width, ' '));

  grid[headY][headX] = 'O';
  grid[foodY][foodX] = 'F';

  for (auto &pair : tail) {
    grid[pair.second][pair.first] = '0';
  }

  std::cout << std::string(width + 2, '#') << std::endl;

  for (auto &row : grid) {
    auto temp = row;
    temp.erase(0, 1);
    temp.erase(row.size() - 1, 1);
    std::cout << "#" << temp << "#" << std::endl;
  }
  std::cout << std::string(width + 2, '#') << std::endl;
}

void SnakeGame::handleInput() {
  if (terminal.kbhit()) {
    char c = getchar();
    if (c == 'h' && dir != 'R')
      dir = 'L';
    else if (c == 'l' && dir != 'L')
      dir = 'R';
    else if (c == 'k' && dir != 'D')
      dir = 'U';
    else if (c == 'j' && dir != 'U')
      dir = 'D';
    else if (c == 'x')
      game_over = true;
  }
}

void SnakeGame::logic() {
  if (!tail.empty()) tail.insert(tail.begin(), {headX, headY}), tail.pop_back();

  if (dir == 'L')
    headX--;
  else if (dir == 'R')
    headX++;
  else if (dir == 'U')
    headY--;
  else if (dir == 'D')
    headY++;

  if (headX < 0 || headX >= width || headY < 0 || headY >= height) game_over = true;
  for (auto &[x, y] : tail)
    if (x == headX && y == headY) game_over = true;

  if (headX == foodX && headY == foodY) {
    score += 10;
    foodX = rand() % width, foodY = rand() % height;
    tail.push_back({headX, headY});
  }
}

void SnakeGame::displayResults() { std::cout << "Your Score: " << score << std::endl; }

void SnakeGame::run() {
  SnakeGame::initalize();
  terminal.enableRawMode();
  while (!game_over) {
    SnakeGame::render();
    SnakeGame::handleInput();
    SnakeGame::logic();
    usleep(100000);
  }
  terminal.disableRawMode();
  displayResults();
}

int main(int argc, char *argv[]) {
  SnakeGame snake_game;
  terminal.init();
  snake_game.run();
  return 0;
}
