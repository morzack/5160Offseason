// drivetrain.h
#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <AFMotor.h>

class DifferentialDrivetrain {
        private:
                // motor power to continually apply
                float left_power_;
                float right_power_;
                // motor objects
                AF_DCMotor* left_motor_;
                AF_DCMotor* right_motor_;
                // enabled flag (for braking or whatever)
                bool enabled_;
                // beast mode/reversed
                bool beast_mode_;
        public:
                DifferentialDrivetrain(uint8_t left_port, uint8_t right_port);
                void set_power(float l_power, float r_power);
                void tank_drive(float left, float right);
                void arcade_drive(float power, float rotation);
                void enable();
                void disable();
                void update_motors();                               // note that this function should be spam called to ensure the motors are running frequently
};

#endif
