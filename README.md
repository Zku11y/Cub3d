*This project has been created as part of the 42 curriculum by [Your Name / 1337 Team].*

## Description

The Cub3D project serves as a practical, simplified introduction to the world of 3D graphics rendering. The primary goal is to create a 3D perspective from a 2D map using the classic raycasting algorithm. 

**Overview:** The engine is highly optimized for performance. Instead of rendering the entire world, it calculates only what is currently visible on the screen. It works by shooting rays from the player's viewpoint for every vertical screen column. By calculating the distance from the player to the nearest wall intersection, the engine uses perspective projection mathematics to convert that distance into wall height on the screen. This allows for the creation of a pseudo-3D environment with very minimal resource costs.

## Instructions

Follow these steps to compile, install dependencies, and execute the game.

### Dependencies & Technical Choices
To handle window creation, events, and rendering, this project relies on specific graphics libraries and macOS frameworks:
* **GLFW:** Window management and OpenGL context creation to send render commands to the GPU.
* **MLX42:** A 42-curriculum wrapper library that obscures the deeper complications of GLFW.
* **macOS Frameworks:** * `-framework Cocoa`: The Mac Window Manager.
    * `-framework OpenGL`: The underlying graphics library.
    * `-framework IOKit`: The input handler for keyboard/mouse events.

### Installation and Execution

**1. Install GLFW**
You will need GLFW installed on your system. You can install it via Homebrew:
```bash
brew install glfw
```

**2. Install and Build MLX42**
Clone the MLX42 repository and build the library so the project can link to it:
```bash
git clone [https://github.com/codam-coding-college/MLX42.git](https://github.com/codam-coding-college/MLX42.git)
cd MLX42
cmake -B build && cmake --build build --parallel --config Release --target install
cd build
make
```
*(Note: This generates the `libmlx42.a` archive that the main program will automatically link against.)*

**3. Compile the Project**
Navigate to the Mandatory or Bonus directory of the project and compile the source code:
```bash
make
```

**4. Execution**
Run the compiled executable by passing a valid `.cub` map file as an argument:
```bash
./cub3D tests/file_name.cub
```

## Resources

While the [Lode V. Tutorial](https://lodev.org/cgtutor/raycasting.html) is widely considered the standard classic reference for raycasting (using vectors and matrices), this project's logic was primarily built using a simpler, more straightforward approach. 

**Articles & Documentation:**
* [Permadi Raycasting Tutorial](https://permadi.com/tutorial/raycast/rayc1.html) - The primary logic and math reference used for this engine.

**Video References:**
These videos, particularly those discussing the famous Wolfenstein 3D engine, were instrumental in understanding the algorithm:
* [Make Your Own Raycaster Part 1](https://youtu.be/gYRrGTC7GtA)
* [Making my First RAYCASTING Game in C++ - SFML Gamedev - Devlog 1](https://youtu.be/LUYxLjic0Bc)
* [Ray casting fully explained. Pseudo 3D game](https://youtu.be/g8p7nAbDz6Y)

### AI Usage

Artificial Intelligence was strictly used as a math and logic consultant rather than a code generator. Specifically, AI tools were utilized to:
* Break down and explain complex mathematical equations related to perspective projection.
* Filter and summarize complex math problems found in various online articles and resources. 
* Assist in shaping the raw mathematical concepts into a logical algorithm structure within my personal notes, which I then manually translated into C code.