//
// Created by larsl on 2/9/2024.
//

#ifndef INVERSEPENDLE_HEADERS_CONTROLLER_H_
#define INVERSEPENDLE_HEADERS_CONTROLLER_H_

#include <random>
#include <cmath>
#include "structs.h"

class Controller {
 public:
  Controller(float mass_platform, float mass_stick, float length_stick);
  /**
 *
 * @param x variable of the platform in x direction
 * @param theta angle of the stick
 * @return acceleration in x for the motor of the platform
 */
  virtual float feedbackControl(Differentials diff_x, Differentials diff_theta, float delta_time) = 0;
  float getRandomNumber(float std_dev = 1.f);
 private:
  std::normal_distribution<float> gaussian_;
  std::mt19937 generator_;
 protected:
  float mass_platform_;
  float mass_stick_;
  float length_stick_;
};

#endif //INVERSEPENDLE_HEADERS_CONTROLLER_H_
