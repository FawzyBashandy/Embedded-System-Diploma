## High Pressure Detector Project - STM32F103C6 Board with Cortex-M3
<p align="center">
  <img src="https://github.com/FawzyBashandy/Embedded-System-Diploma/assets/131293631/a6b451de-41d0-4126-98b8-cfc0ed80d012" alt="Board Specs" width="600" />

### Project Objective
The main objective of this project is to activate an alarm when the pressure value exceeds a specific threshold of 20 bar.

### Google Drive
You can access the project files on [Google Drive](https://drive.google.com/drive/folders/1LUYz2e1n_gIxd5v0YzMyWPvdpXCoBIPp?usp=drive_link).

### Project Components
This project was completed by developing (writing) the following:

- Custom `main.c` file
- State files for each stage (pressure sensor, main algorithm, alarm actutator)
- `startup.c` and `linker_script.ld` files
- Automation `makefile`
- Simulation using Proteus

### Development Tools Used
The following tools were used in the development of this project:

1. TTool - for system architecture
2. Visual Studio Code
3. ARM Cross Toolchain
4. Proteus
5. Terminal
6. Git & Github

### Note
To run this project, you need to install the source code and the mentioned tools. Open the project directory in the terminal and execute the command `make`.

**Additionally, the `map_file` containing all project symbols and memory sections can be found in the `bin` folder.**

### Working Code with Board Simulator
You can watch the simulation video demonstrating the working code on the board simulator at the following link: [Simulation Video](https://drive.google.com/file/d/12OI7nQAV8nQWkSrKlTBqrZyf6eAM3MoZ/view?usp=drive_link)
