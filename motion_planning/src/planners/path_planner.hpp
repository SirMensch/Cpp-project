// include/simulation/path_planner.hpp
#pragma once
#include "simulation/environment.hpp"
#include <vector>

namespace simulation {

using Path = std::vector<Eigen::Vector3d>;

struct GridPos {
  int x, y;
  bool operator==(const GridPos &o) const { return x == o.x && y == o.y; }
  // TODO why do we need this operator?
  bool operator<(const GridPos &o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
};

class PathPlanner {
public:
  PathPlanner(double width, double height, double resolution);

  void setObstacles(simulation::Environment &env);

  Path planPath(double start_x, double start_y,
                                        double goal_x, double goal_y);

private:
  double res_;
  int w_cells_, h_cells_;
  std::vector<std::vector<int>> grid_;

  GridPos worldToGrid(double wx, double wy) const;

  Eigen::Vector3d gridToWorld(const GridPos &g) const;
};

} // namespace simulation