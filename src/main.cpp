#include "keymap.hpp"

#include <cstdint>
#include <iostream>

int main() {
  for (std::uint8_t electrode = 0; electrode < 8; ++electrode) {
    const auto key = get_keycode(electrode);

    std::cout << "Electrode " << static_cast<int>(electrode) << ": ";

    if (key.has_value()) {
      std::cout << "Mapped\n";
    } else {
      std::cout << "Unmapped\n";
    }
  }

  return 0;
}
