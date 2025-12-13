from connect4 import Connect4
import copy


class AlphaBetaAgent:
    def __init__(self, token: str, depth: int = 2):
        self.my_token = token
        self.depth = depth

    def decide(self, connect4: Connect4):
        alfa = float('-inf')
        best_v = -float('inf')
        best_m = None

        for n_column in connect4.possible_drops():
            new_connect4 = copy.deepcopy(connect4)
            new_connect4.drop_token(n_column)
            local_v = self.alphabeta(new_connect4, self.depth - 1, False, alfa)
            if local_v > best_v:
                best_v = local_v
                best_m = n_column

        return best_m
    
    def alphabeta(self, connect4: Connect4, depth: int, maximizing: bool, alpha = -float('inf'), beta = float('inf')):
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
                best_v = max(best_v, self.alphabeta(new_connect4, depth - 1, not maximizing, alpha, beta))
                alpha = max(alpha, best_v)
                if beta <= best_v:
                    break
            return best_v
        else:
            best_v = float('inf')
            for n_column in connect4.possible_drops():
                new_connect4 = copy.deepcopy(connect4)
                new_connect4.drop_token(n_column)
                best_v = min(best_v, self.alphabeta(new_connect4, depth - 1, not maximizing, alpha, beta))
                beta = min(beta, best_v)
                if alpha >= best_v:
                    break

            return best_v
        
    def heuristic(self, connect4: Connect4):
        total = 0
        pts = 0
        weights = [0, 5, 15, 50]
        for four in connect4.iter_fours():
            total += 1
            count1 = four.count(self.my_token) #gracz
            count2 = four.count('_') #puste
            count3 = 4 - count1 - count2 #przeciwnik

            if count3 != 0:
                continue

            pts += weights[count1]

        return pts / (total * weights[-1])
        

