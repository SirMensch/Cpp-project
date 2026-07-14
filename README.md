# Cpp-projects

## motion-planning

A high-performance C++ motion planning and trajectory optimization sandbox built on Fedora Linux using CMake, Ninja, and vcpkg. This framework leverages advanced geometric processing libraries to implement, test, and interactively visualize robotic pathfinding.

### Current Progress & Features

*   **3D Geometric Visualization:** Integrated **Polyscope** for lightweight, real-time 3D visualization of planning scenes, point clouds, grids, and calculated trajectories directly from Eigen structures.
*   **Algorithmic Foundations:** Implemented a robust Breadth-First Search (BFS) algorithm to verify baseline grid-based shortest paths.

### Tech Stack & Tooling

*   **Operating System:** Fedora Linux
*   **Build System:** CMake + Ninja
*   **Package Manager:** `vcpkg` (Manifest Mode activated)
*   **Language Server:** Clangd (Optimized local AST parsing via `.clangd`)

### Dependency Matrix (`vcpkg.json`)

The project utilizes `vcpkg` in manifest mode to manage its core modern C++ library stack automatedly:
*   `polyscope` — 3D desktop visualization GUI for geometric computing.
*   `eigen3` — Linear algebra, matrix operations, and coordinate transforms.
*   `fcl` — Proximity queries, continuous collision detection, and distance calculations.
*   `catch2` — Modern, type-safe unit testing framework.

### Quick Start

#### 1. Prerequisites (Fedora)

TBD

## inverse-pendle

A high-performance C++ physical simulation and control systems playground modeling an inverted pendulum. This project pairs a custom-engineered 2D state-space physics engine with real-time hardware-accelerated visualization via the modern **SFML 3** framework.

### Project Core

The primary goal of **inverse-pendle** is the active stabilization of a highly non-linear, underactuated mechanical system (the classical inverted pendulum on a cart). The repository serves as an active benchmarking platform for comparing classical linear feedback loops against robust non-linear tracking strategies under parametric uncertainties and external disturbances.

### Implemented Control Strategies

*   **Proportional-Integral-Derivative (PID) Control:** A finely-tuned traditional feedback mechanism managing error correction. It calculates localized corrective adjustments based on proportional, integral, and derivative terms to achieve balancing stability around the vertical upright equilibrium point.
*   **Sliding Mode Control (SMC):** A robust non-linear control strategy designed to handle modeling inaccuracies and external torque variations. By utilizing a high-speed switching control law, it forces the system's state trajectories onto a custom-defined sliding surface, guaranteeing asymptotic stability and excellent disturbance rejection.

### Technical Architecture & Design Patterns

*   **Simulation & Rendering Engine:** Built on top of **SFML 3**, utilizing strict type-safe event loops, unit-aware transformations (`sf::degrees` / `sf::radians`), and vectorized layout metrics (`sf::Vector2u`).
*   **Modern C++ Practices:** Employs explicit object life-cycle management (`std::shared_ptr`, member initializer lists) to ensure deterministic memory safety without the overhead of heavy garbage collection.
*   **Linux Tooling Ecosystem:** Formatted and optimized specifically for a **Fedora Linux** environment using a decoupled `CMake` + `Ninja` fallback setup that isolates code logic from boilerplate IDE configurations.

### Compilation & System Setup

#### 1. Install Fedora System Dependencies
```bash
sudo dnf install systemd-devel libX11-devel libXi-devel libXrandr-devel libXcursor-devel mesa-libGL-devel mesa-libGLU-devel