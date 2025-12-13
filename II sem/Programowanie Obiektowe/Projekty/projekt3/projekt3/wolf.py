from predator_animal import PredatorAnimal
from point import Point
from species import Species


class Wolf(PredatorAnimal):
    INITIAL_QUANTITY = 2
    STRENGTH = 9
    INITIATIVE = 5
    SYMBOL = 'W'

    def __init__(self, world, position=None):
        if position:
            super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        else:
            super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, Point(0, 0))
        self.species = "Wolf"

    def reproduce(self, position):
        free_space = self.world.get_random_free_space_around(position)

        if free_space is None:
            return

        new_organism = Wolf(self.world, free_space)
        self.world.set_organism(new_organism, free_space)

        message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
        print(message)
        self.world.add_turn_summary_message(message)