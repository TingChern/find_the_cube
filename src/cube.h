#ifndef __CUBE_AGENT__H
#define __CUBE_AGENT__H 
#include <stdlib.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "enviro.h"
#include <string>
using namespace enviro;

/*
   This code defines a CupController class and a cube class.
   CupController manages the behavior of cups in the environment, including their movement and appearance.
   Cups are controlled to move towards specific positions and change color based on events.

   - CubeController:
     - Initializes with an index for identifying cups and initializing their positions.
     - Listens for "game_init" events to set initial goal positions for cups.
     - Listens for events specific to each cube's index to update goal positions and style based on color.
     - Listens for "agent_click" events to trigger a "button_click" event when the cube with ID 0 is clicked.

   - Cube:
     - Represents a cube in the environment.
     - Instantiates a CubeController to manage its behavior.

   Note: This code assumes the existence of an "enviro" namespace, relevant libraries, and uses the nlohmann::json library for JSON manipulation.
*/

class CubeController : public Process, public AgentInterface {
    // Constructor for CubeController class
    public:
    CubeController() : Process(), AgentInterface(){
        static int i = 0;
        static int j = 0;
        idx = i++;
    }
    // Initialization function
    void init() {
        // Listens for "game_init" events to set initial goal positions for cubes
        watch("game_init", [this](Event e){
            goal_x = e.value()[std::to_string(idx)][0];
            goal_y = e.value()[std::to_string(idx)][1];
        });

        // Listens for events specific to each cube's index to update goal positions and style based on color
        watch(std::to_string(idx), [this](Event e){
            // set_style(arr[2]);
            goal_x = e.value()["x"];
            goal_y = e.value()["y"]; 
            int color = e.value()["color"];
            set_style(arr[color]);
        });

        // if the target cube is clicked, emit the button click event, which shuffles the cubes and changes the color of all cubes
        watch("agent_click", [this](Event e) {
        if ( e.value()["id"] == 0 && id() == 0) {
            emit(Event("button_click", {
            }));
        }   
        });
    }
    /*
      Starts CupController instance.
      This function is empty as no specific action is required upon starting.
    */
    void start() {}
    /*
      Updates CupController instance.
      This function moves cube towards its goal position.
    */
    void update() {
        // damp_movement();
        move_toward(goal_x, goal_y,10000,200);// Moves cube towards its goal position
    }
    
    void stop() {}
    int idx; // Unique index for identifying cubes
    double goal_x, goal_y;
    std::string cube_name;
    void set_cube_name(std::string s) { cube_name = s; };  // Function to set cube's name
    //style for 
    json arr [7] =  {
        // Array containing JSON objects representing different colors for cups
        "{ \"fill\": \"red\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"orange\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"yellow\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"lightgreen\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"blue\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"purple\", \"stroke\": \"black\" }"_json,
        "{ \"fill\": \"black\", \"stroke\": \"black\" }"_json
    };
};

class Cube : public Agent {
    public:
    Cube(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CubeController c;
};

DECLARE_INTERFACE(Cube)

#endif