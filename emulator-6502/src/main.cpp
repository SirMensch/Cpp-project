#include "config.hpp"
#include "cpu/cpu.hpp"
#include "platform/graphics.hpp"
#include "platform/keyboard_input.hpp"
#include "platform/rom_loader.hpp"
#include "spdlog/spdlog.h"
#include <cstddef>
#include <cstdint>

int main(int argc, char **argv) {

  spdlog::set_pattern("[%T.%e|%L] %v");
  spdlog::set_level(conf::SPDLOG_LEVEL);

  std::string filename;
  if (argc < 2) {
    spdlog::error("Please add a filename as first argument.");
  } else {
    filename = argv[1];
  }

  KeyboardHandler keyboard_handler;
  Renderer renderer;
  CPU cpu;

  std::vector<uint8_t> rom = read_rom_file(filename);

  cpu.load_program(rom, rom.size());

  while (renderer.is_running()) {

    cpu.load_keyboard(keyboard_handler.get_keys_pressed());

    for (std::size_t i = 0; i < conf::CPU_CYC_PER_FPS; i++) {
      cpu.execute_instruction();
    }

    renderer.draw(cpu.get_display());
  }

  return 0;
}