#include <constants.hpp>
#include <csignal>
#include <fcntl.h>
#include <handlers/terminal_handler.hpp>
#include <iostream>
#include <unistd.h>

struct termios TerminalHandler::term;
struct winsize TerminalHandler::window;

void TerminalHandler::init() {
  tcgetattr(STDIN_FILENO, &term);
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  TerminalHandler::width = window.ws_col;
  TerminalHandler::height = window.ws_row;
}

void TerminalHandler::enableRawMode() {
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  std::cout << WIPE_SCREEN << HIDE_CURSOR;
}

void TerminalHandler::disableRawMode() {
  term.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  std::cout << WIPE_SCREEN << SHOW_CURSOR;
}

bool TerminalHandler::kbhit() {
  int fnctl = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, fnctl | O_NONBLOCK);
  int ch = getchar();
  fcntl(STDIN_FILENO, F_SETFL, fnctl);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return true;
  }
  return false;
}

void TerminalHandler::clear() { std::cout << WIPE_SCREEN << RESET; }
