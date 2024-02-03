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
  for (auto &object : objects){
    window->draw(*object->getRectangle());
  }
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
bool Simulator::addPlatform(Platform &platform) {
  objects.push_back(std::make_shared<Platform>(platform));
  return false;
}
bool Simulator::addStick(Stick &stick) {
  objects.push_back(std::make_shared<Stick>(stick));
  return false;
}

