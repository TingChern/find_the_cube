# find_the_cube

## Overview

The project aims to create a virtual environment where users can interact with cubes and buttons. The environment consists of cubes that can move towards specific positions and change color based on events triggered by buttons. The main goal is to provide an engaging and interactive environment for users to explore.

## Key Challenges and Solutions

### Challenge 1: Managing Cube Behavior
- **Description**: One key challenge was managing the behavior of cubes, including their movement and color changes based on events.
- **Solution**: The CubeController class was implemented to handle cube behavior. It listens for events such as "game_init" to set initial positions and "button_click" to trigger color changes.

### Challenge 2: User Interaction
- **Description**: Another challenge was enabling user interaction with the environment, such as clicking on buttons to trigger events.
- **Solution**: The CubeController listens for "agent_click" events to detect when the cube with ID 0 is clicked. Upon clicking, it emits a "button_click" event, leading to cube shuffling and color changes.

## Installation and Running

### Prerequisites
- Docker installed on your machine

### Steps
1. Clone the repository: `git clone https://github.com/TingChern/find_the_cube.git`
2. run `docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash` to start the docker with `envrio` installed.
3. Inside the docker container, cd to the project directory.
4. Inside the docker container, run `esm start && apt-get install -y nlohmann-json3-dev && make clean && make && enviro` to start the http server, install the json library needed for this project, build the project, and start enviro.

## How to Use

1. Once the environment is running, open a web browser and go to [localhost](http://127.0.0.1/).
2. You'll see the virtual environment with cubes and buttons.

   <img width="1466" alt="Screenshot 2024-03-10 at 4 33 03 PM" src="https://github.com/TingChern/find_the_cube/assets/30149168/38e62ec3-24be-4f48-ba9e-67eaa9ca4326">

4. Click on the cubes to interact with them, if you find the right one, the cube color will randomly change to another color, and the cube will be shuffled.
5. You can also click on the  `Shuffle!` button if the cubes accidentally get stucked or if you just want to change to another color that make you happier.
6. Check out the video! ↓  ↓  ↓ </br>
[![Watch the video](https://img.youtube.com/vi/obGj_zfyUXc/default.jpg)](https://youtu.be/obGj_zfyUXc)

## Acknowledgments

- The project makes use of the enviro library for creating the virtual environment.
- Inspiration and guidance were taken from [enviro repo](https://github.com/klavinslab/enviro).
