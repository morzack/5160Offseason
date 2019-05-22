// libraries
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <SimpleSoftwareServo.h>

// objects
SoftwareSerial bluetooth(A0, A1);

// TODO Proper configuration!!

// motors
AF_DCMotor leftDriveMotor(1);
AF_DCMotor rightDriveMotor(2);
AF_DCMotor liftMotor(3);

// servos
SimpleSoftwareServo rotator;
SimpleSoftwareServo grabber;
float rotatorPosition = 200;

// input handling things
float xInputMultiplier = 1;
float yInputMultiplier = 1;

// input variables
float xInput, yInput, liftInput, rotatorInput, grabberInput, autonomousInput;
// note the first 3 required a lowered lift
float groundPosInput, lv1PosInput, lv2PosInput, lv3PosInput;

bool driverControlled = true;

// programmed rotator positions; index goes with position from gnd to lv3
int rotatorPositions[4] = {10, 30, 70, 55};

// arduino setup
void setup() {
    bluetooth.begin(9600);
}

void loop() {
    // handle user input
    // it'll be formatted as x1,x2,y,beastMode
    while (bluetooth.available() > 0) {
        if (bluetooth.read() == 'z') { // iirc z is the delimiter for the data sent
            // grab the raw user input
            // drive controls
            xInput = bluetooth.parseFloat() * 100 * xInputMultiplier;
            yInput = bluetooth.parseFloat() * 100 * yInputMultiplier;
            // lift controls
            liftInput = bluetooth.parseFloat() * 100;
            // grabber control
            grabberInput = bluetooth.parseFloat();
            // rotator arm control and positions
            rotatorInput = bluetooth.parseFloat();
            groundPosInput = bluetooth.parseFloat();
            lv1PosInput = bluetooth.parseFloat();
            lv2PosInput = bluetooth.parseFloat();
            lv3PosInput = bluetooth.parseFloat();
            autonomousInput = bluetooth.parseFloat();

            // set rotator position
            if (groundPosInput == 1) {
                rotatorPosition = rotatorPositions[0];
            } else if (lv1PosInput == 1) {
                rotatorPosition = rotatorPositions[1];
            } else if (lv2PosInput == 1) {
                rotatorPosition = rotatorPositions[2];
            } else if (lv3PosInput == 1) {
                rotatorPosition = rotatorPositions[3];
            }
            
            // update rotator based on input
            if (rotatorInput == 1) {
                rotatorPosition -= 10;
            } else if (rotatorInput == -1) { 
                rotatorPosition -= 10;
            }
        }

        if (driverControlled) {
            // update things
            moveRotator(rotatorPosition);
            updateGrabber(grabberInput == 1);
            drive(xInput, yInput);
            lift(liftInput);
        }
        else {
            // yeet
            drive(0, 100);
            delay(3*1000);
            drive(0, 0);
            driverControlled = true;
        }
    }
}

// honestly none of this really matters if we use kbd to drive
float handleDeadzone(float i, int deadzone) {
    // handle a deadzone
    return (abs(i)>deadzone)?i:0;
}

float curveInput(float i) {
    // we'll use x^3 for motor curving because why not
    return i*i*i;
}

void drive(float x, float y) {
    float v = (100 - abs(x)) * (y/100) + y;
    float w = (100 - abs(y)) * (x/100) + x;
    float lPower = (v-w)*1.275;
    float rPower = (v+w)*1.275;
    rightDriveMotor.run(rPower >= 0 ? FORWARD : BACKWARD);
    leftDriveMotor.run(lPower >= 0 ? FORWARD : BACKWARD);
    rightDriveMotor.setSpeed(abs(rPower));
    leftDriveMotor.setSpeed(abs(lPower));
}

void lift(float l) {
    liftMotor.run(l >= 0 ? FORWARD : BACKWARD);
    liftMotor.setSpeed(abs(l)/2);
}

void moveRotator(int pos) {
    rotator.write(constrain(pos, 10, 120));
}

void updateGrabber(bool open) {
    grabber.write(open ? 119 : 179);
}