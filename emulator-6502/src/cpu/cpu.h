#pragma once
#include <array>
#include <cstdint>

template <uint8_t start, uint8_t length, typename T> T extract_bits(T input);

enum class OPC {
  SYS = 0x0,  // system
  JP = 0x1,   // jump
  CALL = 0x2, // call address
  SE = 0x3,   // skip if equal
  SNE = 0x4,  // skip if not equal
  LD = 0x6,   // load const in reg
  ADD = 0x7,  // add to reg
  R2RM = 0x8  // reg to reg math
};

enum class ALU {
  LD = 0x0,  // load reg into reg
  OR = 0x1,  // bitwise or
  AND = 0x2, // bitwise and
  XOR = 0x3, // bitwise xor
};

struct Instruction {
private:
  uint16_t data = 0;

public:
  Instruction();
  Instruction(uint16_t inst) : data(inst) {};
  void update_instruction(uint16_t inst) { data = inst; };
  uint16_t get_x() { return extract_bits<0x8, 0x4>(data); };
  uint16_t get_y() { return extract_bits<0x4, 0x4>(data); };
  ALU get_n() { return static_cast<ALU>(extract_bits<0x0, 0x4>(data)); };
  uint16_t get_nn() { return extract_bits<0x0, 0x8>(data); };
  uint16_t get_nnn() { return extract_bits<0x0, 0xC>(data); };
  OPC get_opc() { return static_cast<OPC>(extract_bits<0xC, 0x4>(data)); };
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

  Instruction instruction_ = Instruction(0x0);
  void get_next_instruction();
  void execute_sys();
  void execute_cls(); // TODO
  void execute_jp_addr();
  void execute_call_addr();
  void execute_skip_eq();
  void execute_skip_not_eq();
  void execute_ret();
  void execute_ld();
  void execute_add();
  void execute_alu();

public:
  CPU();
  ~CPU();

  void reset();
  void load_program(const uint8_t *program, std::size_t size);
  void execute_instruction();
};