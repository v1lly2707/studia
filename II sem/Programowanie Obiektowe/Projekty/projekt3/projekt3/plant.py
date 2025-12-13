import random
from organism import Organism
from point import Point


class Plant(Organism):
    INITIATIVE = 0

    def __init__(self, world, strength=0, symbol='', position=Point(-1, -1)):
        super().__init__(strength, self.INITIATIVE, 0, symbol, world, position)
        self.species = "Plant"

    def action(self):
        if self.can_reproduce_this_turn() and self.has_free_space():
            position = self.world.get_random_free_space_around(self.position)
            if position:
                self.reproduce(position)

    def collision(self, other):
        return False

    def die(self):
        self.world.remove(self)

    def kill(self, other):
        other.die()
        message = f" {other.symbol} zostal zabity przez {self.symbol} na ({self.position.x}, {self.position.y})"
        self.world.add_turn_summary_message(message)

    def can_kill(self, other):
        return False

    def can_be_killed_by(self, other):
        if self.__class__ == other.__class__:
            return False
        return other.strength >= self.strength

    def has_free_space(self):
        return self.world.has_free_space(self.position)

    def can_reproduce_this_turn(self):
        return random.randint(0, 11) == 0

    def reproduce(self, position):
        pass