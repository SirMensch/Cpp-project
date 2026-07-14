#pragma once
#include "vehicle.hpp"
#include <fcl/geometry/shape/box.h>

namespace simulation {

class Car : public Vehicle {

public:
  Car(double x, double y, double phi, double length, double width);
  ~Car() override = default;

  void step(double d_phi, double dt) override;

  Eigen::Vector3d getPosition() const override;

  double getSteeringAngle() const override {
    return position_front_(2) - position_back_(2);
  }

  double getX() const override { return position_front_(0); }

  double getY() const override { return position_front_(1); }

  std::string getType() const override { return "Car"; }

  std::shared_ptr<fcl::CollisionObjectd> getCollisionObject() const override {
    return collision_object_;
  }

  double getLength() const { return size_(0); }

  double getWidth() const { return size_(1); }

private:
  Eigen::Vector3d position_front_; // (x, y, phi)
  Eigen::Vector3d position_back_;  // (x, y, phi)
  // for now we only use position and const velocity forward
  Eigen::Vector3d velocity = {1, 0, 0}; // (vr, vphi, omega)
  // Eigen::Vector3d acceleration;

  Eigen::Vector2d size_; // (length, width)

  std::shared_ptr<fcl::CollisionObjectd> collision_object_;

  Eigen::Vector2d getCarVector() const;

  Eigen::Vector3d getCenterPosition() const;
};

} // namespace simulation