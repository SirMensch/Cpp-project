#include "simulation/car.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <sstream> // For clean string formatting

TEST_CASE("Car kinematics state updates correctly", "[vehicle][kinematics]") {
  // Setup initial state
  double x = 4.5;
  double y = 1.8;
  double phi = 2.7; // radians
  simulation::Car test_car(x, y, phi, 2.f, 1.f);

  SECTION("Initial coordinates start at defined position") {
    REQUIRE(test_car.getX() == x);
    REQUIRE(test_car.getY() == y);
  }

  SECTION("Straight line step updates X coordinate only") {
    double velocity = 2.0;       // 2 m/s
    double steering_angle = 0.0; // straight ahead
    double dt = 0.5;             // half a second

    // 1. Log position BEFORE the step
    UNSCOPED_INFO("BEFORE STEP -> Pos: (" << test_car.getX() << ", "
                                          << test_car.getY() << ")");

    test_car.step(steering_angle, dt);

    // 2. Log position AFTER the step
    UNSCOPED_INFO("AFTER STEP  -> Pos: (" << test_car.getX() << ", "
                                          << test_car.getY() << ")");

    // Expect to move forward 1.0 meter (2.0 * 0.5)
    REQUIRE_THAT(test_car.getX() - x, Catch::Matchers::WithinAbs(0, 0.5));
    REQUIRE_THAT(test_car.getY() - y, Catch::Matchers::WithinAbs(0, 0.5));
    REQUIRE_THAT(test_car.getSteeringAngle(),
                 Catch::Matchers::WithinAbs(0.0, 0.001));
  }
}