#include "config.hpp"
#include "cpu/cpu.hpp"
#include "platform/rom_loader.hpp"
#include <cstdint>
#include <filesystem>
#include <gtest/gtest.h>
#include <numeric>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

class TimendusTestSuite : public ::testing::Test {
protected:
  CPU cpu;

  static void SetUpTestSuite() {
    spdlog::set_pattern("[%T.%e|%L] %v");
    spdlog::set_level(spdlog::level::info); // TOD think of how to manage this
    spdlog::level::level_enum current_lvl = spdlog::get_level();
    auto level_view = spdlog::level::to_string_view(current_lvl);
    spdlog::info("SPD log level is: {}", level_view);
  }

  void SetUp() override {} // TODO remove multiple lines

  void run_rom(const std::string &filename, int max_cycles = 200000) {
    std::string full_path = std::string(ROM_DIR) + "/" + filename;

    spdlog::info("Load rom from: {}", full_path);

    std::vector<uint8_t> rom = read_rom_file(full_path);

    cpu.load_program(rom, rom.size());

    for (int i = 0; i < max_cycles; ++i) {
      cpu.execute_instruction();
    }
  }

  const disp_array load_disp_solution(const std::string &filename) const {
    std::string rel_path =
        std::string(SOL_DIR) + "/" +
        std::filesystem::path(filename).filename().stem().string() + ".bin";

    spdlog::info("Load solution from: {}", rel_path);

    std::ifstream file(rel_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
      spdlog::error("Error: Failed to open file.");
      return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    disp_array buffer{};
    if (file.read(reinterpret_cast<char *>(buffer.data()), size)) {
      spdlog::debug("Sum of pixel: {}",
                    std::accumulate(buffer.begin(), buffer.end(), 0));
      return buffer;
    }

    spdlog::error("Error: Failed to load solution.");
    return {};
  }

  void ExpectFramebuffersEqual(const disp_array &actual,
                               const disp_array &expected) {
    for (size_t i = 0; i < actual.size(); ++i) {
      int x = i % 64;
      int y = i / 64;

      EXPECT_EQ(actual[i], expected[i])
          << "Pixel mismatch at coordinate (X: " << x << ", Y: " << y
          << ") [Index: " << i << "]";

      if (::testing::Test::HasFailure()) {
        break;
      }
    }
  }
};

TEST_F(TimendusTestSuite, Chip8LogoTest) {
  std::string filename = "1-chip8-logo.ch8";
  run_rom(filename, 50000);
  disp_array pixels = cpu.get_display();
  disp_array solution = load_disp_solution(filename);
  ExpectFramebuffersEqual(pixels, solution);
}

TEST_F(TimendusTestSuite, IBMLogoTest) {
  std::string filename = "2-ibm-logo.ch8";
  run_rom(filename, 50000);
  disp_array pixels = cpu.get_display();
  disp_array solution = load_disp_solution(filename);
  ExpectFramebuffersEqual(pixels, solution);
}

TEST_F(TimendusTestSuite, CoraxTest) {
  std::string filename = "3-corax+.ch8";
  run_rom(filename, 50000);
  disp_array pixels = cpu.get_display();
  disp_array solution = load_disp_solution(filename);
  ExpectFramebuffersEqual(pixels, solution);
}

// TODO