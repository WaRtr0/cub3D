# Cub3D
> Group project of the 42 School common core. A pseudo 3D engine built from scratch in C using the Raycasting technique. Inspired by the world-famous 1992 game Wolfenstein 3D, this project explores the mathematical concepts behind early 3D rendering.

![Status](https://img.shields.io/badge/Status-Completed-success)
&emsp;
![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-000000?logo=make&logoColor=white)
![Valgrind](https://img.shields.io/badge/Valgrind-Leak_Free-28a745)

## Gameplay & Rendering Preview

<div align="center">
  <img src="https://github.com/user-attachments/assets/0410c6cd-90a6-4853-8a3a-60ad3ba1869e" width="40%" alt="Cub3D Gameplay Preview">
</div>

## Introduction

The goal is to create a dynamic 3D representation of a labyrinth from a 2D map contained in .cub files. 
The rendering is done using the **MiniLibX**, a basic X-Window graphics library provided by the school.

This project revolves around mathematics (Trigonometry, Vectors) and performance optimization, as every pixel on the screen is calculated and drawn from scratch without the help of modern 3D APIs like OpenGL or Vulkan.

## Features

#### Core Features
- **Raycasting Algorithm:** Uses the Digital Differential Analysis (DDA) algorithm to calculate ray intersections and render walls accurately without fisheye distortion.
- **Texture Mapping:** Reads XPM images and maps them pixel by pixel onto the rendered walls depending on the compass direction (North, South, East, West).
- **Map Parsing:** A robust `.cub` file parser that checks for map enclosures, invalid characters, and duplicate player spawns.

#### Advanced & Bonus Features
- **Custom 2D Layer Engine:** Developed a dedicated layer-based rendering system (Z-index simulation). This allows for clean and efficient superposition of 2D UI elements over the 3D environment.
- **Smooth Movement:** Frame-independent player movement and camera rotation with collision detection (sliding along walls).
- **Interactive Animated Doors:** Raycasting extension to detect, render, and animate doors. Players can open and close them from a distance using an action key.
- **Dynamic Minimap:** A real-time, top-down 2D minimap integrated via the layer engine, which continuously tracks and centers on the player's position and field of view.
- **Textured Floor & Ceiling:** Replaced flat RGB colors with textured rendering for the environment, requiring complex perspective calculations and heavy CPU rendering optimization.

## Install project

This project requires a Linux environment (or WSL) with the standard X11 libraries installed to compile the MiniLibX.

```bash
git clone --recursive git@github.com:WaRtr0/cub3D.git
cd cub3D
```

## Start the game

#### 1 - Build the executable

```bash
make bonus
```

#### 2 - Run the game with any map (here mapbonus.cub)
```bash
./cub3d_bonus map/mapbonus.cub
```
*(You can create your own `.cub` maps in the `map/` directory)

## Controls
- `W`, `A`, `S`, `D` : Move the player
- `←` , `→` / `Mouse` : Rotate camera
- `Space` : Open/Close aimed doors
- `ESC` : Quit game

## The team
- [Maxence Morot](https://github.com/WaRtr0)
- [Gabriel Rivo](https://github.com/GabrielRivo)
