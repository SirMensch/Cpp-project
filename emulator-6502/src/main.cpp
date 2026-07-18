#include "cpu/cpu.hpp"
#include "platform/graphics.hpp"
#include "platform/keyboard_input.hpp"
#include "platform/rom_loader.hpp"
#include <cstdint>

int main(int argc, char **argv) {

  std::string filename;
  if (argc < 2) {
    std::cerr << "Please give rom file." << std::endl;
    return -1;
  } else {
    filename = argv[1];
  }

  KeyboardHandler keyboard_handler;
  Renderer renderer;
  CPU cpu;

  std::vector<uint8_t> rom = read_rom_file(filename);

  cpu.load_program(rom, rom.size());

  while (true) {

    renderer.handle_events();

    cpu.load_keyboard(keyboard_handler.get_keys_pressed());

    cpu.execute_instruction();

    renderer.draw(cpu.get_display());
  }

  return 0;
}