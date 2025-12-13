from plant import Plant
from point import Point


class Grass(Plant):
    INITIAL_QUANTITY = 3
    STRENGTH = 0
    SYMBOL = 'G'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(world, strength=self.STRENGTH, symbol=self.SYMBOL, position=position)
        self.species = "Grass"

    def reproduce(self, position):
        child = Grass(self.world, position)
        self.world.set_organism(child, position)