import random
from animal import Animal
from organism import Organism
from point import Point


class PredatorAnimal(Animal):
    def __init__(self, strength, initiative, age, symbol, world, position=None):
        super().__init__(strength, initiative, 0, symbol, world, position)

    def action(self):
        destination = self.world.get_random_neighbour(self.position)

        if not self.world.is_within_board_boundaries(destination):
            return

        if self.world.is_occupied(destination):
            other = self.world.get_organism_at(destination)
            self.collision(other)

        if not self.world.is_occupied(destination) and self.can_move_to(destination):
            self.move(destination)

    def collision(self, other):
        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)
            return True

        if other.can_be_killed_by(self):
            self.kill(other)
            return True
        elif other.can_kill(self):
            other.kill(self)

        return False

    def reproduce(self, position):
        if random.randint(0, 1) == 0:
            return

        super().reproduce(position)