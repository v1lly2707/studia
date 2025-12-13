from plant import Plant
from point import Point


class Nightshade(Plant):
    INITIAL_QUANTITY = 2
    STRENGTH = 99
    SYMBOL = 'N'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(world, strength=self.STRENGTH, symbol=self.SYMBOL, position=position)
        self.species = "Nightshade"

    def reproduce(self, position):
        free_space = self.world.get_random_free_space_around(position)
        if free_space is not None:
            new_organism = Nightshade(self.world, free_space)
            self.world.set_organism(new_organism, free_space)
            message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
            self.world.add_turn_summary_message(message)

    def collision(self, other):
        other.die()
        message = f" {other.symbol} zjadl wilcze jagody ({self.position.x}, {self.position.y})"
        self.world.add_turn_summary_message(message)
        self.die()
        return True

    def can_reproduce_this_turn(self):
        return False

    def can_kill(self, other):
        return True