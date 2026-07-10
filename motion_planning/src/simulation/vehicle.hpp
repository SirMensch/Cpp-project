#pragma once
#include <Eigen/Dense>
#include <fcl/narrowphase/collision_object.h>

namespace simulation {
class Vehicle {
public:
  virtual ~Vehicle() = default;

  virtual void step(double d_phi, double dt) = 0;

  virtual Eigen::Vector3d getPosition() const = 0;

  virtual double getSteeringAngle() const = 0;

  virtual double getX() const = 0;

  virtual double getY() const = 0;

  virtual std::string getType() const = 0;

  virtual std::shared_ptr<fcl::CollisionObjectd> getCollisionObject() const = 0;
};
} // namespace simulation