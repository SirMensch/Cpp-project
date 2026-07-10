#include "polyscope/point_cloud.h"
#include "polyscope/surface_mesh.h"
#include "simulation/car.hpp"
#include "simulation/environment.hpp"
#include <Eigen/Core>
#include <string>
#include <vector>

namespace visualization {

void drawCar(const std::string &mesh_name, const simulation::Car &car);

void drawEnvironment(const simulation::Environment &env);

void drawAbsoluteCoordinateSystem();

} // namespace visualization