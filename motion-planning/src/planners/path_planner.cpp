#include "path_planner.hpp"
#include <Eigen/Core>
#include <algorithm>
#include <map>
#include <queue>

namespace simulation {

PathPlanner::PathPlanner(double width, double height, double resolution)
    : res_(resolution), w_cells_(static_cast<int>(width / resolution)),
      h_cells_(static_cast<int>(height / resolution)) {
  grid_.resize(w_cells_, std::vector<int>(h_cells_, 0)); // 0 = free space
}

void PathPlanner::setObstacles(simulation::Environment &env) {
  for (const auto &obstacle : env.getObstacles()) {
    for (double x = obstacle.x - obstacle.length / 2.0;
         x <= obstacle.x + obstacle.length / 2.0; x += res_) {
      for (double y = obstacle.y - obstacle.width / 2.0;
           y <= obstacle.y + obstacle.width / 2.0; y += res_) {
        GridPos g = worldToGrid(x, y);
        if (g.x >= 0 && g.x < w_cells_ && g.y >= 0 && g.y < h_cells_) {
          grid_[g.x][g.y] = 1;
        }
      }
    }
  }
}

GridPos PathPlanner::worldToGrid(double wx, double wy) const {
  return {static_cast<int>((wx + (w_cells_ * res_) / 2.0) / res_),
          static_cast<int>((wy + (h_cells_ * res_) / 2.0) / res_)};
}

Eigen::Vector3d PathPlanner::gridToWorld(const GridPos &g) const {
  return Eigen::Vector3d{(g.x * res_) - (w_cells_ * res_) / 2.0 + res_ / 2.0,
                         (g.y * res_) - (h_cells_ * res_) / 2.0 + res_ / 2.0,
                         0};
}

Path PathPlanner::planPath(double start_x, double start_y, double goal_x,
                           double goal_y) {
  GridPos start = worldToGrid(start_x, start_y);
  GridPos goal = worldToGrid(goal_x, goal_y);

  // Standard BFS structures
  std::queue<GridPos> frontier;
  std::map<GridPos, GridPos> came_from;
  std::map<GridPos, bool> visited;

  frontier.push(start);
  visited[start] = true;
  came_from[start] = start;

  // 4-connected movement rules (Up, Down, Left, Right)
  const std::vector<GridPos> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  bool found = false;

  while (!frontier.empty()) {
    GridPos current = frontier.front();
    frontier.pop();

    if (current == goal) {
      found = true;
      break;
    }

    for (const auto &dir : directions) {
      GridPos next = {current.x + dir.x, current.y + dir.y};

      // Check array boundaries
      if (next.x >= 0 && next.x < w_cells_ && next.y >= 0 &&
          next.y < h_cells_) {
        // Check if it's free space and not visited yet
        if (grid_[next.x][next.y] == 0 && !visited[next]) {
          frontier.push(next);
          visited[next] = true;
          came_from[next] = current;
        }
      }
    }
  }

  // Reconstruct the path waypoints list from Back to Front
  Path path;
  if (!found)
    return path; // Return empty vector if path is completely blocked

  GridPos curr = goal;
  while (!(curr == start)) {
    path.push_back(gridToWorld(curr));
    curr = came_from[curr];
  }
  path.push_back(gridToWorld(start));
  std::reverse(path.begin(), path.end());

  return path;
}

} // namespace simulation