#include "keyboard.hpp"

#include <iostream>

int main() {
  Keyboard keyboard;

  const auto print_events = [](const auto &events) {
    for (const auto &event : events) {
      if (event.type == KeyEventType::KeyDown) {
        std::cout << "KeyDown!" << std::endl;
      } else {
        std::cout << "KeyUp" << std::endl;
      }
    }
  };

  print_events(keyboard.update(0, false)); // let go
  print_events(keyboard.update(0, true));  // touched
  print_events(keyboard.update(0, true));  // keep touching
  print_events(keyboard.update(0, true));  // keep touching
  print_events(keyboard.update(0, false)); // let go

  return 0;
}
