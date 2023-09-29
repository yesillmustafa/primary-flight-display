# PFD (Primary Flight Display) [OpenGL ES2.0]
This project is a primary flight display simulator developed using OpenGL ES2.0.

Primary Flight Display (PFD) is a crucial flight instrument found in the cockpit of an aircraft or other air vehicles. The PFD provides pilots with the aircraft's essential flight data in a quick and comprehensible manner, aiding in the safe management of the aircraft.

https://github.com/yesillmustafa/primary-flight-display/assets/74787246/cf2a86e1-dcf7-4bc2-bbf0-b6c7bb533eea

## Libraries
The simulator uses the following libraries for OpenGL interactions and rendering.
- [GLFW](https://www.glfw.org/)
- [GLM](https://github.com/g-truc/glm)
- [stb image](https://github.com/nothings/stb) (included in the project)

## Elements
![PFD](https://github.com/yesillmustafa/primary-flight-display/assets/74787246/7efc8ab9-85a9-45f5-ad1a-ff5b1a4d8588)

## Features

- **Aircraft's Basic Status:** PFD displays the aircraft's horizontal (roll), vertical (pitch), and lateral (yaw) status. This information shows pilots the current position and angles of the aircraft, providing crucial data, especially regarding the horizontal and vertical inclination angles, which pertain to the aircraft's balance and altitude.

- **Speed Information:** PFD displays the aircraft's speed as airspeed, measured in knots. It is presented on the airspeed indicator.

- **Altitude Information:** PFD measures the aircraft's altitude in feet above sea level. The current altitude information for the aircraft is also displayed on the altimeter.

- **Heading Information:** PFD indicates the direction in which the aircraft is facing. This is crucial for determining the aircraft's heading and orientation.

- **Turn Information:** PFD indicates the aircraft's horizontal axis turn rate and slip/skid condition. This is used to monitor the aircraft's turning motion and lateral stability.

- **Vertical Speed Information:** PFD displays changes in the aircraft's vertical speed. This is used to control the rate of climb or descent.


  
## Prerequisites

Before you begin, ensure you have met the following requirements:

- [CMake](https://cmake.org/)
- [OpenGL ES2.0](https://www.khronos.org/opengles/)
- [GLFW 3.3](https://www.glfw.org/)
- [glm](https://github.com/g-truc/glm) (OpenGL Mathematics)

## Installation and Usage

To get started, follow these steps:
1. Clone the repository:
```bash
git clone https://github.com/yesillmustafa/primary-flight-display.git
```
2. Navigate to the repository folder:
```bash
cd primary-flight-display
```
3. Create a build directory:
```bash
mkdir build
cd build
```
4. Generate build files using CMake:
```bash
cmake ..
```
5. Build the project:
```bash
cmake --build .
```
6. Run the simulator:
```bash
./PFDScreen
```
7. Change the Aircraft's status and speed:
```bash
"W" and "S" keys for changing pitch values
"Q" and "E" keys for changing yaw values
"Y" and "H" keys for changing airspeed values
"Z" and "X" keys for changing Slip/Skid values 
```

## FAQ

#### What is GLFW?

GLFW is an open-source, multi-platform library for creating windows with OpenGL contexts and managing input, providing a foundation for building interactive graphical applications.

#### What is GLM?

GLM is a header-only C++ mathematics library designed for use in graphics programming and simulations, providing functions and classes for vector, matrix, and geometry operations.

#### What is stb_image?
stb_image is a single-header C library that provides a simple and fast way to perform image loading operations.

#### What is CMake?
CMake is a tool used for managing software projects; it simplifies the processes of compilation, configuration, and distribution of projects, enabling the creation of seamlessly functional projects on different platforms and compilers.


## Contributors
[Mustafa Yesil](https://github.com/yesillmustafa) <br>
[Ugur Celik](https://github.com/ugurclikk)
