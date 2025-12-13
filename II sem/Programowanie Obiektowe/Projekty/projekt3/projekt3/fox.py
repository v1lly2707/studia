from predator_animal import PredatorAnimal
from point import Point

class Fox(PredatorAnimal):
    INITIAL_QUANTITY = 2
    STRENGTH = 3
    INITIATIVE = 7
    SYMBOL = 'F'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.species = "Fox"

    def reproduce(self, position):
        free_space = self.world.get_random_free_space_around(position)
        if free_space:
            new_organism = Fox(self.world, free_space)
            self.world.set_organism(new_organism, free_space)

            message = f" {self.SYMBOL} rozmnozyl sie na ({position.x}, {position.y})"
            self.world.add_turn_summary_message(message)

    def collision(self, other):
        if self.can_kill(other):
            self.kill(other)
            return True

        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)

        return False