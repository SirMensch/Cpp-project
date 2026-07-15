#pragma once
#include <array>
#include <cstdint>

template <typename T> T extract_bits(T input, uint8_t start, uint8_t length);

struct Instruction {
private:
  uint16_t data = 0;

public:
  Instruction();
  Instruction(uint16_t inst) : data(inst) {};
  void update_instruction(uint16_t inst) { data = inst; };
  const uint16_t get_x() { return extract_bits(data, 0x8, 0x4); };
  const uint16_t get_y() { return extract_bits(data, 0x4, 0x4); };
  const uint16_t get_n() { return extract_bits(data, 0x0, 0x4); };
  const uint16_t get_nn() { return extract_bits(data, 0x0, 0x8); };
  const uint16_t get_nnn() { return extract_bits(data, 0x0, 0xC); };
  const uint16_t get_opc() { return extract_bits(data, 0xC, 0x4); };
};

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

  Instruction instruction_;
  void get_next_instruction();
  void execute_cls(); // TODO
  void execute_jp_addr();
  void execute_call_addr();
  void execute_ret();

public:
  CPU();
  ~CPU();

  void reset();
  void load_program(const uint8_t *program, std::size_t size);
  void execute_instruction();
};