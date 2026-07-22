#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

namespace conf {

#if ENABLE_MASTER_DEBUG
inline constexpr spdlog::level::level_enum SPDLOG_LEVEL = spdlog::level::trace;
#else
inline constexpr spdlog::level::level_enum SPDLOG_LEVEL = spdlog::level::info;
#endif

inline constexpr std::size_t CPU_CYC_PER_FPS = 10;

inline constexpr std::size_t REGISTER_SIZE = 16;
inline constexpr std::size_t STACK_SIZE = 16;
inline constexpr std::size_t MEMORY_SIZE = 4096;
inline constexpr std::size_t KEYPAD_SIZE = 16;

inline constexpr std::size_t INDEX_REGISTER_START = 0x0;
inline constexpr std::size_t STACK_POINTER_START = 0x0;
inline constexpr std::uint16_t PROGRAM_COUNTER_START = 0x200;

inline constexpr std::size_t DISPLAY_ROWS = 32;
inline constexpr std::size_t DISPLAY_COLS = 64;
inline constexpr std::size_t BITS_PER_BYTE = 8;

inline constexpr std::size_t FRAMERATE = 60;
inline constexpr std::size_t SCREEN_SCALE = 20;
inline constexpr std::size_t WINDOW_WIDTH = DISPLAY_COLS * SCREEN_SCALE;
inline constexpr std::size_t WINDOW_HEIGHT = DISPLAY_ROWS * SCREEN_SCALE;

inline constexpr std::array<std::uint8_t, 4> COLOR_OFF = {51, 255, 51, 255};
inline constexpr std::array<std::uint8_t, 4> COLOR_ON = {15, 15, 15, 255};

inline constexpr std::array<sf::Keyboard::Key, KEYPAD_SIZE> KEY_MAP = {
    sf::Keyboard::Key::X,    // 0x0
    sf::Keyboard::Key::Num1, // 0x1
    sf::Keyboard::Key::Num2, // 0x2
    sf::Keyboard::Key::Num3, // 0x3
    sf::Keyboard::Key::Q,    // 0x4
    sf::Keyboard::Key::W,    // 0x5
    sf::Keyboard::Key::E,    // 0x6
    sf::Keyboard::Key::A,    // 0x7
    sf::Keyboard::Key::S,    // 0x8
    sf::Keyboard::Key::D,    // 0x9
    sf::Keyboard::Key::Z,    // 0xA
    sf::Keyboard::Key::C,    // 0xB
    sf::Keyboard::Key::Num4, // 0xC
    sf::Keyboard::Key::R,    // 0xD
    sf::Keyboard::Key::F,    // 0xE
    sf::Keyboard::Key::V     // 0xF
};

} // namespace conf

using disp_array = std::array<uint8_t, conf::DISPLAY_COLS * conf::DISPLAY_ROWS>;
