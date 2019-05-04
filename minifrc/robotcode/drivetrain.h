// drivetrain.h
#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <AFMotor.h>

class DifferentialDrivetrain {
        private:
                // motor ports
                int left_motor_port_;
                int right_motor_port_;
                // motor power to continually apply
                float left_power_;
                float right_power_;
                // motor objects
                AF_DCMOTOR left_motor_;
                AF_DCMOTOR right_motor_;
                // enabled flag (for braking or whatever)
                bool enabled_;
                // beast mode/reversed
                bool beast_mode_;
        public:
                Drivetrain(int left_port, int right_port);
                void set_power(float l_power, float r_power);
                void tank_drive(float left, float right);
                void arcade_drive(float power, float rotation);
                void enable();
                void disable();
                void update_motors();                               // note that this function should be spam called to ensure the motors are running frequently
}

#endif
