# Cub3D

> A pseudo 3D engine built from scratch in C using the Raycasting technique. Inspired by the world-famous 1992 game Wolfenstein 3D, this project explores the mathematical concepts behind early 3D rendering.

![Status](https://img.shields.io/badge/Status-Completed-success)
&emsp;
![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-000000?logo=make&logoColor=white)

## Gameplay & Rendering Preview

<div align="center">
  <img src="https://github.com/user-attachments/assets/TON_LIEN_GIF_ICI" width="80%" alt="Cub3D Gameplay Preview">
</div>

## Introduction

**Cub3D** is a graphics project from the 42 School common core. The goal is to create a dynamic 3D representation of a labyrinth using only a 2D map and the **MiniLibX** (a basic X-Window graphics library provided by the school). 

This project was a deep dive into mathematics (Trigonometry, Vectors) and performance optimization, as every pixel on the screen is calculated and drawn from scratch without the help of modern 3D APIs like OpenGL or Vulkan.

## Features

- **Raycasting Engine:** Uses the Digital Differential Analysis (DDA) algorithm to calculate ray intersections and render walls accurately.
- **Texture Mapping:** Reads XPM images and maps them pixel by pixel onto the rendered walls depending on the compass direction (North, South, East, West).
- **Map Parsing:** A robust `.cub` file parser that checks for map enclosures, invalid characters, and duplicate player spawns.
- **Smooth Movement:** Frame-independent player movement and camera rotation with collision detection (sliding along walls).
- **Memory Management:** Strict adherence to C programming standards, ensuring no memory leaks during execution, rendering, or window closing.

## Install project

This project requires a Linux environment (or WSL) with the standard X11 libraries installed to compile the MiniLibX.

```bash
git clone git@github.com:WaRtr0/cub3D.git
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
- `ESC` : Quit game

## The team
- [Maxence Morot](https://github.com/WaRtr0)
- [Gabriel Rivo](https://github.com/GabrielRivo)
