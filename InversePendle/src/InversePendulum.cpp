//
// Created by larsl on 2/4/2024.
//
#include "InversePendulum.h"

InversePendulum::InversePendulum(float platform_width, float platform_height, float stick_width, float stick_height) {
  //set up stick and platform
  platform_orientation_ = *new Orientation(4.f - platform_width / 2.f, 4.f, 0);
  platform_ = std::make_shared<Platform>(platform_width, platform_height, platform_orientation_);
  stick_orientation_ = *new Orientation(4.f, 4.f, 182);
  stick_ = std::make_shared<Stick>(stick_width, stick_height, stick_orientation_);

  // set up the diff
  diff_x_ = {0, 0, platform_orientation_.x};
  diff_theta_ = {0, 0, float((stick_orientation_.angle - 180.f) / 180.f * M_PI)};

#if C_SLIDING_MODE
  controller_ = std::make_shared<SlidingMode>(platform_->getWeight(), stick_->getWeight(), stick_->getHeight());
#elif C_PID
  controller_ = std::make_shared<PID>(40, 1, 1);
#elif C_LQR
  controller_;
#else
  controller_ = nullptr;
#endif
}

std::list<std::shared_ptr<Object>> InversePendulum::update(float delta_time, float external_force, int sim_steps) {
  float controller_force = 0;
#if C_SLIDING_MODE or C_PID
  controller_force = controller_->feedbackControl(diff_x_, diff_theta_, delta_time);
  std::cout << "Controller Force: " << controller_force << "\n";
#endif
  // calculate new values
  for (int i = 0; i < sim_steps; ++i) {
    float theta_ddot = (G * std::sin(diff_theta_.pos) - diff_x_.acc * std::cos(diff_theta_.pos)) / 2.f;
    theta_ddot -= MU_ROT * G / stick_->getHeight() * diff_theta_.vel;
    theta_ddot *= 3.f / stick_->getHeight();

    float x_ddot = std::pow(diff_theta_.vel, 2.f) * std::sin(diff_theta_.pos);
    x_ddot -= diff_theta_.acc * std::cos(diff_theta_.pos);
    x_ddot *= 1 / 2.f * stick_->getWeight() * stick_->getHeight();
    x_ddot -= MU_TRANS * G * platform_->getWeight() * diff_x_.vel;
    x_ddot += external_force + controller_force;
    x_ddot /= (platform_->getWeight() + stick_->getWeight());

    // update new values
    diff_x_ = {x_ddot,
               diff_x_.vel + diff_x_.acc * delta_time / float(sim_steps),
               diff_x_.pos + diff_x_.vel * delta_time / float(sim_steps)};
    diff_theta_ =
        {theta_ddot,
         diff_theta_.vel + diff_theta_.acc * delta_time / float(sim_steps),
         diff_theta_.pos + diff_theta_.vel * delta_time / float(sim_steps)};

#if DEBUG
    // print x and theta and the derivations
    //std::cout << "x: " << diff_x_ << "\n";
    //std::cout << "theta:  " << diff_theta_ << "\n";
    // TODO calculate energy inside the system
#endif

  }

  //update objects
  platform_orientation_.x += diff_x_.vel * delta_time;
  stick_orientation_.x += diff_x_.vel * delta_time;
  stick_orientation_.angle = 180.f * diff_theta_.pos / float(M_PI) + 180.f;

  bool success = stick_->updatePosition(stick_orientation_);
  success &= platform_->updatePosition(platform_orientation_);
  if (!success) {
    throw std::runtime_error("Update of Stick or Platform failed!");
  }
  // give objects to simulator
  std::list<std::shared_ptr<Object>> object_list;
  object_list.push_back(stick_);
  object_list.push_back(platform_);
  return object_list;
}
