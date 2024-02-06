#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#define FRAMERATE 60
#define DEBUG false

struct TTT {
  std::vector<sf::RectangleShape> recs;
  std::vector<bool> reds;
  std::vector<bool> blues;
  TTT() : recs(9), reds(9, false), blues(9, false) {}
};

// vector of all possible solutions
std::vector<std::vector<int8_t>>
    results{{0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7}, {2, 4, 6}, {2, 5, 8}, {3, 4, 5}, {6, 7, 8}};

std::shared_ptr<sf::RenderWindow> createWindow() {

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  std::shared_ptr<sf::RenderWindow>
      window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "TicTacToe", sf::Style::Default, settings);
  window->setVerticalSyncEnabled(true);
  window->setFramerateLimit(FRAMERATE);
  window->clear(sf::Color::Black);
  window->display();
  return window;
}

void startScreen(const std::shared_ptr<sf::RenderWindow> &window, const sf::Font &font) {
#if DEBUG
  std::cout << "Start Start screen.\n";
#endif
  sf::Text startText("Welcome to TicTacToe\n\n\nTo start the game press C.", font, 20);
  startText.setFillColor(sf::Color::White);

  auto center = sf::Vector2f(startText.getGlobalBounds().width, startText.getGlobalBounds().height) / 2.f;
  startText.setOrigin(center);
  startText.setPosition(sf::Vector2f{window->getSize() / 2u});

  bool con = true;
  while (window->isOpen() && con) {
    sf::Event event{};
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::C) {
          con = false;
        }
      }
    }

    window->clear(sf::Color::Black);
    window->draw(startText);
    window->display();
  }
#if DEBUG
  std::cout << "Leave Start screen.\n";
#endif
}

void winnerScreen(const std::shared_ptr<sf::RenderWindow> &window, const sf::Font &font, int winner) {

#if DEBUG
  std::cout << "Start Winner screen.\n";
#endif

  sf::Text winnerText("", font, 20);
  if (winner == 1) {
    winnerText.setString("Congratulations Blue. Press C to end game.");
  } else if (winner == 0) {
    winnerText.setString("Congratulations Red. Press C to end game.");
  } else {
    winnerText.setString("Nobody won. Press C to end game.");
  }

  winnerText.setFillColor(sf::Color::Yellow);

  auto center = sf::Vector2f(winnerText.getGlobalBounds().width, winnerText.getGlobalBounds().height) / 2.f;
  winnerText.setOrigin(center);
  winnerText.setPosition(sf::Vector2f{window->getSize() / 2u});

  while (window->isOpen()) {
    sf::Event event{};
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
      if (event.type == sf::Event::KeyPressed) {
        window->close();
      }
    }

    window->clear(sf::Color::Black);
    window->draw(winnerText);
    window->display();
  }
#if DEBUG
  std::cout << "Leave Start screen.\n";
#endif
}

bool checkFinished(std::vector<bool> fields) {
  for (std::vector<int8_t> &result : results) {
    bool possible_solution = true;
    for (int8_t number : result) {
      if (!fields[number]) {
        possible_solution = false;
        break;
      }
#if DEBUG
      std::cout << fields[number] << " " << number << std::endl;
#endif
    }
    if (possible_solution) {
#if DEBUG
      std::cout << "solution found" << result[0] << " " << result[1] << " " << result[2] << std::endl;
#endif
      return true;
    }
  }
  return false;
}

bool updateField(TTT &rectangles, sf::Vector2i &mouse_position, bool turn_blue) {
#if DEBUG
  std::cout << "updateField" << std::endl;
#endif

  for (int i = 0; i < 9; i++) {
    if (rectangles.recs[i].getGlobalBounds().contains(float(mouse_position.x), float(mouse_position.y))) {
      if (rectangles.blues[i] || rectangles.reds[i])
        return false;
      if (turn_blue) {
        rectangles.recs[i].setFillColor(sf::Color::Blue);
        rectangles.blues[i] = true;
      } else {
        rectangles.recs[i].setFillColor(sf::Color::Red);
        rectangles.reds[i] = true;
      }
      return true;
    }
  }
  return false;
}

int handleLMBPress(TTT &rectangles, sf::Vector2i &mouse_position, sf::Text &start_text, bool &turn_blue) {
  static uint8_t filled_fields = 0;
  if (updateField(rectangles, mouse_position, turn_blue)) {
    filled_fields += 1;
#if DEBUG
    std::cout << "Free Press found.";
#endif
    if (turn_blue) {
      if (checkFinished(rectangles.blues))
        return 1;
      start_text.setFillColor(sf::Color::Red);
      start_text.setString("Red please pick a field.");
    } else {
      if (checkFinished(rectangles.reds))
        return 1;
      start_text.setFillColor(sf::Color::Blue);
      start_text.setString("Blue please pick a field.");
    }
    turn_blue -= 1;
  }
  if (filled_fields == 9)
    return -1;
  return 0;
}
int tictactoeScreen(const std::shared_ptr<sf::RenderWindow> &window, const sf::Font &font) {

  bool turn_blue = true;
  sf::Text start_text("Blue please pick a field.", font, 20);
  start_text.setFillColor(sf::Color::Blue);
#if DEBUG
  std::cout << "TicTacToe screen.\n";
#endif
  // setup position for start_text
  auto centerText = sf::Vector2f(start_text.getGlobalBounds().width, start_text.getGlobalBounds().height) / 2.f;
  start_text.setOrigin(centerText);
  start_text.setPosition(sf::Vector2f{float(window->getSize().x), centerText.y + 10} / 2.f);

  // setup rectangles
  TTT rectangles;
  auto size_window = sf::Vector2f(window->getSize());
  size_window.x /= 2.f;
  size_window.y /= 2.f;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      auto pos =
          sf::Vector2f(size_window) + sf::Vector2f(float(120 * (i - 1)), float(120 * (j - 1))) - sf::Vector2f(50, 50);
      rectangles.recs[3 * i + j].setSize(sf::Vector2f(100.f, 100.f));
      rectangles.recs[3 * i + j].setPosition(pos);
      rectangles.recs[3 * i + j].setFillColor(sf::Color::White);
    }
  }

  // first draw
  window->clear(sf::Color::Black);
  window->draw(start_text);
  for (const auto &rec : rectangles.recs) {
    window->draw(rec);
  }
  window->display();

  bool con = true;
  while (window->isOpen() && con) {
    sf::Event event{};
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::C) {
          con = false;
        }
      }
      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
#if DEBUG
        std::cout << mousePosition.x << "  " << mousePosition.y << std::endl;
#endif
        int finished = handleLMBPress(rectangles, mousePosition, start_text, turn_blue);
        if (finished == 1) {
          return turn_blue;
        } else if (finished == -1) {
          return -1;
        }

        window->clear(sf::Color::Black);
        window->draw(start_text);
        for (const auto &rec : rectangles.recs) {
          window->draw(rec);
        }
        window->display();

      }
    }
  }
#if DEBUG
  std::cout << "Leave TicTacToe screen.\n";
#endif
  return -1;
}

int main() {
  // create window
  auto window = createWindow();

  // Load it from a file
  sf::Font font;
  font.loadFromFile(R"(res/fonts/arial.ttf)");

  startScreen(window, font);

  int winner = tictactoeScreen(window, font);

  winnerScreen(window, font, winner);

  return 0;
}