#include "../drivers/screen.h"

int main() {
  screen_clear();
  screen_print("Hello it is my longest string i've ever made, so now it "
               "can't work anymore. Even more longer");

  return 0;
}
