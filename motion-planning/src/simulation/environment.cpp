#include "simulation/environment.hpp"

namespace simulation {

void Environment::addBoxObstacle(const std::string &name, double x, double y,
                                 double yaw, double length, double width,
                                 double height) {

  auto box_shape = std::make_shared<fcl::Box<double>>(length, width, height);

  fcl::Vector3d translation(x, y, height / 2.0); // Center on Z axis
  fcl::Matrix3d rotation =
      Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();

  auto collision_obj = std::make_shared<fcl::CollisionObject<double>>(
      box_shape, rotation, translation);

  obstacles_.push_back({name, x, y, yaw, length, width, height, collision_obj});
}

} // namespace simulation