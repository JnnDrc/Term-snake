
#include "input.h"

void enable_nbi(){
  #ifndef _WIN32
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

  #endif
}

void disable_nbi() {
  #ifndef _WIN32
    struct termios oldt;

    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  #endif
}

int get_key(){
  #ifdef _WIN32
    if (_kbhit()){
      return _getch();
    }
    return 0;
  #else 
  char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        if (ch == 27) {
            char seq[2];
            if (read(STDIN_FILENO, seq, 2) == 2) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': return 1000;
                        case 'B': return 1001;
                        case 'C': return 1002;
                        case 'D': return 1003;
                    }
                }
            }
        }
        return ch;
    }
    return 0;
  #endif
}
