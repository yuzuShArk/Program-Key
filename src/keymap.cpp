#include "keymap.hpp"
#include <optional>

std::optional<KeyCode> get_keycode(std::uint8_t electrode_id) {
  switch (electrode_id) {
  case 0:
    return KeyCode::A;
    break;
  case 1:
    return KeyCode::B;
    break;
  case 2:
    return KeyCode::C;
    break;
  case 3:
    return KeyCode::D;
    break;
  case 4:
    return KeyCode::Enter;
    break;
  case 5:
    return KeyCode::Space;
    break;
  case 6:
    return KeyCode::Escape;
    break;
  default:
    return std::nullopt;
  }
}
