//
// Created by larsl on 2/9/2024.
//

#ifndef INVERSEPENDLE_HEADERS_SLIDINGMODE_H_
#define INVERSEPENDLE_HEADERS_SLIDINGMODE_H_

#include "Controller.h"

class SlidingMode : public Controller {
 public:
  SlidingMode(float mass_platform, float mass_stick, float length_stick);
  float feedbackControl(Differentials diff_x, Differentials diff_theta) override;
 private:
};

#endif //INVERSEPENDLE_HEADERS_SLIDINGMODE_H_
