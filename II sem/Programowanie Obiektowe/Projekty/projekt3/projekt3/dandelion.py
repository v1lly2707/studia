import random
from plant import Plant
from point import Point


class Dandelion(Plant):
    INITIAL_QUANTITY = 2
    STRENGTH = 0
    INITIATIVE = 0
    SYMBOL = 'D'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(world, strength=self.STRENGTH, symbol=self.SYMBOL, position=position)
        self.species = "Dandelion"

    def reproduce(self, position):
        for _ in range(3):
            new_position = self.world.get_random_free_space_around(self.position)
            if new_position is not None:
                plant = Dandelion(self.world, new_position)
                self.world.set_organism(plant, new_position)

    def can_reproduce_this_turn(self):
        return random.randint(0, 31) == 0