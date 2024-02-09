//
// Created by larsl on 2/9/2024.
//

#ifndef INVERSEPENDLE_HEADERS_CONTROLLER_H_
#define INVERSEPENDLE_HEADERS_CONTROLLER_H_

class Controller {
  Controller(float mass_platform, float mass_stick, float length_stick);
  /**
   *
   * @param x variable of the platform in x direction
   * @param theta angle of the stick
   * @return acceleration in x for the motor of the platform
   */
  virtual float feedbackControl(float x, float theta) = 0;
};

#endif //INVERSEPENDLE_HEADERS_CONTROLLER_H_
