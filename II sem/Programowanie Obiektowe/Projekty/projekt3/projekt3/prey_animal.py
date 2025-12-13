from animal import Animal
from organism import Organism
from point import Point


class PreyAnimal(Animal):
    def __init__(self, strength, initiative, age, symbol, world, position=None):
        super().__init__(strength, initiative, age, symbol, world, position)

    def action(self):
        destination = self.world.get_random_neighbour(self.position)

        if not self.world.is_within_board_boundaries(destination):
            return

        if self.world.is_occupied(destination):
            other = self.world.get_organism_at(destination)
            self.collision(other)
            return

        if self.can_move_to(destination):
            self.move(destination)
            return

    def collision(self, other):
        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)
            return True

        if other.can_be_killed_by(self):
            self.kill(other)
            return True
        elif other.can_kill(self):
            other.collision(self)
            return True

        return False