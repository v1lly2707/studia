import random
from prey_animal import PreyAnimal
from point import Point


class Antelope(PreyAnimal):
    INITIAL_QUANTITY = 2
    STRENGTH = 4
    INITIATIVE = 4
    SYMBOL = 'A'

    def __init__(self, world, position=None):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.species = "Antelope"

    def reproduce(self, position):
        free_space = self.world.get_random_free_space_around(position)

        if free_space is None:
            return

        new_organism = Antelope(self.world, free_space)
        self.world.set_organism(new_organism, free_space)

        message = f"Organism {self.symbol} reproduced at ({position.x}, {position.y})"
        self.world.add_turn_summary_message(message)

    def action(self):
        for i in range(2):
            destination = self.world.get_random_free_space_around(self.position)

            if destination is None:
                return

            if destination != self.position:
                self.move(destination)

    def collision(self, other):
        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)
            return True

        if other.can_be_killed_by(self):
            self.kill(other)
            return True

        elif other.can_kill(self):
            if random.randint(0, 1) == 0:
                free_space = self.world.get_random_free_space_around(self.position)

                if free_space != self.position:
                    self.move(free_space)

                message = f"Organism {self.symbol} escaped from fight at ({self.position.x}, {self.position.y})"
                self.world.add_turn_summary_message(message)
                return True

            return other.collision(self)

        return False

    def die(self):
        if random.randint(0, 1) == 0:
            free_space = self.world.get_random_free_space_around(self.position)

            if free_space == self.position:
                self.world.remove(self)

            self.move(free_space)

            message = f" {self.symbol} uciekla przed walka na: ({self.position.x}, {self.position.y})"
            self.world.add_turn_summary_message(message)

            return

        self.world.remove(self)