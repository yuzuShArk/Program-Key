#include "keyboard.hpp"
#include "pico/stdlib.h"

#include <array>
#include <cstdio>
#include <vector>

const char *keycode_name(KeyCode key) {
    switch (key) {
    case KeyCode::A:
        return "A";
    case KeyCode::B:
        return "B";
    case KeyCode::C:
        return "C";
    case KeyCode::D:
        return "D";
    case KeyCode::Enter:
        return "Enter";
    case KeyCode::Space:
        return "Space";
    case KeyCode::Escape:
        return "Escape";
    }
    return "Unknown";
}

int main() {
    stdio_init_all();

    Keyboard keyboard;
    std::array<bool, 256> states{};

    sleep_ms(3000);

    for (int step = 0; step < 4; ++step) {
        if (step == 1) {
            states[0] = true;
        } else if (step == 3) {
            states[0] = false;
        }

        const std::vector<KeyEvent> events = keyboard.update(states);

        printf("Step %d:\n", step + 1);

        if (events.empty()) {
            printf("No event!\n");
        }

        for (const auto &event : events) {
            const char *type =
                event.type == KeyEventType::KeyDown ? "KeyDown" : "KeyUp";
            printf("%s: %s\n", type, keycode_name(event.key));
        }
        sleep_ms(1000);
    }
    while (true) {
        tight_loop_contents();
    }
}

/*
    1. create a Class "Keyboard" object called keyboard, initialized 256
   electrode_states to false
    2. first time calling update(): all electrode_states should be false, so no
   events
    3. second time calling update(): set state[0] to true(pressed down), so
   KeyDown::A
    4. third time calling update(): keep pressing donw A, so no events
    5. fourth time calling update(): set state[0] back to false, so KeyUp::auto
*/
