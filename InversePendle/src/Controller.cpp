//
// Created by larsl on 2/9/2024.
//

#include "Controller.h"


Controller::Controller(float mass_platform, float mass_stick, float length_stick) {
  std::random_device random_device;
  generator_.seed(random_device());

  gaussian_.param(std::normal_distribution<float>::param_type(0,1));

  mass_platform_ = mass_platform + getRandomNumber(); // stddev 1 kg
  mass_stick_ = mass_stick + getRandomNumber(); // stddev 1 kg
  length_stick_ = length_stick + getRandomNumber(); // std dev 1 cm
}
float Controller::getRandomNumber(float std_dev) {
  return gaussian_(generator_) * std_dev;
}
