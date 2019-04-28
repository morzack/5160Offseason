import magicbot
import wpilib
from ctre import WPI_TalonSRX

# import serial

import robotmap

import motor_configuration

from components.drivetrain import Drivetrain
# from components.led_drivper import LEDDriver
from oi import OI

class MyRobot(magicbot.MagicRobot):
    drivetrain : Drivetrain
    # led_driver : LEDDriver

    def createObjects(self):
        self.front_left_motor = WPI_TalonSRX(robotmap.front_left_drive)
        self.front_right_motor = WPI_TalonSRX(robotmap.front_right_drive)
        self.back_left_motor = WPI_TalonSRX(robotmap.back_left_drive)
        self.back_right_motor = WPI_TalonSRX(robotmap.back_right_drive)

        motor_configuration.bulk_configure(self.front_left_motor, self.front_right_motor, self.back_left_motor, self.back_right_motor)

        self.left_motors = wpilib.SpeedControllerGroup(self.front_left_motor, self.back_left_motor)
        self.right_motors = wpilib.SpeedControllerGroup(self.front_right_motor, self.back_right_motor)

        self.front_left_motor.setInverted(True)
        self.front_right_motor.setInverted(True)

        self.drivetrain_object = wpilib.drive.DifferentialDrive(self.left_motors, self.right_motors)

        self.oi = OI()

        # self.arduino_serial_connection = serial.Serial(
        #     port=robotmap.com_port,
        #     baudrate=9600,
        #     parity=serial.PARITY_ODD,
        #     stopbits=serial.STOPBITS_TWO,
        #     bytesize=serial.SEVENBITS
        # )

        wpilib.CameraServer.launch('vision.py:main')

    def teleopInit(self):
        # self.led_driver.write_color()
        pass
    
    def teleopPeriodic(self):
        self.oi.execute()


if __name__ == "__main__":
    wpilib.run(MyRobot)