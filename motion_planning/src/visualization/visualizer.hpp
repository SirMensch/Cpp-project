
#include "simulation/car.hpp"
#include "simulation/environment.hpp"
#include <Eigen/Core>
#include <string>

namespace visualization {

void drawCar(const std::string &mesh_name, const simulation::Car &car);

void drawEnvironment(const simulation::Environment &env);

void drawAbsoluteCoordinateSystem();

void drawPlannedPath(const std::string &name,
                     const std::vector<Eigen::Vector3d> &path);

} // namespace visualization