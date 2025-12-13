import random
from prey_animal import PreyAnimal
from organism import Organism
from point import Point


class Sheep(PreyAnimal):
    INITIAL_QUANTITY = 4
    STRENGTH = 4
    INITIATIVE = 4
    SYMBOL = 'S'

    def __init__(self, world, position=None):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.species = "Sheep"

    def reproduce(self, position):
        if random.randint(0, 2) != 0:
            return

        free_space = self.world.get_random_free_space_around(position)

        if free_space is None:
            return

        new_organism = Sheep(self.world, free_space)
        self.world.set_organism(new_organism, free_space)

        message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
        self.world.add_turn_summary_message(message)