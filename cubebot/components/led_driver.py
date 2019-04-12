import serial

class Color:
    def __init__(self, r, g, b, a):
        # oh yeah a doesnt actually do anything btw
        self.r = r
        self.g = g
        self.b = b
        self.a = a

    def getColor(self):
        return [self.r, self.g, self.b, self.a]

    def __str__(self):
        return "{},{},{},{}\r\n".format(str(self.r).zfill(3), str(self.g).zfill(3), str(self.b).zfill(3), str(self.a).zfill(3))

class NeoPixelStrip:
    def __init__(self):
        self.color = Color(100, 100, 100, 50)

    def set_color(self, color):
        self.color = color

    def get_sending_string(self):
        """this just gets the string to send to the arduino, it doesnt send it through serial or anything"""
        return str(self.color)

class LEDDriver:
    arduino_serial_connection : serial.Serial

    def __init__(self):
        self.colors = {
            "red" : Color(150, 0, 0, 0),
            "blue" : Color(0, 50, 150, 0),
            "green" : Color(0, 150, 50, 0)
        }
        self.current_color = "blue"
    
    def write_color(self):
        self.arduino_serial_connection.write(str.encode(str(self.colors[self.current_color])))
        print(str(self.colors[self.current_color]))

    def execute(self):
        # self.write_color()
        pass