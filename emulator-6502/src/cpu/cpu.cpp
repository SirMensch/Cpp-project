#include "cpu.h"
#include <cstdint>
#include <stdexcept>
#include <sys/types.h>

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
  OPC opc = instruction_.get_opc();

  switch (opc) {
  case OPC::SYS: {
    execute_sys();
    break;
  }
  case OPC::JP: {
    execute_jp_addr();
    break;
  }
  case OPC::CALL: {
    execute_call_addr();
    break;
  }
  case OPC::SE: {
    execute_skip_eq();
    break;
  }
  case OPC::SNE: {
    execute_skip_not_eq();
    break;
  }
  case OPC::LD: {
    execute_ld();
    break;
  }
  case OPC::ADD: {
    execute_add();
    break;
  }
  case OPC::R2RM: {
    execute_alu();
    break;
  }
  case OPC::SNE_R2R: {
    execute_sne_r2r();
    break;
  }
  case OPC::LD_I: {
    execute_ld_i();
    break;
  }
  case OPC::JP_V0: {
    execute_jp_v0();
    break;
  }
  case OPC::RND: {
    execute_rnd();
    break;
  }
  case OPC::DRW: {
    execute_drw();
    break;
  }
  case OPC::MISC: {
    execute_misc();
    break;
  }
  default:
    break;
  }
}

void CPU::execute_sys() {
  uint16_t nn = instruction_.get_nn();
  if (nn == 0xEE) {
    execute_ret();
  } else if (nn == 0xE0) {
    execute_cls();
  }
}

void CPU::execute_cls() {} // TODO

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

void CPU::execute_ld() {
  uint8_t x = instruction_.get_x();
  uint8_t nn = instruction_.get_nn();
  registers_[x] = nn;
}

void CPU::execute_add() {
  uint8_t x = instruction_.get_x();
  uint8_t nn = instruction_.get_nn();
  registers_[x] += nn;
}

void CPU::execute_skip_eq() {
  uint8_t x = instruction_.get_x();
  uint8_t nn = instruction_.get_nn();
  if (registers_[x] == nn) {
    program_counter_ += 2;
  }
}

void CPU::execute_skip_not_eq() {
  uint8_t x = instruction_.get_x();
  uint8_t nn = instruction_.get_nn();
  if (registers_[x] != nn) {
    program_counter_ += 2;
  }
}

void CPU::execute_alu() {
  uint8_t x = instruction_.get_x();
  uint8_t y = instruction_.get_y();
  ALU alu = instruction_.get_alu_inst();
  switch (alu) {
  case ALU::LD: {
    registers_[x] = registers_[y];
    break;
  }
  case ALU::OR: {
    registers_[x] |= registers_[y];
    break;
  }
  case ALU::AND: {
    registers_[x] &= registers_[y];
    break;
  }
  case ALU::XOR: {
    registers_[x] ^= registers_[y];
    break;
  }
  case ALU::ADD: {
    uint16_t sum = static_cast<uint16_t>(registers_[x]) +
                   static_cast<uint16_t>(registers_[y]);
    uint8_t flag = (sum >> 8) ? 1 : 0;
    registers_[x] = static_cast<uint8_t>(sum & 0xFF);
    status_reg() = flag;
    break;
  }
  case ALU::SUB: {
    uint8_t flag = (registers_[x] < registers_[y]) ? 0 : 1;
    registers_[x] -= registers_[y];
    status_reg() = flag;
    break;
  }
  case ALU::SUBN: {
    uint8_t flag = (registers_[x] > registers_[y]) ? 0 : 1;
    registers_[x] = registers_[y] - registers_[x];
    status_reg() = flag;
    break;
  }
  case ALU::SHR: {
    uint8_t flag = extract_bits<0, 1>(registers_[x]);
    registers_[x] >>= 0x1;
    status_reg() = flag;
    break;
  }
  case ALU::SHL: {
    uint8_t flag = extract_bits<7, 1>(registers_[x]);
    registers_[x] <<= 0x1;
    status_reg() = flag;
    break;
  }
  default:
    break;
  }
}

void CPU::execute_sne_r2r() {
  uint8_t x = instruction_.get_x();
  uint8_t y = instruction_.get_y();
  if (registers_[x] != registers_[y]) {
    program_counter_ += 2;
  }
}

void CPU::execute_ld_i() {
  uint16_t nnn = instruction_.get_nnn();
  index_register_ = nnn;
}

void CPU::execute_jp_v0() {
  uint16_t nnn = instruction_.get_nnn();
  program_counter_ = nnn + registers_[0];
}

void CPU::execute_rnd() {
  uint8_t nn = instruction_.get_nn();
  uint8_t x = instruction_.get_x();
  uint8_t random_byte = static_cast<uint8_t>(dist_(rng_));
  registers_[x] = random_byte & nn;
}

void CPU::execute_drw() {
  uint8_t x = instruction_.get_x();
  uint8_t y = instruction_.get_y();
  uint8_t n = instruction_.get_n();
  uint8_t start_col = registers_[x] % DISPLAY_COLS;
  uint8_t start_row = registers_[y] % DISPLAY_ROWS;
  status_reg() = 0x0;

  for (uint16_t row = 0; row < n; row++) { // bytes
    if (start_row + row >= DISPLAY_ROWS) {
      break;
    }
    uint8_t sprite = memory_[index_register_ + row];
    for (uint16_t col = 0; col < 8; col++) { // bits
      if (start_col + col >= DISPLAY_COLS) {
        break;
      }
      if (extract_bits(sprite, 7 - col, 0x1)) {
        uint16_t disp_addr =
            (start_row + row) * DISPLAY_COLS + (start_col + col);
        uint8_t current_bit = display_[disp_addr];
        uint8_t next_bit = current_bit ^ 0x1;
        display_[disp_addr] = next_bit;
        if (current_bit) {
          status_reg() = 0x1;
        }
      }
    }
  }
}

void CPU::execute_misc() {
  uint8_t x = instruction_.get_x();
  uint16_t nn = instruction_.get_nn();
  switch (nn) {
  case 0x07: {
    registers_[x] = delay_timer_;
    break;
  }
  case 0x15: {
    delay_timer_ = registers_[x];
    break;
  }
  case 0x18: {
    sound_timer_ = registers_[x];
    break;
  }
  case 0x1E: {
    index_register_ += registers_[x];
    break;
  }
  case 0x55: {
    for (uint8_t i = 0; i <= x; i++) {
      memory_[index_register_ + i] = registers_[i];
    }
    break;
  }
  case 0x65: {
    for (uint8_t i = 0; i <= x; i++) {
      registers_[i] = memory_[index_register_ + i];
    }
    break;
  }
  }
}