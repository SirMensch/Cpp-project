//
// Created by larsl on 2/9/2024.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#ifndef INVERSEPENDLE_HEADERS_EVENTHANDLER_H_
#define INVERSEPENDLE_HEADERS_EVENTHANDLER_H_

inline int handleLeftAndRightClick(sf::Event::KeyPressed &event) {
  if (event.code == sf::Keyboard::Key::Right) {
#if DEBUG
    std::cout << "Pressed right.\n";
#endif
    return 1;
  } else if (event.code == sf::Keyboard::Key::Left) {
#if DEBUG
    std::cout << "Pressed left.\n";
#endif
    return -1;
  } else {
    return 0;
  }
}

#endif // INVERSEPENDLE_HEADERS_EVENTHANDLER_H_
