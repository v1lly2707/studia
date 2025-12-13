class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def distance(self, other):
        return abs(self.x - other.x) + abs(self.y - other.y)

    def get_neighbours(self, size):
        neighbours = []
        if self.x > 0:
            neighbours.append(Point(self.x - 1, self.y))
        if self.x < size - 1:
            neighbours.append(Point(self.x + 1, self.y))
        if self.y > 0:
            neighbours.append(Point(self.x, self.y - 1))
        if self.y < size - 1:
            neighbours.append(Point(self.x, self.y + 1))
        return neighbours