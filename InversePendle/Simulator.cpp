//
// Created by larsl on 1/22/2024.
//

#include "Simulator.h"

std::shared_ptr<sf::RenderWindow> Simulator::get_window() {
  return window;
}

bool Simulator::render() {
  bool finish = false;
  // check all the window's events that were triggered since the last iteration of the loop
  sf::Event event;
  while (window->pollEvent(event)) {
    // "close requested" event: we close the window
    if (event.type == sf::Event::Closed)
      window->close();
  }

  // clear the window with black color
  window->clear(sf::Color::Black);

  // draw everything here...
  // window.draw(...);

  // end the current frame
  window->display();

  if(!window->isOpen()) {
    return true;
  }
  return false;
}

Simulator::Simulator() {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Inverse Pendulum");
  window->setActive(true);
}
bool Simulator::addObject(Object& object) {
  objects.push_back(std::make_shared<Object>(object));
  return false;
}
