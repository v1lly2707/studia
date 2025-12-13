from typing import Union, List
from enum import Enum
import numpy as np

from cyber_sheep import CyberSheep
from dandelion import Dandelion
from grass import Grass
from guarana import Guarana
from hogweed import Hogweed
from nightshade import Nightshade
from world import World

from antelope import Antelope
from fox import Fox
from human import Human
from sheep import Sheep
from tortoise import Tortoise
from wolf import Wolf

from direction import Direction
from point import Point
from player_action import PlayerAction


class Game:
    SPECIAL_ABILITY_COOLDOWN = 5

    def __init__(self, gui):
        self.gui = gui
        self.world = None
        self.size = 0
        self.turn = 0
        self.special_ability_cooldown = self.SPECIAL_ABILITY_COOLDOWN
        self.special_ability_duration = 0

        self.initialize_game()

    def initialize_game(self):
        self.size = self.gui.get_board_size()

        self.world = World(self, self.size)
        self.turn = 0

        self.special_ability_cooldown = self.SPECIAL_ABILITY_COOLDOWN
        self.special_ability_duration = 0

        self.spawn_initial_organisms()

    def spawn_initial_organisms(self):
        self.create_human()

        self.spawn_wolves()
        self.spawn_foxes()
        self.spawn_sheep()
        self.spawn_cyber_sheep()
        self.spawn_antelopes()
        self.spawn_tortoises()

        self.spawn_grass()
        self.spawn_dandelions()
        self.spawn_guarana()
        self.spawn_nightshade()
        self.spawn_hogweed()

    def create_human(self):
        position = Point(0, 0)

        human = Human(self.world, position)
        self.world.create_human(human)

    def spawn_wolves(self):
        for _ in range(Wolf.INITIAL_QUANTITY):
            wolf = Wolf(self.world)
            self.world.spawn_organism(wolf)

    def spawn_foxes(self):
        for _ in range(Fox.INITIAL_QUANTITY):
            fox = Fox(self.world)
            self.world.spawn_organism(fox)

    def spawn_sheep(self):
        for _ in range(Sheep.INITIAL_QUANTITY):
            sheep = Sheep(self.world)
            self.world.spawn_organism(sheep)

    def spawn_cyber_sheep(self):
        for _ in range(CyberSheep.INITIAL_QUANTITY):
            cyber_sheep = CyberSheep(self.world)
            self.world.spawn_organism(cyber_sheep)

    def spawn_antelopes(self):
        for _ in range(Antelope.INITIAL_QUANTITY):
            antelope = Antelope(self.world)
            self.world.spawn_organism(antelope)

    def spawn_tortoises(self):
        for _ in range(Tortoise.INITIAL_QUANTITY):
            tortoise = Tortoise(self.world)
            self.world.spawn_organism(tortoise)

    def spawn_grass(self):
        for _ in range(Grass.INITIAL_QUANTITY):
            grass = Grass(self.world)
            self.world.spawn_organism(grass)

    def spawn_dandelions(self):
        for _ in range(Dandelion.INITIAL_QUANTITY):
            dandelion = Dandelion(self.world)
            self.world.spawn_organism(dandelion)

    def spawn_guarana(self):
        for _ in range(Guarana.INITIAL_QUANTITY):
            guarana = Guarana(self.world)
            self.world.spawn_organism(guarana)

    def spawn_nightshade(self):
        for _ in range(Nightshade.INITIAL_QUANTITY):
            nightshade = Nightshade(self.world)
            self.world.spawn_organism(nightshade)

    def spawn_hogweed(self):
        for _ in range(Hogweed.INITIAL_QUANTITY):
            hogweed = Hogweed(self.world)
            self.world.spawn_organism(hogweed)

    def move_player(self, direction: Direction):
        human = self.world.get_human()

        if direction == Direction.UP:
            human.set_player_action(PlayerAction.MOVE_UP)
        elif direction == Direction.DOWN:
            human.set_player_action(PlayerAction.MOVE_DOWN)
        elif direction == Direction.LEFT:
            human.set_player_action(PlayerAction.MOVE_LEFT)
        elif direction == Direction.RIGHT:
            human.set_player_action(PlayerAction.MOVE_RIGHT)

        self.world.take_turn()
        self.increment_organisms_age()
        self.turn += 1

        if self.special_ability_cooldown > 0:
            self.special_ability_cooldown -= 1

        if self.special_ability_duration > 0:
            self.special_ability_duration -= 1
            if self.special_ability_duration == 0:
                self.special_ability_cooldown = self.SPECIAL_ABILITY_COOLDOWN

    def increment_organisms_age(self):
        for organism in self.world.get_organisms_list():
            organism.age = organism.age + 1

    def activate_special_ability(self):
        if self.special_ability_cooldown > 0:
            print("Special ability is on cooldown!")
            return

        self.special_ability_duration = 5
        self.special_ability_cooldown = 0

    def get_special_ability_duration(self):
        return self.special_ability_duration

    def get_special_ability_cooldown(self):
        return self.special_ability_cooldown

    def get_organisms_list(self):
        return self.world.get_organisms_list()

    def save_to_file(self):
        try:
            with open('save.txt', 'w') as file:
                file.write(f"{self.turn}\n")
                file.write(f"{self.size} {len(self.world.organisms_list)}\n")
                file.write(f"{self.special_ability_cooldown} {self.special_ability_duration}\n")
                file.write(f"{self.world.human.position.x} {self.world.human.position.y}\n")

                for organism in self.world.organisms_list:
                    file.write(f"{organism.position.x} {organism.position.y} "
                               f"{organism.strength} {organism.age} {organism.species}\n")

        except FileNotFoundError as e:
            print(f"File error: {e}")

    def load_from_file(self):
        try:
            with open('save.txt', 'r') as file:
                self.world.clear_organisms()

                lines = file.readlines()

                self.turn = int(lines[0])
                self.size = int(lines[1].split()[0])
                organisms_quantity = int(lines[1].split()[1])

                self.special_ability_cooldown = int(lines[2].split()[0])
                self.special_ability_duration = int(lines[2].split()[1])

                player_x = int(lines[3].split()[0])
                player_y = int(lines[3].split()[1])

                self.world.human.position = Point(player_x, player_y)

                for i in range(organisms_quantity):
                    x = int(lines[4 + i].split()[0])
                    y = int(lines[4 + i].split()[1])
                    strength = int(lines[4 + i].split()[2])
                    age = int(lines[4 + i].split()[3])
                    species_string = lines[4 + i].split()[4]

                    if species_string == "Human":
                        organism = Human(self.world, Point(x, y))
                        self.world.human = organism
                    elif species_string == "Wolf":
                        organism = Wolf(self.world, Point(x, y))
                    elif species_string == "Sheep":
                        organism = Sheep(self.world, Point(x, y))
                    elif species_string == "CyberSheep":
                        organism = CyberSheep(self.world, Point(x, y))
                    elif species_string == "Fox":
                        organism = Fox(self.world, Point(x, y))
                    elif species_string == "Tortoise":
                        organism = Tortoise(self.world, Point(x, y))
                    elif species_string == "Antelope":
                        organism = Antelope(self.world, Point(x, y))
                    elif species_string == "Grass":
                        organism = Grass(self.world, Point(x, y))
                    elif species_string == "Dandelion":
                        organism = Dandelion(self.world, Point(x, y))
                    elif species_string == "Guarana":
                        organism = Guarana(self.world, Point(x, y))
                    elif species_string == "Nightshade":
                        organism = Nightshade(self.world, Point(x, y))
                    elif species_string == "Hogweed":
                        organism = Hogweed(self.world, Point(x, y))

                    organism.strength = strength
                    organism.age = age

                    self.world.set_organism(organism, Point(x, y))

        except FileNotFoundError:
            print("Blad: nie mozna otworzyc pliku")

    def spawn_from_menu(self, menu_index, position: Point):
        menu_items = ["Wolf", "Sheep", "Antelope", "Tortoise", "CyberSheep", "Fox", "Grass", "Guarana", "Dandelion", "Nightshade", "Hogweed"]
        menu_item = menu_items[menu_index]

        if menu_item == "Wolf":
            organism = Wolf(self.world)
        elif menu_item == "Sheep":
            organism = Sheep(self.world)
        elif menu_item == "Antelope":
            organism = Antelope(self.world)
        elif menu_item == "Tortoise":
            organism = Tortoise(self.world)
        elif menu_item == "CyberSheep":
            organism = CyberSheep(self.world)
        elif menu_item == "Fox":
            organism = Fox(self.world)
        elif menu_item == "Grass":
            organism = Grass(self.world)
        elif menu_item == "Guarana":
            organism = Guarana(self.world)
        elif menu_item == "Dandelion":
            organism = Dandelion(self.world)
        elif menu_item == "Nightshade":
            organism = Nightshade(self.world)
        elif menu_item == "Hogweed":
            organism = Hogweed(self.world)

        position.x //= 40
        position.y //= 40

        organism.set_position(position)
        print(position.x, position.y)
        self.world.set_organism(organism, position)
