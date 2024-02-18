//
// Created by larsl on 2/9/2024.
//

#include "SlidingMode.h"

float SlidingMode::feedbackControl(Differentials diff_x, Differentials diff_theta, float delta_time) {

  diff_theta = diff_theta + Differentials{getRandomNumber(0.01), getRandomNumber(0.01), getRandomNumber(0.01)};
  diff_x = diff_x + Differentials{getRandomNumber(), getRandomNumber(), getRandomNumber()};

  // S = eps_dot + LAMBDA * eps || eps = diff_x.pos - THETA_X_FACTOR * diff_theta.pos
  float f_t_x = mass_stick_ * length_stick_ / 3.f *
      (diff_theta.acc * std::cos(diff_theta.pos)
      - std::pow(diff_theta.vel, 2.f) * std::sin(diff_theta.pos));
  f_t_x += MU_TRANS * mass_platform_ * G * diff_x.vel;
  float f_t_theta = THETA_X_FACTOR / length_stick_ *
      (3.f * G * std::sin(diff_theta.pos)
      - diff_x.acc * std::cos(diff_theta.pos)
      - MU_ROT * G * diff_theta.vel / 6.f);
  f_t_theta += LAMBDA * (diff_theta.vel * THETA_X_FACTOR - diff_x.vel / THETA_X_FACTOR);
  f_t_theta *= (mass_platform_ + mass_stick_ / 3.f);
  f_t_x += ETA * std::sin(diff_theta.pos) * mass_platform_ * std::pow(length_stick_,2.f);
  return f_t_x + f_t_theta;
}
SlidingMode::SlidingMode(float mass_platform, float mass_stick, float length_stick) : Controller(mass_platform,
                                                                                                 mass_stick,
                                                                                                 length_stick) {}
