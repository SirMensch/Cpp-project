#include "visualizer.hpp"

namespace visualization {

void drawCar(const std::string &mesh_name, const simulation::Car &car) {
  // 1. Get current physical transformations from the vehicle instance
  Eigen::Vector3d pos = car.getPosition();
  auto collision_obj = car.getCollisionObject();

  // Default fallback dimensions in case casting fails
  double half_l = 1;
  double half_w = 1;
  double height = 5;

  // TODO get this everytime is a waste
  auto box_geom = collision_obj->collisionGeometry();
  if (collision_obj && box_geom) {
    auto casted_box_geom = std::dynamic_pointer_cast<const fcl::Box<double>>(
        collision_obj->collisionGeometry());
    if (box_geom) {
      // box_geom->side holds [X_length, Y_width, Z_height]
      half_l = casted_box_geom->side[0] / 2.0;
      half_w = casted_box_geom->side[1] / 2.0;
      height = casted_box_geom->side[2];
    }
  }

  fcl::Vector3d translation = collision_obj->getTranslation();
  fcl::Matrix3d rotation = collision_obj->getRotation();

  // 3. Define the 6 rectangular faces of the box mesh using index tracking
  std::vector<std::vector<size_t>> faces = {
      {0, 1, 2, 3}, // Bottom face
      {4, 5, 6, 7}, // Top face
      {0, 1, 5, 4}, // Left face
      {1, 2, 6, 5}, // Front face
      {2, 3, 7, 6}, // Right face
      {3, 0, 4, 7}  // Back face
  };

  double yaw = std::atan2(rotation(1, 0), rotation(0, 0));
  double cos_y = std::cos(yaw);
  double sin_y = std::sin(yaw);
  auto get_world_point = [&](double local_x, double local_y,
                             double local_z) -> std::vector<double> {
    return {translation.x() + (local_x * cos_y - local_y * sin_y),
            translation.y() + (local_x * sin_y + local_y * cos_y), local_z};
  };

  std::vector<std::vector<double>> vertices = {
      get_world_point(-half_l, -half_w, 0.0),
      get_world_point(half_l, -half_w, 0.0),
      get_world_point(half_l, half_w, 0.0),
      get_world_point(-half_l, half_w, 0.0),
      get_world_point(-half_l, -half_w, height),
      get_world_point(half_l, -half_w, height),
      get_world_point(half_l, half_w, height),
      get_world_point(-half_l, half_w, height)};

  // 4. Update Polyscope Mesh
  auto *ps_mesh = polyscope::registerSurfaceMesh(mesh_name, vertices, faces);

  // Add directional vector
  cos_y = std::cos(pos(2));
  sin_y = std::sin(pos(2));
  std::vector<std::vector<double>> vector_origins = {
      {pos(0), pos(1),
       height / 2.0}}; // Start the arrow at the center of the car's top face};
  std::vector<std::vector<double>> vector_directions = {
      {cos_y * 1.5, sin_y * 1.5, 0}};

  // 2. Register a lightweight point cloud for the arrow's starting position
  auto *ps_heading_node =
      polyscope::registerPointCloud(mesh_name + "_Heading", vector_origins);

  // 3. Attach the vector to this point node (PointCloud natively allows
  // arbitrary origins!)
  auto *heading_arrow = ps_heading_node->addVectorQuantity(
      "Direction", vector_directions, polyscope::VectorType::AMBIENT);
  heading_arrow->setEnabled(true);
  heading_arrow->setVectorColor({0.0, 1.0, 0.5}); // Neon green arrow

  // Optional: Hide the raw coordinate point itself so only the clean arrow is
  // visible
  ps_heading_node->setPointRadius(0.0);
}

void drawAbsoluteCoordinateSystem() {
  // Origin location (0, 0, 0)
  std::vector<std::vector<double>> origin = {{0.0, 0.0, 0.0}};

  // Define standard unit vectors for X, Y, and Z axes (1.0 meter long)
  std::vector<std::vector<double>> x_dir = {{1.0, 0.0, 0.0}};
  std::vector<std::vector<double>> y_dir = {{0.0, 1.0, 0.0}};
  std::vector<std::vector<double>> z_dir = {{0.0, 0.0, 1.0}};

  // Register the origin point node
  auto *world_node = polyscope::registerPointCloud("World_Origin", origin);
  world_node->setPointRadius(0.0); // Hide the center vertex point

  // Add X-Axis (Red)
  auto *x_axis = world_node->addVectorQuantity("X-Axis (Forward)", x_dir,
                                               polyscope::VectorType::AMBIENT);
  x_axis->setEnabled(true);
  x_axis->setVectorColor({1.0, 0.0, 0.0});

  // Add Y-Axis (Green)
  auto *y_axis = world_node->addVectorQuantity("Y-Axis (Left)", y_dir,
                                               polyscope::VectorType::AMBIENT);
  y_axis->setEnabled(true);
  y_axis->setVectorColor({0.0, 1.0, 0.0});

  // Add Z-Axis (Blue)
  auto *z_axis = world_node->addVectorQuantity("Z-Axis (Up)", z_dir,
                                               polyscope::VectorType::AMBIENT);
  z_axis->setEnabled(true);
  z_axis->setVectorColor({0.0, 0.0, 1.0});
}

void drawEnvironment(const simulation::Environment &env) {
  for (const auto &obs : env.getObstacles()) {
    double half_l = obs.length / 2.0;
    double half_w = obs.width / 2.0;
    double h = obs.height;

    double cos_y = std::cos(obs.yaw);
    double sin_y = std::sin(obs.yaw);

    // Helper to transform local box corners to world coordinates
    auto get_world_point = [&](double lx, double ly,
                               double lz) -> std::vector<double> {
      return {obs.x + (lx * cos_y - ly * sin_y),
              obs.y + (lx * sin_y + ly * cos_y), lz};
    };

    // Define 8 corners of the 3D box obstacle
    std::vector<std::vector<double>> vertices = {
        get_world_point(-half_l, -half_w, 0.0), // 0
        get_world_point(half_l, -half_w, 0.0),  // 1
        get_world_point(half_l, half_w, 0.0),   // 2
        get_world_point(-half_l, half_w, 0.0),  // 3
        get_world_point(-half_l, -half_w, h),   // 4
        get_world_point(half_l, -half_w, h),    // 5
        get_world_point(half_l, half_w, h),     // 6
        get_world_point(-half_l, half_w, h)     // 7
    };

    // 6 quadrilaterals for the box faces
    std::vector<std::vector<size_t>> faces = {
        {0, 1, 2, 3}, // Bottom
        {4, 5, 6, 7}, // Top
        {0, 1, 5, 4}, // Side 1
        {1, 2, 6, 5}, // Side 2
        {2, 3, 7, 6}, // Side 3
        {3, 0, 4, 7}  // Side 4
    };

    // Register mesh to Polyscope
    auto *ps_mesh =
        polyscope::registerSurfaceMesh("env_" + obs.name, vertices, faces);

    // Give obstacles a distinct color (e.g., dark gray/slate red)
    ps_mesh->setSurfaceColor({0.4, 0.4, 0.45});
  }
}

} // namespace visualization
