from plant import Plant
from point import Point


class Guarana(Plant):
    INITIAL_QUANTITY = 2
    STRENGTH = 0
    SYMBOL = 'U'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(world, strength=self.STRENGTH, symbol=self.SYMBOL, position=position)
        self.species = "Guarana"

    def reproduce(self, position):
        free_space = self.world.get_random_free_space_around(position)
        if free_space is not None:
            new_organism = Guarana(self.world, free_space)
            self.world.set_organism(new_organism, free_space)
            message = f" {self.symbol} rozmnozyla sie na ({position.x}, {position.y})"
            self.world.add_turn_summary_message(message)

    def collision(self, other):
        if self.can_be_killed_by(other):
            other.strength += 3
            message = f" {other.symbol} zjadl guarane na ({self.position.x}, {self.position.y})"
            self.world.add_turn_summary_message(message)
            self.die()
            return True
        return False