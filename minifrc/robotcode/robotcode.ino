#include <SoftwareSerial.h>
#include <AFMotor.h>

// set all of the constants and things to use
int left_motor_port = 1;
int right_motor_port = 3;

// objects
SoftwareSerial bluetooth(A0, A1);

// motors
AF_DCMotor left_motors(left_motor_port);
AF_DCMotor right_motors(right_motor_port);

// input objects
float deadzone = -0.05;
float x_power_multiplier = 1;
float y_power_multiplier = 1;
float x_axis, y_axis;
bool beast_mode = false;

void setup() {
    bluetooth.begin(9600);
    drive(0, 0);
}

void loop() {
    // handle user input
    // it'll be formatted as x,y,beastMode
    while (bluetooth.available() > 0) {
        if (bluetooth.read() == 'z') { // iirc z is the delimiter for the data sent
            x_axis = bluetooth.parseFloat()*x_power_multiplier;
            y_axis = bluetooth.parseFloat()*y_power_multiplier;
            int b_m = bluetooth.parseInt();
        }
    }
}

void tank_drive(int left_axis, int right_axis) {
    // tank drive given the power and rotation
    // basically do the beast mode calculations in math like a sane person
    int lV = !beast_mode?left_axis:-right_axis;
    int rV = !beast_mode?right_axis:-left_axis;
    // run motors
    left_motors.run((lV>0)?FORWARD:BACKWARD);
    left_motors.setSpeed(abs(lV));
    right_motors.run((rV>0)?FORWARD:BACKWARD);
    right_motors.setSpeed(abs(rV));
}

float handle_deadzone(int i, int deadzone) {
    // handle a deadzone
    return (abs(i)>deadzone)?i:0;
}
