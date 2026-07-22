#include "platform/graphics.hpp"
#include "config.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cstddef>

Renderer::Renderer() : sprite_(texture_) {
  window_.create(sf::VideoMode({conf::WINDOW_WIDTH, conf::WINDOW_HEIGHT}),
                 "emulator-6502");
  window_.clear(sf::Color::Black);
  window_.setFramerateLimit(conf::FRAMERATE);

  auto passed = texture_.resize({conf::DISPLAY_COLS, conf::DISPLAY_ROWS});

  sprite_.setTexture(texture_);
  sprite_.setTextureRect(
      sf::IntRect({0, 0}, {conf::DISPLAY_COLS, conf::DISPLAY_ROWS}));
  sprite_.setScale({static_cast<float>(conf::SCREEN_SCALE),
                    static_cast<float>(conf::SCREEN_SCALE)});

  rgba_buffer_.resize(conf::DISPLAY_COLS * conf::DISPLAY_ROWS * 4, 255);
}

void Renderer::draw(const disp_array &screen) {

  for (std::size_t i = 0; i < screen.size(); i++) {
    std::size_t rgba_index = i * 4;
    if (screen[i]) {
      std::copy(conf::COLOR_ON.begin(), conf::COLOR_ON.end(),
                rgba_buffer_.begin() + rgba_index);
    } else {
      std::copy(conf::COLOR_OFF.begin(), conf::COLOR_OFF.end(),
                rgba_buffer_.begin() + rgba_index);
    }
  }
  texture_.update(rgba_buffer_.data());
  window_.clear(sf::Color::Black);
  window_.draw(sprite_);
  window_.display();
}

bool Renderer::is_running() {
  bool is_running = true;
  while (const std::optional event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();
      is_running = false;
    } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
        window_.close();
        is_running = false;
      }
    }
  }
  return is_running;
}