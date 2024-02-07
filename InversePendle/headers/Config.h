#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// Function to read and parse the configuration file
std::unordered_map<std::string, std::string> readConfig(const std::string& filename) {
  std::unordered_map<std::string, std::string> config;
  std::ifstream configFile(filename);

  if (configFile.is_open()) {
    std::string line;
    while (std::getline(configFile, line)) {
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos) {
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        config[key] = value;
      }
    }

    configFile.close();
  } else {
    std::cerr << "Error: Unable to open config file." << std::endl;
  }

  return config;
}


