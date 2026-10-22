#include "keyboard.hpp"

#include <array>
#include <iostream>

int main() {
    Keyboard keyboard;
    std::array<bool, 256> states{};

    // first time: not pressed
    auto events = keyboard.update(states);
    std::cout << "after first update: " << events.size() << std::endl;

    // second time: press down elec 0->A
    states[0] = true;
    events = keyboard.update(states);
    std::cout << "pressed A, event counter:" << events.size() << std::endl;

    // third time: keep pressing A
    events = keyboard.update(states);
    std::cout << "pressed A, event counter:" << events.size() << std::endl;

    // fourth time: release A
    states[0] = false;
    events = keyboard.update(states);
    std::cout << "pressed A, event counter:" << events.size() << std::endl;

    return 0;
}
