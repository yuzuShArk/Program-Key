#ifndef KEYMAP_HPP
#define KEYMAP_HPP

#include <cstdint>
#include <optional>

enum class KeyCode : std::uint8_t { A, B, C, D, Enter, Space, Escape };

std::optional<KeyCode> get_keycode(std::uint8_t electrode_id);

#endif
