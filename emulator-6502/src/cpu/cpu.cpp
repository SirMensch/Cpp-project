#include "cpu.h"
#include <cstdint>
#include <stdexcept>

template <typename T> T extract_bits(T input, uint8_t start, uint8_t length) {
  // compile time assess
  constexpr uint8_t type_bits = sizeof(T) * 8;
  static_assert(std::is_integral<T>::value, "Template type must be an integer");
  static_assert(start < type_bits, "Start position exceeds data type size");
  static_assert(length <= type_bits, "Length exceeds data type size");

  if (start >= type_bits || length == 0) {
    return 0;
  }
  T mask = (static_cast<T>(1) << length) - 1;
  return (input >> start) & mask;
}

CPU::CPU() { reset(); }

void CPU::reset() {
  registers_.fill(0);
  stack_.fill(0);
  memory_.fill(0);

  index_register_ = INDEX_REGISTER_START;
  program_counter_ = PROGRAM_COUNTER_START;
  stack_pointer_ = STACK_POINTER_START;
}

void CPU::load_program(const uint8_t *program, std::size_t size) {
  if (size > MEMORY_SIZE - PROGRAM_COUNTER_START) {
    throw std::runtime_error("Program size exceeds available memory.");
  }
  std::copy(program, program + size, memory_.begin() + PROGRAM_COUNTER_START);
}

void CPU::get_next_instruction() {
  uint16_t instruction = 0x0;
  instruction |= memory_[program_counter_++] << 8; // MSB
  instruction |= memory_[program_counter_++];      // LSB
  instruction_.update_instruction(instruction);
}

void CPU::execute_instruction() {
  get_next_instruction();
  uint8_t opc = instruction_.get_opc();

  switch (opc) {
  case 0x0: {
    uint16_t nn = instruction_.get_nn();
    if (nn == 0xEE) {
      execute_ret();
    } else if (nn == 0xE0) {
      execute_cls();
    }
    break;
  }
  case 0x1: {
    execute_jp_addr();
    break;
  }
  case 0x2: {
   execute_call_addr();
   break;
  }
  default:
    break;
  }
}

void CPU::execute_jp_addr() { program_counter_ = instruction_.get_nnn(); }

void CPU::execute_call_addr() {
  if (stack_pointer_ >= STACK_SIZE) {
    throw std::runtime_error(
        "Stack overflow: Maximum nested subroutine depth exceeded.");
  }
  stack_[stack_pointer_] = program_counter_;
  stack_pointer_++;
  uint16_t nnn = instruction_.get_nnn();
  program_counter_ = nnn;
}

void CPU::execute_ret() {
  if (stack_pointer_ == 0) {
    throw std::runtime_error(
        "Stack underflow: Attempted to return without an active subroutine.");
  }
  stack_pointer_--;
  program_counter_ = stack_[stack_pointer_];
}