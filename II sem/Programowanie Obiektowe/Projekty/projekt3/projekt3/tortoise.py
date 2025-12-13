import random
from prey_animal import PreyAnimal
from point import Point
from organism import Organism


class Tortoise(PreyAnimal):
    INITIAL_QUANTITY = 2
    STRENGTH = 2
    INITIATIVE = 1
    SYMBOL = 'T'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.species = "Tortoise"

    def reproduce(self, position):
        if random.randint(0, 2) != 0:
            return

        free_space = self.world.get_random_free_space_around(position)

        if free_space:
            new_organism = Tortoise(self.world, free_space)
            self.world.set_organism(new_organism, free_space)

            message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
            self.world.add_turn_summary_message(message)

    def collision(self, other):
        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)
            return True

        if self.can_kill(other):
            self.kill(other)
            return True
            # else:
            #     other.collision(self)

            if self.world.get_organism_at(self.position):
                destination = self.world.get_random_neighbour(self.position)

                if self.world.is_within_board_boundaries(destination) and not self.world.is_occupied(destination):
                    self.move(destination)
            return True

    def action(self):
        if random.randint(0, 3) == 0:
            return

        super().action()

    def can_be_killed_by(self, other):
        if isinstance(other, Tortoise):
            return False

        return self.strength < other.strength and other.strength > 5