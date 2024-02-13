//
// Created by larsl on 2/9/2024.
//

#include "SlidingMode.h"

float SlidingMode::feedbackControl(Differentials diff_x, Differentials diff_theta) {

  //diff_theta = diff_theta + Differentials{getRandomNumber(0.01), getRandomNumber(0.01), getRandomNumber(0.01)};
  //diff_x = diff_x + Differentials{getRandomNumber(), getRandomNumber(), getRandomNumber()};

  // implement Sliding Mode

  float f_t = mass_stick_ * length_stick_ / (3.f * ( mass_platform_ + mass_stick_ / 3.f ) ) *
      ( diff_theta.acc * std::cos(diff_theta.pos) -
      std::pow(diff_theta.vel,2.f) * std::sin(diff_theta.pos) );
  f_t += MU_TRANS * mass_platform_ * G * diff_x.vel + MU_ROT * mass_stick_ * G * diff_theta.vel;
  f_t += 1 / length_stick_ * (- 3.f * G * std::sin(diff_theta.pos) + diff_x.vel * std::cos(diff_theta.pos));
  f_t -= LAMBDA * (diff_theta.vel + diff_x.vel);
  // f_t += uncertainties * ETA
  return f_t;
}
SlidingMode::SlidingMode(float mass_platform, float mass_stick, float length_stick) : Controller(mass_platform,
                                                                                                 mass_stick,
                                                                                                 length_stick) {}
