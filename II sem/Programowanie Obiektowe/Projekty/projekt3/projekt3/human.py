from enum import Enum
import random

from animal import Animal
from organism import Organism
from point import Point

from player_action import PlayerAction


class Human(Animal):
    STRENGTH = 5
    INITIATIVE = 4
    SYMBOL = 'H'

    def __init__(self, world, position: Point):
        super().__init__(self.STRENGTH, self.INITIATIVE, 0, self.SYMBOL, world, position)
        self.player_action = PlayerAction.NONE
        self.species = 'Human'
        self.is_alive = True

    def action(self):
        x = self.position.x
        y = self.position.y

        print(f"Obecna pozycja: ({x}, {y})")

        special_ability_duration = self.world.get_game().get_special_ability_duration()
        random_number = random.choice([0, 1])


        if self.player_action == PlayerAction.MOVE_UP:
            y -= 1
        elif self.player_action == PlayerAction.MOVE_DOWN:
            y += 1
        elif self.player_action == PlayerAction.MOVE_LEFT:
            x -= 1
        elif self.player_action == PlayerAction.MOVE_RIGHT:
            x += 1

        print(f"Pozycja po ruchu czlowieka: ({x}, {y})")

        destination = Point(x, y)

        if not self.world.is_within_board_boundaries(destination):
            return

        if self.world.is_occupied(destination):
            other = self.world.get_organism_at(destination)
            self.collision(other)

        # if self.can_move_to(destination):
        self.move(destination)

    def collision(self, other: Organism):
        if self.can_kill(other):
            self.kill(other)
            return True
        elif other.can_kill(self):
            other.kill(self)

        return False

    def die(self):
        self.is_alive = False
        self.world.handle_human_died()
        super().die()

    def reproduce(self, position: Point):
        pass

    def get_player_action(self):
        return self.player_action

    def set_player_action(self, player_action: PlayerAction):
        self.player_action = player_action