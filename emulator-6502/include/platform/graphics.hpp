#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#pragma once
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstdint>
#include <vector>

class Renderer {
private:
  sf::RenderWindow window_;
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::vector<uint8_t> rgba_buffer_;

public:
  Renderer();
  void draw(const disp_array &screen);
  bool is_running();
};

#endif // __GRAPHICS_H__