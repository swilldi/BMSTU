class Point:
    def __init__(self, index, x, y):
        self.index = index
        self.x: float = x
        self.y: float = y

    def __eq__(self, other: Point):
        return self.index == other.index
