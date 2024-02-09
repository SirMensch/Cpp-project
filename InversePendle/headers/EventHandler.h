//
// Created by larsl on 2/9/2024.
//

#include "SFML/Window/Event.hpp"

#ifndef INVERSEPENDLE_HEADERS_EVENTHANDLER_H_
#define INVERSEPENDLE_HEADERS_EVENTHANDLER_H_

inline int handleLeftAndRightClick(sf::Event::KeyEvent &event) {
  if (event.code == sf::Keyboard::Right) {
#if DEBUG
    std::cout << "Pressed right.\n";
#endif
    return 1;
  } else if (event.code == sf::Keyboard::Left) {
#if DEBUG
    std::cout << "Pressed left.\n";
#endif
    return -1;
  } else {
    return 0;
  }
}

#endif //INVERSEPENDLE_HEADERS_EVENTHANDLER_H_
