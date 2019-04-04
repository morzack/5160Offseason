from wpilib.drive import DifferentialDrive

from oi import OI

class Drivetrain:
    drivetrain_object : DifferentialDrive
    oi : OI

    def __init__(self):
        pass

    def execute(self):
        if self.oi.arcade_drive:
            self.drivetrain_object.arcadeDrive(self.oi.left_power, self.oi.right_power)
        else:
            self.drivetrain_object.tankDrive(self.oi.left_power, self.oi.right_power)