#include "polyscope/polyscope.h"
#include "polyscope/types.h"
#include "simulation/car.hpp"
#include "simulation/environment.hpp"
#include "visualization/visualizer.hpp"

void polyscope_setup() {
  polyscope::init();
  polyscope::view::upDir = polyscope::view::UpDir::ZUp;
  polyscope::options::groundPlaneEnabled = true;
  polyscope::options::groundPlaneMode = polyscope::GroundPlaneMode::Tile;
  polyscope::options::groundPlaneHeightFactor = 0.0;
}

simulation::Environment createEnvironment() {
  simulation::Environment env;
  env.addBoxObstacle("wall_front", 10.0, 0.f, 0.0, 0.5, 20, 0.5);
  env.addBoxObstacle("wall_right", 0.f, -10.0, 0.0, 20.0, 0.5, 0.5);
  env.addBoxObstacle("wall_left", 0.f, 10.0, 0.0, 20.0, 0.5, 0.5);
  return env;
}

int main() {
  static bool is_paused = true;

  polyscope_setup();

  simulation::Environment env = createEnvironment();
  simulation::Car ego_car(0.0, 0.0, 0.0, 2.0, 1.0);

  visualization::drawAbsoluteCoordinateSystem();

  polyscope::state::userCallback = [&]() {
    // 2. Create a clean Control Panel overlay panel using ImGui
    ImGui::Begin("Simulation Controls");

    if (is_paused) {
      if (ImGui::Button("▶ Play", ImVec2(100, 0))) {
        is_paused = false;
      }
    } else {
      if (ImGui::Button("⏸ Pause", ImVec2(100, 0))) {
        is_paused = true;
      }
    }

    double d_phi = 0.2;
    double dt = 0.0166667; // 1/60 seconds

    ImGui::SameLine();
    if (ImGui::Button("Step Single Frame")) {
      ego_car.step(d_phi, dt);
    }

    ImGui::End();

    if (!is_paused) {
      ego_car.step(d_phi, dt);
    }

    visualization::drawCar("EgoVehicle", ego_car);
    visualization::drawEnvironment(env);
  };

  polyscope::show();
  return 0;
  return 0;
}