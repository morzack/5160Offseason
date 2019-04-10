import magicbot
import wpilib
from ctre import WPI_TalonSRX

import robotmap

import motor_configuration

from components.drivetrain import Drivetrain
from oi import OI

class MyRobot(magicbot.MagicRobot):
    drivetrain : Drivetrain

    def createObjects(self):
        self.front_left_motor = WPI_TalonSRX(robotmap.front_left_drive)
        self.front_right_motor = WPI_TalonSRX(robotmap.front_right_drive)
        self.back_left_motor = WPI_TalonSRX(robotmap.back_left_drive)
        self.back_right_motor = WPI_TalonSRX(robotmap.back_right_drive)

        motor_configuration.bulk_configure(self.front_left_motor, self.front_right_motor, self.back_left_motor, self.back_right_motor)

        self.left_motors = wpilib.SpeedControllerGroup(self.front_left_motor, self.back_left_motor)
        self.right_motors = wpilib.SpeedControllerGroup(self.front_right_motor, self.back_right_motor)

        self.drivetrain_object = wpilib.drive.DifferentialDrive(self.left_motors, self.right_motors)

        self.oi = OI()

        wpilib.CameraServer.launch('vision.py:main')

    def teleopInit(self):
        pass
    
    def teleopPeriodic(self):
        self.oi.execute()


if __name__ == "__main__":
    wpilib.run(MyRobot)