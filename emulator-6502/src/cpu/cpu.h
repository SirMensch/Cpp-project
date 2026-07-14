#pragma once
#include <array>
#include <cstdint>

class CPU {
private:
  static constexpr std::size_t REGISTER_SIZE = 16;
  static constexpr std::size_t STACK_SIZE = 16;
  static constexpr std::size_t MEMORY_SIZE = 4096;

  static constexpr std::size_t INDEX_REGISTER_START = 0x0;
  static constexpr std::size_t STACK_POINTER_START = 0x0;
  static constexpr uint16_t PROGRAM_COUNTER_START = 0x200;

  std::array<uint8_t, REGISTER_SIZE> registers_{};
  std::array<uint16_t, STACK_SIZE> stack_{};
  std::array<uint8_t, MEMORY_SIZE> memory_{};

  uint16_t index_register_{INDEX_REGISTER_START};
  uint16_t program_counter_{PROGRAM_COUNTER_START};
  uint8_t stack_pointer_{STACK_POINTER_START};

public:
  CPU();
  ~CPU();

  void reset();
  void load_program(const uint8_t *program, std::size_t size);
  void execute_instruction();
};