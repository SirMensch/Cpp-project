//
// Created by larsl on 2/4/2024.
//
#include "InversePendulum.h"

InversePendulum::InversePendulum(float platform_width, float platform_height, float stick_width, float stick_height) {
  //set up stick and platform
  platform_orientation_ = *new Orientation(400.f - platform_width / 2.f, 400, 0);
  platform_ = std::make_shared<Platform>(platform_width, platform_height, platform_orientation_);
  stick_orientation_ = *new Orientation(400.f + stick_width / 2.f, 400, 182);
  stick_ = std::make_shared<Stick>(stick_width, stick_height, stick_orientation_);

  // set up the diff
  diff_x_ = {0, 0, platform_orientation_.x};
  diff_theta_ = {0, 0, float((stick_orientation_.angle - 180.f) / 180.f * M_PI)};
}
std::list<std::shared_ptr<Object>> InversePendulum::update(float delta_time) {
  // TODO check for physics, feels weird, fix speed
  // calculate new values
  float theta_ddot = (diff_x_.acc * std::cos(diff_theta_.pos) + G * std::sin(diff_theta_.pos));
  theta_ddot /= stick_->getHeight();

  float x_ddot = - diff_theta_.acc * std::cos(diff_theta_.pos);
  x_ddot += std::pow(diff_theta_.vel, 2.f) * std::sin(diff_theta_.pos);
  x_ddot *= stick_->getWeight() * stick_->getHeight() / (stick_->getWeight() + platform_->getWeight());

  // update new values
  diff_x_ = {x_ddot,
             diff_x_.vel + diff_x_.acc * delta_time,
             diff_x_.pos + diff_x_.vel * delta_time};
  diff_theta_ =
      {theta_ddot,
       diff_theta_.vel + diff_theta_.acc * delta_time,
       diff_theta_.pos + diff_theta_.vel * delta_time};

  platform_orientation_.x += diff_x_.vel * delta_time;
  stick_orientation_.x += diff_x_.vel * delta_time;
  stick_orientation_.angle = 180.f * diff_theta_.pos / float(M_PI) + 180.f;

  std::cout << "x: " << diff_x_ << std::endl;
  std::cout << "theta:  " << diff_theta_ << std::endl;
  //update objects
  stick_->updatePosition(stick_orientation_);
  platform_->updatePosition(platform_orientation_);
  // give objects to simulator
  std::list<std::shared_ptr<Object>> object_list;
  object_list.push_back(stick_);
  object_list.push_back(platform_);
  return object_list;
}
