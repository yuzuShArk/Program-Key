#include "keyboard.hpp"
#include <cstddef>

std::vector<KeyEvent>
Keyboard::update(const std::array<bool, 256> &current_states) {
    std::vector<KeyEvent> events;

    for (std::size_t i = 0; i < current_states.size(); ++i) {
        const bool previous_state = electrode_states[i];
        const bool current_state = current_states[i];
        if (previous_state != current_state) {
            const auto key = get_keycode(static_cast<std::uint8_t>(i));
            if (key.has_value()) {
                if (current_state) {
                    events.push_back({KeyEventType::KeyDown, *key});
                } else {
                    events.push_back({KeyEventType::KeyUp, *key});
                }
            }
            electrode_states[i] = current_state;
        }
    }
    return events;
}
