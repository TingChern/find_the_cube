#ifndef __BUTTON_AGENT__H
#define __BUTTON_AGENT__H 
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include "enviro.h"

using namespace enviro;

/*
   This code defines a ButtonController class and a Button class.
   ButtonController manages the positions and colors of buttons in the environment.
   It shuffles the positions of buttons upon receiving a "button_click" event,
   ensuring no two consecutive button shuffles have the same color.

   - ButtonController:
     - Initializes with predefined positions for buttons.
     - Emits a "game_init" event with initial button positions upon initialization.
     - Listens for "button_click" events to trigger a shuffle of button positions.
     - Shuffles button positions and assigns a random color to each button.
     - Emits events for each button's new position and color after shuffling.

   - Button:
     - Represents a button in the environment.
     - Instantiates a ButtonController to manage its behavior.

   Note: This code assumes the existence of an "enviro" namespace and relevant libraries.
*/



class ButtonController : public Process, public AgentInterface {
    /*
      Constructor for ButtonController class.
      Initializes ButtonController with predefined positions for buttons.
    */
    public:
    ButtonController() : Process(), AgentInterface(),pos1(-600,200),pos2(0,200),pos3(600,200),pos4(-600,0),pos5(0,0),pos6(600,0),pos7(-600,-200),pos8(0,-200),pos9(600,-200) {}

    /*
      Shuffles the elements of a vector randomly.
      Template function that takes a vector as input and shuffles its elements using a random number generator.
    */ 
    template<typename T>
    void shuffleVector(std::vector<T>& vec) {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Shuffle the vector
        std::shuffle(vec.begin(), vec.end(), gen);
    }
    /*
     Initializes ButtonController instance.
     Adds predefined cube positions to the 'pos' vector.
     Emits a "game_init" event with initial cube positions.
     Listens for "button_click" events to trigger cube shuffling.
    */
    void init() {
        pos.push_back(pos1);
        pos.push_back(pos2);
        pos.push_back(pos3);
        pos.push_back(pos4);
        pos.push_back(pos5);
        pos.push_back(pos6);
        pos.push_back(pos7);
        pos.push_back(pos8);
        pos.push_back(pos9);

        emit(Event("game_init", {
            { "0", {pos[0].first, pos[0].second} }, 
            { "1", {pos[1].first, pos[1].second} },
            { "2", {pos[2].first, pos[2].second} },
            { "3", {pos[3].first, pos[3].second} }, 
            { "4", {pos[4].first, pos[4].second} },
            { "5", {pos[5].first, pos[5].second} },
            { "6", {pos[6].first, pos[6].second} }, 
            { "7", {pos[7].first, pos[7].second} },
            { "8", {pos[8].first, pos[8].second} }
        }));

        // Listen for button_click events
        watch("button_click", [this](Event e) {
        
            // Shuffle cube positions
            shuffleVector(pos);

            // Generate a random color for cube, the color should be different with the previous color
            int color = rand() % 7;
            while(cur_color == color){
                color = rand() % 7;
            }

            // Emit new position and color for each cube
            for(int i =0;i<9;i++){ 

                emit(Event(std::to_string(i), {
                    { "x", pos[i].first}, 
                    { "y", pos[i].second},
                    { "color", color}
                }));
            }
        });
    }

    /*
      Starts ButtonController instance.
      This function is empty as no specific action is required upon starting.
    */
    void start() {}

    /*
     Updates ButtonController instance.
     This function is empty as there are no ongoing updates for the ButtonController.
    */
    void update(){
    }

    /*
     Stops ButtonController instance.
     This function is empty as no specific action is required upon stopping.
    */
    void stop() {}
    std::pair<int, int> pos1;
    std::pair<int, int> pos2;
    std::pair<int, int> pos3;
    std::pair<int, int> pos4;
    std::pair<int, int> pos5;
    std::pair<int, int> pos6;
    std::pair<int, int> pos7;
    std::pair<int, int> pos8;
    std::pair<int, int> pos9;
    std::vector<std::pair<int,int>> pos;
    int cur_color;
};

class Button : public Agent {
    public:
    Button(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    ButtonController c;
};

DECLARE_INTERFACE(Button)

#endif