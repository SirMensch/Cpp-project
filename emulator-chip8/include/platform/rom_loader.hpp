#ifndef __ROM_LOADER_H__
#define __ROM_LOADER_H__

#include <cstddef>
#include <ios>
#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

inline std::vector<uint8_t> read_rom_file(const std::string &filepath) {
  std::ifstream file(filepath, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "Failed to open ROM-file:" << filepath << "\n";
    return {};
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(static_cast<std::size_t>(size));

  if (!file.read(reinterpret_cast<char *>(buffer.data()), size)) {
    std::cerr << "Failed to read ROM file contents:" << filepath << "\n";
  }

  return buffer;
}

#endif // __ROM_LOADER_H__