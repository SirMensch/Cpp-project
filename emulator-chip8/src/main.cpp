#include "config.hpp"
#include "cpu/cpu.hpp"
#include "platform/graphics.hpp"
#include "platform/keyboard_input.hpp"
#include "platform/rom_loader.hpp"
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {

  spdlog::set_pattern("[%T.%e|%L] %v");
  spdlog::set_level(conf::SPDLOG_LEVEL);

  std::string filename;
  if (argc < 2) {
    spdlog::error("Please add a filename as first argument.");
    return -1;
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

// get solutions
#include <filesystem>
#include <fstream>
  auto pixels = cpu.get_display();
  std::filesystem::path absolute_dir =
      "/home/ryuuma/repos/Cpp-project/emulator-6502/tests/solutions";
  if (!std::filesystem::exists(absolute_dir)) {
    std::filesystem::create_directories(absolute_dir);
  }

  std::filesystem::path p(filename);
  std::string filename_o = p.filename().stem().string() + ".bin";

  std::filesystem::path full_path = absolute_dir / filename_o;

  std::ofstream file(full_path, std::ios::binary);
  if (file.is_open()) {
    file.write(reinterpret_cast<const char *>(pixels.data()), pixels.size());
  }

  return 0;
}
