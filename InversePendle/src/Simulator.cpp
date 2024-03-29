//
// Created by larsl on 1/22/2024.
//

#include "Simulator.h"

Simulator::Simulator(int framerate) {
  window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Inverse Pendulum");
  // Check if the window was created successfully
  if (!window_->isOpen()) {
    std::cerr << "Failed to create SFML window." << std::endl;
  }
  window_->setActive(true);
  window_->setFramerateLimit(framerate);
  framerate_ = framerate;
}

std::shared_ptr<sf::RenderWindow> Simulator::get_window() {
  return window_;
}
/**
 *
 * @return says if rendering is finished -> it crashed or was closed
 */
bool Simulator::render() {
#if EXT_FORCE
  int force_direction = 0;
#endif
  if (inverse_pendulum_ == nullptr) {
    std::cout << "No Pendulum" << std::endl;
    return true;
  }
  // check all the window's events that were triggered since the last iteration of the loop
  sf::Event event = *new sf::Event();
  while (window_->pollEvent(event)) {
    // "close requested" event: we close the window
    if (event.type == sf::Event::Closed)
      window_->close();
#if EXT_FORCE
    if (event.type == sf::Event::KeyPressed) {
      force_direction = handleLeftAndRightClick(event.key);
    }
#endif
  }

  // clear the window with black color
  window_->clear(sf::Color::Black);

  // draw everything here...
#if EXT_FORCE
  float force = 10.f * G * float(force_direction); // button press is 1e6 N
  for (auto &object : inverse_pendulum_->update(1.f / float(framerate_), force, 10)) {
#else
    for (auto &object : inverse_pendulum_->update(1.f / float(framerate_))) {
#endif
    window_->draw(*object->getRectangle());
  }
  // window.draw(...);

  // end the current frame
  window_->display();

  if (!window_->isOpen()) {
    return true;
  }
  return false;
}
void Simulator::addInversePendulum(InversePendulum &inverse_pendulum) {
  inverse_pendulum_ = std::make_shared<InversePendulum>(inverse_pendulum);
}










