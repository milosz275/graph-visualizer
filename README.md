# Graph Visualizer

[![Make](https://github.com/milosz275/graph-visualizer/actions/workflows/makefile.yml/badge.svg)](https://github.com/milosz275/graph-visualizer/actions/workflows/makefile.yml)
[![CodeQL](https://github.com/milosz275/graph-visualizer/actions/workflows/codeql.yml/badge.svg)](https://github.com/milosz275/graph-visualizer/actions/workflows/codeql.yml)
[![Doxygen Pages](https://github.com/milosz275/graph-visualizer/actions/workflows/doxygen-pages.yml/badge.svg)](https://github.com/milosz275/graph-visualizer/actions/workflows/doxygen-pages.yml)
[![License](https://img.shields.io/github/license/milosz275/graph-visualizer)](/LICENSE)

![Logo](assets/logo.png)

[Graph Visualizer](https://github.com/milosz275/graph-visualizer) is a browser-based tool for visualizing directed and undirected graphs, featuring interactive traversal algorithms using WebGL and Emscripten. Try it out with the [demo](https://milosz275.github.io/graph-visualizer/demo) (note: might not scale well on mobile devices).

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Build](#build)
- [Graph Algorithms](#graph-algorithms)
- [Project Structure](#project-structure)
- [Design Patterns](#design-patterns)
- [Force-directed Graph Simulation](#force-directed-graph-simulation)
- [Acknowledgements](#acknowledgements)
- [License](#license)

## Features

- Create graphs in polygonal shapes or generate random graphs.
- Visualize graph traversal using BFS, DFS, and Dijkstra's algorithm.
- Step-by-step execution with one-second intervals.
- Interactive UI with WebGL rendering.

## Prerequisites

Graph Visualizer is compiled by emcc, available from [Emscripten](https://emscripten.org/). Build depends on `ccache`.

## Build

Run the following to setup to get a working copy of this project:

```bash
git clone --recurse-submodules -j$(nproc) https://github.com/milosz275/graph-visualizer
cd graph-visualizer
make -j$(nproc)
```

Setup local server to test the app:

```bash
cp src/index.html build
cp assets/favicon.ico build
cd build
python3 -m http.server
```

## Graph Algorithms

- [x] BFS - Traverses the graph using a queue, exploring all neighbors of a node before moving to the next level.
- [x] DFS - Traverses the graph using a stack, exploring as far as possible along each branch before backtracking.
- [x] Dijkstra - Finds the shortest path from a source node to all other nodes using a priority queue, ensuring the lowest-cost path is always processed first. Recovers the best path by backtracking from the target node to the source.
- [x] A* - An optimized shortest-path algorithm that combines Dijkstra’s approach with a heuristic function to estimate the remaining cost, guiding the search more efficiently toward the target.
- [x] Bellman-Ford - Computes the shortest paths from a source node to all other nodes, allowing for negative-weight edges. Iteratively relaxes edges, ensuring that no shorter path exists. Can detect negative-weight cycles.

## Project Structure

The project uses the [web-ui](https://github.com/milosz275/web-ui) frontend framework for rendering. It follows the Model-View-Controller (MVC) architecture to separate concerns effectively.

- Model - Abstract elements of the Graph Visualizer such as graph nodes, their physical properties along with graph algorithms, state of individual nodes and representation.
- View - Graphical aspect of both the program's state, UI and the graph itself.
- Controller - Interaction with the canvas with mouse and canvas translation to model component, and canvas resizing (no keyboard integration at this point).

## Design Patterns

Graph Visualizer is a highly abstracted project that leverages multiple design patterns, with MVC as the primary architectural pattern.

### Creational Patterns

- Singleton – Ensures only one instance of the Graph App exists.
- Abstract Factory – Used for UI elements such as labels and buttons, allowing flexible UI customization.

### Structural Patterns

- Facade – Simplifies interactions with the web framework and user input.
- Proxy – Handles input callbacks efficiently.
- Composite – Groups nodes into graph structures.

### Behavioral Patterns

- State Pattern – Manages different states of the program and executes appropriate behavior.
- Visitor Pattern – Allows traversal algorithms to operate on graph nodes without modifying their structure.

## Force-directed Graph Simulation

Graph Visualizer includes a force-directed graph simulation that models realistic physical interactions between nodes. The simulation applies several forces to create a natural graph layout:

- Repulsion Force – Nodes repel each other to avoid overlap, using a repulsion constant `k_r`.
- Attraction Force – Connected nodes attract each other like springs, controlled by an attraction constant `k_a` and a rest length parameter.
- Gravity Force – Nodes experience a gravitational pull toward a central point, determined by a gravity constant `k_g`.
- Velocity and Damping – The simulation updates node positions and velocities over time `time_step`, with damping to smooth movements.
- Explosion Force – An optional burst force can be applied to disperse nodes outward, simulating an explosion effect.

These physics-based forces create an intuitive and interactive experience when exploring graph structures.

## Acknowledgements

- [Project icon](https://www.svgrepo.com/svg/451006/knowledge-graph)

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/milosz275/graph-visualizer/blob/main/LICENSE) file for details.
