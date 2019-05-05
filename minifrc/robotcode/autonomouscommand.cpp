// autonomouscommand.cpp
#include "autonomouscommand.h"
#include "drivetrain.h"
#include "Arduino.h"

// Command implementation

Command::Command(Command *next_command) {
        start_time_ = 0;
        running_ = false;
        next_command_ = next_command;
}

void Command::start() {
        start_time_ = millis();
        running_ = true;
}

void Command::stop() {
        running_ = false;
}

void Command::update() {
        if (running_) {
            if (Command::is_finished()) {
                    Command::finish();
            }
            else {
                    Command::run();
            }
        }
        else {
                next_command_->update();
        }
}

void Command::finish() {
        running_ = false;
        next_command_->start();
}


// TimedCommand implementation

TimedCommand::TimedCommand(float duration_seconds, Command *next_command) : Command(next_command) {
        unsigned long duration_millis = (unsigned long) (duration_seconds*1000);
        duration_ = duration_millis;
}

bool TimedCommand::is_finished() {
        return millis()-start_time_ >= duration_;    // basically is only done when its run past duration
}


// JustSendIt implementation. this is the one to send it off the platform, duh

// we'll be sending it for 3 seconds
JustSendIt::JustSendIt(DifferentialDrivetrain *drive, Command *next_command) : TimedCommand((float) 3, next_command) {
        drivetrain_ = drive;
}

void JustSendIt::run() {
        drivetrain_->enable();
        drivetrain_->set_power(1, 1);
        drivetrain_->update_motors();
}


// IdleLoop implementation

IdleLoop::IdleLoop() : Command(NULL) {}

void IdleLoop::run() {}

bool IdleLoop::is_finished() {
        return false;
}
