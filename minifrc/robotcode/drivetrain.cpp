// drivetrain.cpp
#include "drivetrain.h"
#include <AFMotor.h>
#include <stdlib.h>

DifferentialDrivetrain::DifferentialDrivetrain(uint8_t left_port, uint8_t right_port) {
        left_motor_ = new AF_DCMotor(left_port);
        right_motor_ = new AF_DCMotor(right_port);
        left_power_ = 0;
        right_power_ = 0;
        enabled_ = true; // is it really a good idea to start enabled? eh why not
        beast_mode_ = false;
}

void DifferentialDrivetrain::set_power(float l_power, float r_power) {
        left_power_ = l_power;
        right_power_ = r_power;
}

void DifferentialDrivetrain::tank_drive(float left, float right) {
        // when beast mode is enabled the sides switch as well as the powers
        int left_velocity = !beast_mode_ ? left : -right;
        int right_velocity = !beast_mode_ ? right : -left;
        // set motor powers
        DifferentialDrivetrain::set_power(left_velocity, right_velocity);
}

void DifferentialDrivetrain::arcade_drive(float power, float rotation) {
        // code (kind of) taken from CD because i'm lazy
        int left_velocity = power+rotation;
        int right_velocity = power-rotation;
        // assuming capped motor speed is 1
        left_velocity = left_velocity>1 ? 1 : (left_velocity<-1 ? -1 : left_velocity);
        right_velocity = right_velocity>1 ? 1 : (right_velocity<-1 ? -1 : right_velocity);
        // set motor powers
        DifferentialDrivetrain::set_power(left_velocity, right_velocity);
}

void DifferentialDrivetrain::enable() {
        enabled_ = true;
}

void DifferentialDrivetrain::disable() {
        enabled_ = false;
}

void DifferentialDrivetrain::update_motors() {
        // set motor direction
        left_motor_->run((left_power_>0) ? FORWARD : BACKWARD);
        right_motor_->run((right_power_>0) ? FORWARD : BACKWARD);
        // set motor powers depending on enabled state
        if (enabled_) {
                left_motor_->setSpeed(abs(left_power_));
                right_motor_->setSpeed(abs(right_power_));
        } else {
                left_motor_->setSpeed(0);
                right_motor_->setSpeed(0);
        }
}
