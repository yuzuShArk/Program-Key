#include "keyboard.hpp"

std::vector<KeyEvent> Keyboard::update(std::uint8_t electrode_id,
                                       bool touched) {
  std::vector<KeyEvent> events;

  const auto key = get_keycode(electrode_id);

  if (!key.has_value()) { // from std::optional(included in keymap.hpp)
    return events;
  }

  const bool previous_state = electrode_states[electrode_id];
  if (previous_state != touched) {
    if (touched) {
      events.push_back({KeyEventType::KeyDown, *key});
    } else {
      events.push_back({KeyEventType::KeyUp, *key});
    }
    electrode_states[electrode_id] = touched; // previous state = state now
  }
  return events;
}
