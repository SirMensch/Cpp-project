//
// Created by larsl on 2/9/2024.
//

#include "SlidingMode.h"

float SlidingMode::feedbackControl(Differentials diff_x, Differentials diff_theta) {
  //TODO add noise to the sensor signals

  // implement Sliding Mode

  float f_m = mass_stick_ * length_stick_ / (3.f * ( mass_platform_ + mass_stick_ / 3.f ) ) *
      ( diff_theta.acc * std::cos(diff_theta.pos) +
      std::pow(diff_theta.vel,2.f) * std::sin(diff_theta.pos) );
  f_m += - MU_TRANS * mass_platform_ * G * diff_theta.vel;
  return 0;
}
SlidingMode::SlidingMode(float mass_platform, float mass_stick, float length_stick) : Controller(mass_platform,
                                                                                                 mass_stick,
                                                                                                 length_stick) {}
