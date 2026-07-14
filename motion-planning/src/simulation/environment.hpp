// include/simulation/environment.hpp
#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fcl/geometry/shape/box.h>
#include <fcl/narrowphase/collision_object.h>

namespace simulation {

struct Obstacle {
    std::string name;
    double x, y, yaw;
    double length, width, height;
    std::shared_ptr<fcl::CollisionObject<double>> collision_object;
};

class Environment {
public:
    Environment() = default;

    // Adds a static box obstacle to the world
    void addBoxObstacle(const std::string& name, double x, double y, double yaw, 
                        double length, double width, double height);

    const std::vector<Obstacle>& getObstacles() const { return obstacles_; }

private:
    std::vector<Obstacle> obstacles_;
};

} // namespace simulation