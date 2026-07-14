//
// Created by larsl on 2/17/2024.
//

#include "PID.h"
PID::PID(float k_proportional, float k_integral, float k_differential) : Controller(0, 0, 0),
                                                                         p_(k_proportional),
                                                                         i_(k_integral),
                                                                         d_(k_differential) {}

float PID::feedbackControl(Differentials diff_x, Differentials diff_theta, float delta_time) {
  static float integrative_part = 0;
  static float last_theta = 0;

  // measurements are noisy
  diff_theta = diff_theta + Differentials{getRandomNumber(0.01), getRandomNumber(0.01), getRandomNumber(0.01)};
  //diff_x = diff_x + Differentials{getRandomNumber(), getRandomNumber(), getRandomNumber()};

  // calculate force
  float force = p_ * diff_theta.pos + d_ * (diff_theta.pos - last_theta) + i_ * integrative_part;

  // d and i for next iteration
  integrative_part += delta_time * diff_theta.pos;
  last_theta = diff_theta.pos;
  return force;
}
