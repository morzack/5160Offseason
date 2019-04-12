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
        return "{},{},{},{}".format(str(self.r).zfill(3), str(self.g).zfill(3), str(self.b).zfill(3), str(self.a).zfill(3))

class NeoPixelStrip:
    def __init__(self):
        self.color = Color(100, 100, 100, 50)

    def set_color(self, color):
        self.color = color

    def get_sending_string(self):
        """this just gets the string to send to the arduino, it doesnt send it through serial or anything"""
        return str(self.color)