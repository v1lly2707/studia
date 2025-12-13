from abc import ABC, abstractmethod

from point import Point
from species import Species


class Organism(ABC):
    def __init__(self, strength, initiative, age, symbol, world, position, is_animal=True):
        self.strength = strength
        self.initiative = initiative
        self.age = age
        self.symbol = symbol
        self.is_animal = is_animal
        self.position = position
        self.world = world
        self.species = Species.ORGANISM
        self.is_alive = True

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self, other):
        pass

    @abstractmethod
    def reproduce(self, position):
        pass

    @abstractmethod
    def die(self):
        pass

    @abstractmethod
    def kill(self, other):
        pass

    @abstractmethod
    def can_kill(self, other):
        pass

    @abstractmethod
    def can_be_killed_by(self, other):
        pass

    def print_info(self):
        print(f"Symbol: {self.symbol}")
        print(f"Sila: {self.strength}")
        print(f"Inicjatywa: {self.initiative}")
        print(f"Wiek: {self.age}")
        print(f"Pozycja: ({self.position.x}, {self.position.y})")

    def print_short_info(self):
        print(f"{self.symbol} ({self.position.x}, {self.position.y})")

    @property
    def strength(self):
        return self._strength

    @strength.setter
    def strength(self, strength):
        self._strength = strength

    @property
    def initiative(self):
        return self._initiative

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, age):
        self._age = age

    @property
    def symbol(self):
        return self._symbol

    @property
    def is_animal(self):
        return self._is_animal

    @is_animal.setter
    def is_animal(self, is_animal):
        self._is_animal = is_animal

    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, position):
        self._position = position

    @property
    def is_alive(self):
        return self._is_alive

    @is_alive.setter
    def is_alive(self, is_alive):
        self._is_alive = is_alive

    def get_x(self):
        return self.position.x

    def get_y(self):
        return self.position.y

    @property
    def species(self):
        return self._species

    def set_position(self, x, y):
        self.position = Point(x, y)

    # set position for Point
    def set_position(self, position):
        self.position = position

    @initiative.setter
    def initiative(self, value):
        self._initiative = value

    @symbol.setter
    def symbol(self, value):
        self._symbol = value

    @species.setter
    def species(self, value):
        self._species = value