from wpilib import XboxController

import math

class OI:
    def __init__(self):
        self.reversed = False
        self.arcade_drive = True
        self.turbo = False

        self.controls = {
            "reverse" :         XboxController.Button.kB,
            "arcade_switch" :   XboxController.Button.kX,
            "turbo" :           XboxController.Button.kY,
            "reset" :           XboxController.Button.kA
        }

        self.driver_controller = XboxController(0)

        self.left_power = 0
        self.right_power = 0

    def get_button_config_pressed(self, controller, button_name):
        return controller.getRawButtonPressed(self.controls[button_name])

    def get_button_config_held(self, controller, button_name):
        return controller.getRawButton(self.controls[button_name])

    def curve_input(self, i):
        deadzone = 0.1
        if abs(i) < deadzone:
            return 0
        return math.pow(i, 3)/2

    def reset(self):
        self.left_power = 0
        self.right_power = 0
        self.reversed = False
        self.arcade_drive = True
        self.turbo = False

    def execute(self):
        if self.get_button_config_pressed(self.driver_controller, "reverse"):
            self.reversed = not self.reversed
        
        if self.get_button_config_pressed(self.driver_controller, "arcade_switch"):
            self.arcade_drive = not self.arcade_drive

        self.turbo = self.get_button_config_held(self.driver_controller, "turbo")

        self.left_power = self.driver_controller.getY(XboxController.Hand.kLeft)
        
        if self.arcade_drive:
            self.right_power = self.driver_controller.getX(XboxController.Hand.kRight)
        else:
            self.right_power = self.driver_controller.getY(XboxController.Hand.kRight)

        reversed_constant = -1 if self.reversed else 1
        self.left_power = self.curve_input(self.left_power*reversed_constant)
        self.right_power = self.curve_input(self.right_power*reversed_constant)
        
        if self.turbo:
            self.left_power *= 2
            self.right_power *= 2

        print(self.left_power)

        if self.get_button_config_pressed(self.driver_controller, "reset"):
            self.reset()