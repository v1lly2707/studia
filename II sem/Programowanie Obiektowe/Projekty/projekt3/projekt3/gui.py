import tkinter as tk

import pygame

WIDTH = 800
HEIGHT = 800

ICON_WIDTH = 40
ICON_HEIGHT = 40

WHITE = (255, 255, 255)

FPS = 144

pygame.font.init()

WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))

pygame.display.set_caption("Symulacja wirtualnego swiata - Filip Swiniarski")


class Gui:
    def __init__(self):
        self.context_menu_active = False
        pygame.init()

        self.world_size = 0

        self.window = tk.Tk()
        self.window.title("Rozmiar swiata")

        self.window.geometry("300x100")

        self.size_label = tk.Label(self.window, text="Podaj wymiary:")
        self.size_label.pack()

        self.size_entry = tk.Entry(self.window)
        self.size_entry.pack()

        self.submit_button = tk.Button(self.window, text="Zatwierdz", command=self.submit)
        self.submit_button.pack()

    def submit(self):
        self.world_size = int(self.size_entry.get())
        print(f"Rozmiar swiata: {self.world_size}")
        self.window.destroy()

    def get_board_size(self):
        self.window.mainloop()
        return self.world_size

    def update_window(self, organisms_list):
        WINDOW.fill(WHITE)

        for i in range(0, self.world_size):
            for j in range(0, self.world_size):
                pygame.draw.rect(WINDOW, (0, 0, 0), (i * ICON_WIDTH, j * ICON_HEIGHT, ICON_WIDTH, ICON_HEIGHT), 1)

        font = pygame.font.Font(None, 36)  
    
        for organism in organisms_list:
            if organism.symbol == "H":
                text_surface = font.render("H", True, (0, 0, 0))
            elif organism.symbol == "W":
                text_surface = font.render("W", True, (0, 0, 0))
            elif organism.symbol == "S":
                text_surface = font.render("S", True, (0, 0, 0))
            elif organism.symbol == "C":
                text_surface = font.render("C", True, (0, 0, 0))
            elif organism.symbol == "A":
                text_surface = font.render("A", True, (0, 0, 0))
            elif organism.symbol == "T":
                text_surface = font.render("T", True, (0, 0, 0))
            elif organism.symbol == "F":
                text_surface = font.render("F", True, (0, 0, 0))
            elif organism.symbol == "G":
                text_surface = font.render("G", True, (0, 0, 0))
            elif organism.symbol == "U":
                text_surface = font.render("U", True, (0, 0, 0))
            elif organism.symbol == "D":
                text_surface = font.render("D", True, (0, 0, 0))
            elif organism.symbol == "N":
                text_surface = font.render("N", True, (0, 0, 0))
            elif organism.symbol == "P":
                text_surface = font.render("P", True, (0, 0, 0))
            else:
                continue  
    
            WINDOW.blit(text_surface, (organism.position.x * ICON_WIDTH, organism.position.y * ICON_HEIGHT))
    
            if self.context_menu_active:
                menu_font = pygame.font.Font(None, 24)  # You may need to choose a different font.
                menu_items = ["Wolf", "Sheep", "Antelope", "Tortoise", "CyberSheep", "Fox", "Grass", "Guarana", "Dandelion", "Nightshade", "Hogweed"]
                menu_height = len(menu_items) * menu_font.get_linesize()
                pygame.draw.rect(WINDOW, (200, 200, 200), (self.context_menu_position.left, self.context_menu_position.top, 150, menu_height))
                for i, item in enumerate(menu_items):
                    text_surface = menu_font.render(item, True, (0, 0, 0))
                    WINDOW.blit(text_surface, (self.context_menu_position.x, self.context_menu_position.y + i * menu_font.get_linesize()))
    
        pygame.display.update()

    def show_context_menu(self, position):
        self.context_menu_active = True
        self.context_menu_position = pygame.Rect(position[0], position[1], 0, 0)  # Convert tuple to Rect object