#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "keymap.hpp"

#include <array>
#include <cstdint>
#include <vector>

enum class KeyEventType { KeyDown, KeyUp };

struct KeyEvent {
  KeyEventType type;
  KeyCode key;
};

class Keyboard {
public:
  std::vector<KeyEvent> update(std::uint8_t electrode_id,
                               bool touched); // use vector to query keys that
                                              // are pressed at different times

private:
  std::array<bool, 256> electrode_states{};
};

#endif
