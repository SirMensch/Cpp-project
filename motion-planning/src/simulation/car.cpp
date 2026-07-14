#include "car.hpp"
#include "polyscope/polyscope.h" // For polyscope::getTerminal()
#include <iostream>              // For std::cout

namespace simulation {

Car::Car(double x, double y, double phi, double length, double width) {
  Eigen::Vector2d position_center = {x, y};
  position_front_ << x + cos(phi) * length / 2.0, y + sin(phi) * length / 2.0,
      phi;
  position_back_ << x - cos(phi) * length / 2.0, y - sin(phi) * length / 2.0,
      phi;
  size_ << length, width;

  auto car_shape = std::make_shared<fcl::Box<double>>(length, width, 1.0);

  Eigen::Vector3d translation = getCenterPosition();
  Eigen::Matrix3d rotation =
      Eigen::AngleAxisd(phi, Eigen::Vector3d::UnitZ()).toRotationMatrix();

  collision_object_ = std::make_shared<fcl::CollisionObject<double>>(
      car_shape, rotation, translation);

  // -------------------------------------------------------------------------
  // Debug Prints
  // -------------------------------------------------------------------------

  std::cout << "[DEBUG] Car Created Successfully\n"
            << "  -> Target Pos (x, y, phi): (" << x << ", " << y << ", " << phi
            << ")\n"
            << "  -> FCL Translation Vector: (" << translation.x() << ", "
            << translation.y() << ", " << translation.z() << ")\n"
            << "  -> Yaw Matrix Angle (deg): " << (phi * 180.0 / M_PI) << "°\n"
            << std::endl;

  if (polyscope::state::initialized) {
    polyscope::info("Car constructed at (" + std::to_string(x) + ", " +
                    std::to_string(y) + ")");
  }
}

void Car::step(double d_phi, double dt) {
  static int debug_frame_counter = 0;
  debug_frame_counter++;

  double phi = position_back_(2) + d_phi;

  position_front_(0) = position_front_(0) + velocity(0) * dt * cos(phi);
  position_front_(1) = position_front_(1) + velocity(0) * dt * sin(phi);
  position_front_(2) = phi;

  // update back axis
  Eigen::Vector2d diff_back_to_front = this->getCarVector();
  auto step_pos_back = (diff_back_to_front.norm() - getLength()) *
                       diff_back_to_front.normalized();
  auto phi_back = atan2(step_pos_back(1), step_pos_back(0));
  position_back_ << position_back_(0) + step_pos_back(0),
      position_back_(1) + step_pos_back(1), phi_back;

  // update collision object
  Eigen::Vector3d translation = getCenterPosition();
  Eigen::Matrix3d rotation =
      Eigen::AngleAxisd(position_back_(2), Eigen::Vector3d::UnitZ())
          .toRotationMatrix();
  collision_object_->setTransform(rotation, translation);

  // -------------------------------------------------------------------------
  // Debug Outputs
  // -------------------------------------------------------------------------

  // 1. Throttled Console Print (Outputs roughly twice per second at 60 FPS)
  if (debug_frame_counter % 30 == 0) {
    std::cout << "[STEP DEBUG] Frame: " << debug_frame_counter << "\n"
              << "  -> Input d_phi: " << d_phi << " | dt: " << dt << "\n"
              << "  -> Front Axis Pos: (" << position_front_(0) << ", "
              << position_front_(1) << ")\n"
              << "  -> Back Axis Pos:  (" << position_back_(0) << ", "
              << position_back_(1) << ")\n"
              << "  -> Calculated Yaw: " << (phi_back * 180.0 / M_PI) << "°\n"
              << "  -> FCL Center:     (" << translation.x() << ", "
              << translation.y() << ")\n"
              << std::endl;
  }

  // 2. Real-time ImGui Custom Diagnostic Overlay
  // Add this inside your main userCallback loop alongside your other panel
  // windows!
  if (polyscope::state::initialized) {
    ImGui::Begin("Vehicle Kinematics State");
    ImGui::Text("Front Axis: (%.3f, %.3f, %.1f°)", position_front_(0),
                position_front_(1), position_front_(2) * 180.0 / M_PI);
    ImGui::Text("Back Axis:  (%.3f, %.3f, %.1f°)", position_back_(0),
                position_back_(1), phi_back * 180.0 / M_PI);
    ImGui::Text("FCL Translation: (%.3f, %.3f)", translation.x(),
                translation.y());
    ImGui::End();
  }
}

Eigen::Vector3d Car::getPosition() const {
  return position_front_; // Return the position of the front axis
}

Eigen::Vector2d Car::getCarVector() const {
  return position_front_.head<2>() - position_back_.head<2>();
}

Eigen::Vector3d Car::getCenterPosition() const {
  Eigen::Vector3d center;
  center << (position_front_.head<2>() + position_back_.head<2>()) / 2.0, 0;
  return center;
}

} // namespace simulation