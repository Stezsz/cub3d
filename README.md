# 🎮 Cub3D – 42 School Project (Raycasting Engine)
This project is part of the 42 School curriculum, focused on creating a dynamic 3D perspective inside a maze using raycasting techniques, inspired by the legendary Wolfenstein 3D - the first true FPS in video game history.

---

## 📋 Project Overview
**Main Concept:**
- Build a raycasting engine from scratch
- Create a 3D perspective from a 2D map
- Implement real-time rendering using MiniLibX
- Handle player movement and collision detection
- Parse configuration files and map validation

**Core Technologies:**
- C programming language
- MiniLibX graphics library
- Mathematical calculations for raycasting
- File parsing and validation
- Event handling and game loop

---

## 🎯 Technical Challenges

### **Map Parsing & Validation**
- Parse `.cub` configuration files
- Extract texture paths (North, South, East, West walls)
- Define floor and ceiling colors
- Validate map structure and boundaries
- Handle player starting position and orientation

### **Raycasting Algorithm**
- Implement DDA (Digital Differential Analyzer) algorithm
- Calculate ray distances for each screen column
- Determine wall height based on distance
- Handle texture mapping on walls
- Optimize rendering performance

### **Graphics & Rendering**
- Real-time 3D perspective rendering
- Texture application on walls
- Floor and ceiling color filling
- Smooth player movement
- Window management and pixel manipulation

### **Player Controls & Physics**
- WASD movement system
- Mouse or arrow key rotation
- Collision detection with walls
- Smooth movement and rotation
- ESC key to exit program

---

## 🔧 Key Learning Objectives

**Mathematical Concepts:**
- Understand trigonometry in game development
- Vector mathematics and 2D/3D coordinate systems
- Distance calculations and perspective projection
- Optimization of mathematical operations

**Graphics Programming:**
- Low-level graphics manipulation
- Pixel-by-pixel rendering techniques
- Understanding of how 3D engines work
- Performance optimization in real-time rendering

**System Programming:**
- Event-driven programming
- Memory management in graphics applications
- File I/O and parsing
- Cross-platform compatibility considerations

---

## 📁 Project Structure
```
cub3D/
├── src/
│   ├── parsing/          # Configuration and map parsing
│   ├── raycasting/       # Core raycasting algorithm
│   ├── rendering/        # Graphics and texture handling
│   ├── player/           # Player movement and controls
│   └── utils/            # Helper functions and utilities
├── maps/                 # Sample map files (.cub)
├── textures/             # Wall texture images
└── Makefile
```

---

## 🎮 Gameplay Features
- **First-person perspective** inside a 3D maze
- **Smooth player movement** in four directions
- **360-degree rotation** with mouse or keyboard
- **Textured walls** with different textures for each direction
- **Collision detection** preventing wall clipping
- **Clean exit** with ESC key or window close button

---

## 🏆 Skills Developed
- **Computer Graphics**: Understanding of rendering pipelines and 3D mathematics
- **Algorithm Implementation**: DDA algorithm and optimization techniques  
- **Game Development**: Real-time rendering and player input handling
- **System Programming**: Event loops, memory management, and performance
- **Problem Solving**: Debugging complex mathematical and visual issues

---

## 📚 Educational Value
This project serves as an excellent introduction to:
- 3D graphics programming fundamentals
- Game engine architecture basics
- Real-time rendering concepts
- Mathematical applications in programming
- Historical significance of raycasting in gaming

Cub3D recreates the raycasting technique used in Wolfenstein 3D, the first true FPS in videogame history, providing students with hands-on experience in graphics programming and game development fundamentals.

---
 
> ✅ **Final Grade: 100/100**
> Project made at [42 Lisboa](https://www.42lisboa.com/pt/)
> 👤 Author: Stephan Rodrigues Lassaponari ([@Stezsz](https://github.com/Stezsz))
