#ifndef TERMINAL_HANDLER_HPP
#define TERMINAL_HANDLER_HPP

#include <sys/ioctl.h>
#include <termios.h>

class TerminalHandler {
private:
  static struct termios term;
  static struct winsize window;

public:
  unsigned width;
  unsigned height;

  void init();
  bool kbhit();
  void clear();
  static void enableRawMode();
  static void disableRawMode();
  static void signalHandler(int);
  static void registerSignalHandler();
};

#endif
