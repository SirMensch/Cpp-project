#ifndef __KEYBOARD_INPUT_H__
#define __KEYBOARD_INPUT_H__

#include "config.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>

using keypad_array = std::array<bool, conf::KEYPAD_SIZE>;

class KeyboardHandler {
public:
  keypad_array get_keys_pressed() const {
    keypad_array keys_pressed{};

    for (std::size_t i = 0; i < conf::KEYPAD_SIZE; i++) {
      bool pressed = sf::Keyboard::isKeyPressed(conf::KEY_MAP[i]);
      keys_pressed[i] = pressed;
    }

    return keys_pressed;
  }
};

#endif // __KEYBOARD_INPUT_H__