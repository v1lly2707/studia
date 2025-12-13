import pygame
from game import Game
from gui import Gui
from direction import Direction
from point import Point

FPS = 144


def main():
    gui = Gui()
    game = Game(gui)

    clock = pygame.time.Clock()

    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    print("Ruch w lewo")
                    game.move_player(Direction.LEFT)
                elif event.key == pygame.K_RIGHT:
                    print("Ruch w prawo")
                    game.move_player(Direction.RIGHT)
                elif event.key == pygame.K_UP:
                    print("Ruch w gore")
                    game.move_player(Direction.UP)
                elif event.key == pygame.K_DOWN:
                    print("Ruch w dol")
                    game.move_player(Direction.DOWN)
                
                elif event.key == pygame.K_k:
                    print("Zapis do pliku")
                    game.save_to_file()
                elif event.key == pygame.K_l:
                    print("Wczytywanie z pliku")
                    game.load_from_file()
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 3:
                #print("right mouse button clicked")
                right_click_mouse_position = pygame.mouse.get_pos()
                gui.context_menu_position = pygame.Rect(right_click_mouse_position[0], right_click_mouse_position[1], 0, 0)  # Convert tuple to Rect object
                gui.context_menu_active = True
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                #print("left mouse button clicked")
                if gui.context_menu_active:
                    mouse_position_tuple = pygame.mouse.get_pos()
                    # mouse_position_tuple = right_click_mouse_position
                    menu_font = pygame.font.Font(None, 24)
                    menu_item_index = (mouse_position_tuple[1] - gui.context_menu_position[1]) // menu_font.get_linesize()
                    # mouse_position_tuple = pygame.mouse.get_pos()
                    mouse_position = Point(right_click_mouse_position[0], right_click_mouse_position[1])
                    # game.spawn_from_menu(menu_item_index, mouse_position)
                    if 0 <= menu_item_index < 12:
                        game.spawn_from_menu(menu_item_index, mouse_position)
                        
                    gui.context_menu_active = False

        organisms_list = game.get_organisms_list()
        gui.update_window(organisms_list)
        clock.tick(FPS)

    pygame.quit()


if __name__ == "__main__":
    main()