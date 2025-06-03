# cub3d – 42 School Project

The **cub3d** project is a 3D graphical rendering challenge that simulates a first-person view using **raycasting**, inspired by the classic Wolfenstein 3D. The goal is to create a basic 3D engine using **MiniLibX**, allowing the player to navigate a maze-like map with textures, walls, and smooth movement.

---

## Main Objectives

- Parse and validate a `.cub` map file with correct settings and layout.
- Render a 3D environment from a 2D map using **raycasting**.
- Implement movement and camera rotation using keyboard input.
- Use **MiniLibX** to display the game window and handle events.
- Avoid glitches such as walking through walls or invalid map rendering.

---

## Problem Breakdown

- **Raycasting:** A technique to render 3D-like environments by projecting rays from the player’s point of view to detect wall distances.
- **Map Parsing:** The `.cub` file contains the map layout, wall textures, and color settings for the floor and ceiling.
- **Player Controls:** The player can move forward, backward, sideways, and rotate the camera view left or right.
- **Graphics:** Walls are textured using `.xpm` files, and the floor/ceiling are rendered with solid colors.
- **Collision:** The player cannot move through walls — collision detection is required.

---

## Example Usage

```bash
$ make
$ ./cub3d maps/example.cub
```

Keyboard controls:
- `W`, `A`, `S`, `D` – Move forward, left, backward, right  
- `←`, `→` – Rotate camera left/right  
- `ESC` – Exit the program

---

## 📘 Conclusion

The **cub3d** project is a deep dive into **raycasting**, **2D to 3D projection**, and **real-time rendering** using basic graphical libraries. It challenges the developer to manage low-level drawing, geometry math, and efficient input handling — all written in **pure C** using the **MiniLibX** graphics library.

---

> ✅ **Final Grade: /100**  
> Project made at [42 Lisboa](https://www.42lisboa.com)  
> 👤 Author: Stephan Rodrigues Lassaponari ([@Stezsz](https://github.com/Stezsz))

