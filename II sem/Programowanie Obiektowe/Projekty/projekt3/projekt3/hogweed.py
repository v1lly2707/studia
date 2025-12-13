from plant import Plant
from point import Point


class Hogweed(Plant):
    INITIAL_QUANTITY = 2
    STRENGTH = 0
    SYMBOL = 'P'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(world, strength=self.STRENGTH, symbol=self.SYMBOL, position=position)
        self.species = "Hogweed"

    def can_kill(self, other):
        return True

    def can_reproduce_this_turn(self):
        return False

    def action(self):
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if dx == 0 and dy == 0:
                    continue

                destination = Point(self.position.x + dx, self.position.y + dy)

                if self.world.is_within_board_boundaries(destination) and self.world.is_occupied(destination):
                    organism = self.world.get_organism_at(destination)
                    if organism is not None:
                        self.kill(organism)

    def collision(self, other):
        self.kill(other)
        return True