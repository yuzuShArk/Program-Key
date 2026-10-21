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
  std::vector<KeyEvent> update(const std::array<bool, 256> &current_states);

private:
  std::array<bool, 256> electrode_states{};
};

#endif
