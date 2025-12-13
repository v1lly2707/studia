import random
from prey_animal import PreyAnimal
from point import Point


class CyberSheep(PreyAnimal):
    INITIAL_QUANTITY = 2
    STRENGTH = 11
    INITIATIVE = 4
    SYMBOL = 'C'

    def __init__(self, world, position=Point(-1, -1)):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.species = "CyberSheep"

    def action(self):
        hogweed = self.world.get_nearest_hogweed(self.position)
        hogweed_location = hogweed.position if hogweed else None

        if hogweed_location is not None:
            direction = self.get_direction_to_hogweed(hogweed_location)

            if direction == "up":
                self.position.y -= 1
            elif direction == "down":
                self.position.y += 1
            elif direction == "left":
                self.position.x -= 1
            elif direction == "right":
                self.position.x += 1

            self.kill_hogweed_if_possible()
        else:
            super().action()

    def get_direction_to_hogweed(self, hogweed_location):
        dx = hogweed_location.x - self.position.x
        dy = hogweed_location.y - self.position.y

        if abs(dx) > abs(dy):
            return "right" if dx > 0 else "left"
        else:
            return "down" if dy > 0 else "up"

    def kill_hogweed_if_possible(self):
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if dx == 0 and dy == 0:
                    continue

                destination = Point(self.position.x + dx, self.position.y + dy)

                if self.world.is_within_board_boundaries(destination) and self.world.is_occupied(destination):
                    organism = self.world.get_organism_at(destination)
                    if organism is not None and organism.species == "Hogweed":
                        self.kill(organism)

    def reproduce(self, position):
        if random.randint(0, 2) == 0:
            free_space = self.world.get_random_free_space_around(position)
            if free_space:
                new_organism = CyberSheep(self.world, free_space)
                self.world.set_organism(new_organism, free_space)
                message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
                self.world.add_turn_summary_message(message)