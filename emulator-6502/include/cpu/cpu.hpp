#ifndef __CPU_H__
#define __CPU_H__

#include "platform/graphics.hpp"
#pragma once
#include "config.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <random>
#include <spdlog/spdlog.h>

template <typename T>
constexpr T extract_bits(uint8_t start, uint8_t length, T input) {
  static_assert(std::is_integral_v<T>, "Template type must be an integer");
  const uint8_t type_bits = sizeof(T) * 8;
  assert((start + length <= type_bits) ||
         (spdlog::error(" | start: {} | length: {}", +start, +length), false));

  if (length == type_bits) {
    return input;
  }
  T mask = (static_cast<T>(1) << length) - 1;
  return (input >> start) & mask;
}

template <uint8_t start, uint8_t length, typename T>
constexpr T extract_bits(T input) {
  static_assert(start + length <= sizeof(T) * 8,
                "Length exceeds data type size");
  return extract_bits<T>(start, length, input);
}

enum class OPC {
  SYS = 0x0,     // system
  JP = 0x1,      // jump
  CALL = 0x2,    // call address
  SE = 0x3,      // skip if equal
  SNE = 0x4,     // skip if not equal
  SE_R2R = 0x5,  // skif if  equal reg to reg
  LD = 0x6,      // load const in reg
  ADD = 0x7,     // add to reg
  R2RM = 0x8,    // reg to reg math
  SNE_R2R = 0x9, // skif if not equal reg to reg
  LD_I = 0xA,    // load const to index reg
  JP_V0 = 0xB,   // jump by register0 + nnn
  RND = 0xC,     // generate random
  DRW = 0xD,     // draw screen
  KEY = 0xE,     // key board press
  MISC = 0xF     // misc -> time and sound
};

enum class ALU {
  LD = 0x0,   // load reg into reg
  OR = 0x1,   // bitwise or
  AND = 0x2,  // bitwise and
  XOR = 0x3,  // bitwise xor
  ADD = 0x4,  // add with carry
  SUB = 0x5,  // subtract
  SHR = 0x6,  // shift right
  SUBN = 0x7, // reverse substract
  SHL = 0xE   // shift left
};

struct Instruction {
private:
  uint16_t data_ = 0;

public:
  Instruction();
  Instruction(uint16_t inst) : data_(inst) {};
  void update_instruction(uint16_t inst) { data_ = inst; };
  uint16_t get_x() { return extract_bits<0x8, 0x4>(data_); };
  uint16_t get_y() { return extract_bits<0x4, 0x4>(data_); };
  ALU get_alu_inst() {
    return static_cast<ALU>(extract_bits<0x0, 0x4>(data_));
  };
  uint8_t get_n() { return extract_bits<0x0, 0x4>(data_); };
  uint16_t get_nn() { return extract_bits<0x0, 0x8>(data_); };
  uint16_t get_nnn() { return extract_bits<0x0, 0xC>(data_); };
  OPC get_opc() { return static_cast<OPC>(extract_bits<0xC, 0x4>(data_)); };
};

class CPU {
private:
  std::random_device rd_{};
  std::mt19937 rng_{rd_()};
  std::uniform_int_distribution<uint16_t> dist_{0, 255};

  std::array<uint8_t, conf::REGISTER_SIZE> registers_{};
  std::array<uint16_t, conf::STACK_SIZE> stack_{};
  std::array<uint8_t, conf::MEMORY_SIZE> memory_{};
  disp_array display_{};
  std::array<bool, conf::KEYPAD_SIZE> keypad_{};

  uint16_t index_register_{conf::INDEX_REGISTER_START};
  uint16_t program_counter_{conf::PROGRAM_COUNTER_START};
  uint8_t stack_pointer_{conf::STACK_POINTER_START};
  uint8_t delay_timer_{0};
  uint8_t sound_timer_{0};

  Instruction instruction_ = Instruction(0x0);

  uint8_t &status_reg() { return registers_[0xF]; }

  void get_next_instruction();
  void execute_sys();
  void execute_cls();
  void execute_ret();
  void execute_jp_addr();
  void execute_call_addr();
  void execute_skip_eq();
  void execute_skip_not_eq();
  void execute_se_r2r();
  void execute_ld();
  void execute_add();
  void execute_alu();
  void execute_sne_r2r();
  void execute_ld_i();
  void execute_jp_v0();
  void execute_rnd();
  void execute_drw();
  void execute_key();
  void execute_misc();

public:
  CPU();
  ~CPU() = default;

  void reset();
  void load_program(const std::vector<uint8_t> &program, std::size_t size);
  void load_keyboard(const std::array<bool, conf::KEYPAD_SIZE> &keys);
  void execute_instruction();
  const disp_array &get_display() const { return display_; };
};
#endif // __CPU_H__