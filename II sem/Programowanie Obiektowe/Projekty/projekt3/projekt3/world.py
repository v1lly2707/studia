import random
from typing import Optional

from human import Human
from organism import Organism
from point import Point


class World:
    def __init__(self, game, size: int):
        self.game = game
        self.size = size
        self.organisms = [[None for _ in range(size)] for _ in range(size)]
        self.organisms_list = []
        self.turn_summary_messages = []
        self.human: Optional[Human] = None

    def take_turn(self):
        

        if not self.human.is_alive:
            print("Human died!")

        self.organisms_list.sort(key=lambda org: (org.initiative, org.age), reverse=True)

        for organism in self.organisms_list:
            organism.action()

    def spawn_organism(self, organism: Organism):
        position = self.get_random_position()

        if self.is_occupied(position):
            return

        organism.set_position(position)
        self.organisms_list.append(organism)
        self.organisms[position.x][position.y] = organism

    def is_within_board_boundaries(self, position: Point):
        return 0 <= position.x < self.size and 0 <= position.y < self.size

    def get_random_position(self):
        x = random.randint(0, self.size - 1)
        y = random.randint(0, self.size - 1)

        return Point(x, y)

    def get_random_neighbour(self, position: Point):
        neighbours = []
        for x in range(position.x - 1, position.x + 2):
            for y in range(position.y - 1, position.y + 2):
                neighbour = Point(x, y)
                if self.is_within_board_boundaries(neighbour) and neighbour != position:
                    neighbours.append(neighbour)

        return random.choice(neighbours)

    def has_free_space(self, position: Point):
        for x in range(position.x - 1, position.x + 2):
            for y in range(position.y - 1, position.y + 2):
                neighbour = Point(x, y)
                if self.is_within_board_boundaries(neighbour) and neighbour != position and self.is_empty(neighbour):
                    return True

        return False

    def get_random_free_space_around(self, position: Point):
        free_spaces = []
        for x in range(position.x - 1, position.x + 2):
            for y in range(position.y - 1, position.y + 2):
                neighbour = Point(x, y)
                if self.is_within_board_boundaries(neighbour) and neighbour != position and self.is_empty(neighbour):
                    free_spaces.append(neighbour)

        if len(free_spaces) == 0:
            return None

        return random.choice(free_spaces)

    def set_organism(self, organism: Organism, position: Point):
        self.organisms[position.x][position.y] = organism
        self.organisms_list.append(organism)

    def add_turn_summary_message(self, message: str):
        self.turn_summary_messages.append(message)

    def remove(self, organism: Organism):
        if organism in self.organisms_list:
            self.organisms_list.remove(organism)
        self.organisms[organism.position.x][organism.position.y] = None

    def clear_organisms(self):
        self.organisms = [[None for _ in range(self.size)] for _ in range(self.size)]
        self.organisms_list = []

    def is_occupied(self, position: Point):
        return self.organisms[position.x][position.y] is not None

    def is_empty(self, position: Point):
        return self.organisms[position.x][position.y] is None

    def get_organism(self, position: Point):
        return self.organisms[position.x][position.y]

    def get_organism_at(self, position: Point):
        return self.organisms[position.x][position.y]

    def get_nearest_hogweed(self, position: Point):
        nearest_hogweed = None
        nearest_distance = 1000000000
        for organism in self.organisms_list:
            if organism.symbol == 'P':
                distance = organism.position.distance(position)
                if distance < nearest_distance:
                    nearest_distance = distance
                    nearest_hogweed = organism

        return nearest_hogweed

    def remove_organism(self, organism: Organism):
        self.organisms_list.remove(organism)
        self.organisms[organism.position.x][organism.position.y] = None

    def move_organism(self, old_position: Point, new_position: Point):
        # print(f"Moving from ({old_position.x}, {old_position.y}) to ({new_position.x}, {new_position.y})")
        self.organisms[new_position.x][new_position.y] = self.organisms[old_position.x][old_position.y]
        self.organisms[old_position.x][old_position.y] = None

    def create_human(self, human: Human):
        self.human = human
        self.organisms_list.append(human)
        self.organisms[human.position.x][human.position.y] = human

    def get_human(self):
        return self.human

    def get_organisms_list(self):
        return self.organisms_list

    def get_size(self):
        return self.size

    def get_game(self):
        return self.game

    def get_turn_summary_messages(self):
        return self.turn_summary_messages

    def clear_turn_summary_messages(self):
        self.turn_summary_messages.clear()

    def handle_human_died(self):
        # self.game.game_over()
        print("Human died!")
       # exit(0)