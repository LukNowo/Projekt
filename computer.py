import pygame
import math
import random


board = [ ['', '', '' ],
          ['', '', '' ],
          ['', '', '' ] ] 
empty_spaces = 9 

#kontrola vítěze po každém kole
def check_winner(letter, board):
        if(board[0][0] == board[0][1] == board[0][1] == board[0][2]  != ''): 
            return letter
        elif(board[1][0] == board[1][1] == board[1][2] != ''): 
            return letter
        elif(board[2][0] == board[2][1] == board[2][2] != ''): 
            return letter
        elif(board[0][0] == board[1][0] == board[2][0] != ''):
            return letter
        elif(board[0][1] == board[1][1] == board[2][1] != ''): 
            return letter
        elif(board[0][2] == board[1][2] == board[2][2] != ''):
            return letter
        elif(board[0][0] == board[1][1] == board[2][2] != ''): 
            return letter
        elif(board[0][2] == board[1][1] == board[2][0] != ''): 
            return letter
        elif(empty_spaces == 0):
            return "REMIZA"
        else:
            return ''


class Smart_Computer:

    def __init__(self, X_O, screenDim): 
        self.letter = X_O
        self.present = self.letter
        if(self.letter == 'x'):
            self.opposition = 'o'
        else:
            self.opposition = 'x'
        self.screen = screenDim
        self.first_turn = True 

    #Počítač si vypočítává nejvhodnější pozici umístění svého políčka
    def minimax(self, game_board, isMaximizing: bool): 
        global empty_spaces 
        result = check_winner(self.present, game_board) 
        if(result != ''):
            if(result == self.letter):
                return 1*(empty_spaces+1)
            elif(result == self.opposition): 
                return -1*(empty_spaces+1)
            else:
                return 0
        if(isMaximizing):
            best_score = -math.inf
        else:
            best_score = math.inf

        for i in range(0, 3):
            for j in range(0, 3):
                if(game_board[i][j] == ''):
                    if(isMaximizing):
                        self.present = self.letter
                    else:
                        self.present = self.opposition
                    game_board[i][j] = self.present
                    empty_spaces = empty_spaces-1
                    if(isMaximizing): 
                        check_score = self.minimax(game_board, False)
                        if(check_score>best_score):
                            best_score = check_score
                    else:
                        check_score = self.minimax(game_board, True)
                        if(check_score<best_score):
                            best_score = check_score
                    game_board[i][j] = ''
                    empty_spaces = empty_spaces+1  
        return best_score
        
    def best_move(self, game_board):
        self.present = self.letter
        global empty_spaces
        turn = None
        if self.first_turn != True:
            best_score = -math.inf
            for i in range(0, 3):
                for j in range(0, 3):
                    if(game_board[i][j]==''):
                        self.present = self.letter
                        game_board[i][j] = self.present    
                        empty_spaces = empty_spaces-1
                        score = self.minimax(game_board, False) 
                        game_board[i][j] = ''
                        empty_spaces = empty_spaces+1
                        if(score>best_score):
                            best_score = score 
                            turn = [i, j]
            self.present = self.letter 
            game_board[turn[0]][turn[1]] = self.present  
      
        else:
            assigned = False
            while(assigned == False):
                i = random.randrange(0, 3)
                j = random.randrange(0, 3)
                if game_board[i][j] == '':
                    game_board[i][j] = self.present
                    turn = [i, j]
                    assigned = True
            self.first_turn = False
        return turn