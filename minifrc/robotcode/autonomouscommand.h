// autonomouscommand.h
#ifndef AUTONOMOUSCOMMAND_H_
#define AUTONOMOUSCOMMAND_H_

// basically include all of the robot parts to use
#include "drivetrain.h"

class Command {
        protected:
                unsigned long start_time_;
                bool running_;
                Command *next_command_;
        public:
                Command(Command *next_command);
                void start();
                void stop();
                virtual void run();
                void update();
                void finish();
                virtual bool is_finished();
};

class TimedCommand : public Command {
        private:
                unsigned long duration_;
        public:
                TimedCommand(float duration_seconds, Command *next_command);
                virtual void run();
                bool is_finished();
};

class JustSendIt : public TimedCommand {
        private:
                DifferentialDrivetrain *drivetrain_;
        public:
                JustSendIt(DifferentialDrivetrain *drive, Command *next_command);
                virtual void run();
};

#endif
