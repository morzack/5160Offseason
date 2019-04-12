import ctre

def configure_drivetrain(motor: ctre.WPI_TalonSRX):
    """
    Configure a given motor controller for drivetrain usage
        :param motor:ctre.WPI_TalonSRX: The motor to be configured
    """
    # TODO make sure to uncomment next line on first test/deploy
    # motor.configFactoryDefault()
    motor.configOpenLoopRamp(0.2)
    motor.clearStickyFaults()
    motor.enableCurrentLimit(True)
    motor.configContinuousCurrentLimit(10)
    motor.configPeakCurrentLimit(0)
    motor.setNeutralMode(ctre.NeutralMode.Brake)

def bulk_configure(*args):
    for _, motor in enumerate(args):
        configure_drivetrain(motor)