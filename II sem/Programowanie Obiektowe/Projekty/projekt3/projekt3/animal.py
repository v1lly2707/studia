from organism import Organism
import random


class Animal(Organism):
    def __init__(self, strength, initiative, age, symbol, world, position):
        super().__init__(strength, initiative, age, symbol, world, position)
        self.is_animal = True

    def action(self):
        destination = self.world.get_random_neighbour(self.position)

        if not self.world.is_within_board_boundaries(destination):
            return

        if self.can_move_to(destination):
            self.move(destination)
            return

        if self.world.is_occupied(destination):
            other = self.world.get_organism_at(destination)
            self.collision(other)

    def collision(self, other):
        if self.can_kill(other):
            self.kill(other)
            return True

        other.collision(self)

        if self.can_reproduce(other, self.position):
            self.reproduce(self.position)

        return False

    def move(self, destination):
        self.world.move_organism(self.position, destination)
        self.position = destination

    def kill(self, other):
        other.die()
        message = f" {other.symbol} zostal pokonany przez {self.symbol} na ({self.position.x}, {self.position.y})"
        self.world.add_turn_summary_message(message)

    def reproduce(self, position):
        message = f" {self.symbol} rozmnozyl sie na ({position.x}, {position.y})"
        self.world.add_turn_summary_message(message)

    def die(self):
        self.world.remove(self)

    def can_move_to(self, destination):
        can_move_to = self.world.is_empty(destination)

        if destination.x < 0 or destination.x >= self.world.size or destination.y < 0 or destination.y >= self.world.size:
            can_move_to = False

        return can_move_to

    def can_kill(self, other):
        if isinstance(self, type(other)):
            return False

        return other.can_be_killed_by(self)

    def can_be_killed_by(self, other):
        if isinstance(self, type(other)):
            return False

        return self.strength < other.strength

    def can_reproduce(self, other, position):
        if isinstance(self, type(other)) and self != other and self.world.has_free_space(position):
            return True

        return False