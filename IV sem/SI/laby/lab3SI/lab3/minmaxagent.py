from connect4 import Connect4
import copy

class MinMaxAgent:
    def __init__(self, token: str, depth: int = 2):
        self.my_token = token
        self.depth = depth

    def decide(self, connect4: Connect4):
        best_v = -float('inf')
        best_m = None

        for n_column in connect4.possible_drops():
            new_connect4 = copy.deepcopy(connect4)
            new_connect4.drop_token(n_column)
            local_v = self.minmax(new_connect4, self.depth - 1, False)
            if local_v > best_v:
                best_v = local_v
                best_m = n_column

        return best_m
    
    def minmax(self, connect4: Connect4, depth: int, maximizing: bool):
        if connect4.game_over:
            if connect4.wins == self.my_token:
                return 1
            elif connect4.wins is None:
                return 0
            else:
                return -1
            
        if depth == 0:
            return self.heuristic(connect4)
        
        if maximizing:
            best_v = -float('inf')
            for n_column in connect4.possible_drops():
                new_connect4 = copy.deepcopy(connect4)
                new_connect4.drop_token(n_column)
                best_v = max(best_v, self.minmax(new_connect4, depth - 1, not maximizing))
            return best_v
        else:
            best_v = float('inf')
            for n_column in connect4.possible_drops():
                new_connect4 = copy.deepcopy(connect4)
                new_connect4.drop_token(n_column)
                best_v = min(best_v, self.minmax(new_connect4, depth - 1, not maximizing))

            return best_v
    
    def heuristic(self, connect4: Connect4):
        total = 0
        pts = 0
        weights = [0, 5, 15, 50]
        for four in connect4.iter_fours():
            total += 1
            count1 = four.count(self.my_token)
            count2 = four.count('_')
            count3 = 4 - count1 - count2

            if count3 != 0:
                continue

            pts += weights[count1]

        return pts / (total * weights[-1])