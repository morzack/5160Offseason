// libraries
#include <SoftwareSerial.h>
#include <AFMotor.h>

// custom code stuff
#include "drivetrain.h"

// objects
SoftwareSerial bluetooth(A0, A1);
DifferentialDrivetrain drivetrain(1, 3); // 1 is left port, 3 is right

// game state enumeration
enum GameState {disabled, autonomous, teleop};
GameState game_state = teleop;  // TODO: note that this is just for testing. start disabled probably

// input handling things
float x1_input_multiplier = 1;
float x2_input_multiplier = 1;
float y_input_multiplier = 1;
float x1_input, x2_input, y_input;
bool beast_mode;

// arduino setup
void setup() {
    bluetooth.begin(9600);
    drivetrain.set_power(0, 0);
}

void loop() {
    // handle user input
    // it'll be formatted as x1,x2,y,beastMode
    while (bluetooth.available() > 0) {
        if (bluetooth.read() == 'z') { // iirc z is the delimiter for the data sent
            // grab the raw user input
            x1_input = bluetooth.parseFloat()*x1_input_multiplier;
            x2_input = bluetooth.parseFloat()*x2_input_multiplier;
            y_input = bluetooth.parseFloat()*y_input_multiplier;
            beast_mode = bluetooth.parseFloat()==1;
            // handle deadzone and all that cool jazz
            float axis_deadzone = 0.05;
            x1_input = handle_deadzone(x1_input, 0.05);
            x2_input = handle_deadzone(x2_input, 0.05);
            y_input = handle_deadzone(y_input, 0.05);
            x1_input = curve_input(x1_input);
            x2_input = curve_input(x2_input);
            y_input = curve_input(y_input);
        }
    }

    // handle the game based on current state
    switch (game_state) {
        case disabled:
            drivetrain.disable();
            break;
        case autonomous:
            break;
        case teleop:
            drivetrain.enable();
            drivetrain.tank_drive(x1_input, x2_input);
            break;
    }

    // update robot components
    drivetrain.update_motors();
}

float handle_deadzone(float i, int deadzone) {
    // handle a deadzone
    return (abs(i)>deadzone)?i:0;
}

float curve_input(float i) {
    // we'll use x^3 for motor curving because why not
    return i*i*i;
}
