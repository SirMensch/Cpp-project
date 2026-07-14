#include "cpu.h"
#include <stdexcept>

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