//
// Created by larsl on 2/9/2024.
//

#ifndef INVERSEPENDLE_HEADERS_SLIDINGMODE_H_
#define INVERSEPENDLE_HEADERS_SLIDINGMODE_H_

#include "Controller.h"

class SlidingMode : public Controller {
  float feedbackControl(float x, float theta) override;
};

#endif //INVERSEPENDLE_HEADERS_SLIDINGMODE_H_
