from wpilib.drive import DifferentialDrive
from ctre import WPI_TalonSRX

from oi import OI

class Drivetrain:
    drivetrain_object : DifferentialDrive
    oi : OI
    back_left_motor : WPI_TalonSRX
    back_right_motor : WPI_TalonSRX

    def __init__(self):
        pass

    def execute(self):
        povAngle = self.oi.driver_controller.getPOV()
        if povAngle == 90:
            self.back_left_motor.set(self.oi.driver_controller.getY())
            self.back_right_motor.set(-self.oi.driver_controller.getY()/2)
        elif povAngle == 270:
            self.back_right_motor.set(-self.oi.driver_controller.getY())
            self.back_left_motor.set(self.oi.driver_controller.getY()/2)
        elif self.oi.arcade_drive:
            self.drivetrain_object.arcadeDrive(self.oi.left_power, self.oi.right_power)
        else:
            self.drivetrain_object.tankDrive(self.oi.left_power, self.oi.right_power)
        self.drivetrain_object.setSafetyEnabled(False)