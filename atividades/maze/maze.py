from collections import deque
import pygame
import numpy as np
import csv
import random
import threading

class Maze:

    '''
    O labirinto é representado por uma matriz binária em arquivo. Onde
    o valor 0 representa um quadrado da parede do labirinto, e o valor 1 representa 
    um quadrado do corredor do labirinto.
    
    O labirinto em memória é representado por uma matriz inteira, indicando para cada
    quadrado se o mesmo é uma parede, um corredor, o prêmio ou o jogador.
    '''
    
    WALL = 0
    HALL = 1
    PLAYER = 2
    PRIZE = 3
    
    def __init__(self):
        '''
        Inicializa a matriz de inteiros M que representa a lógica do labirinto

        '''
        self.M = None #matriz que representa o labirinto
        pygame.init()

    
    def load_from_csv(self, file_path : str):
        '''
        Função para carregar a matriz de um arquivo CSV  

        Parameters
        ----------
        file_path : str
            Nome do arquivo contendo a matriz binária que descreve o labirinto.

        '''
        with open(file_path, newline='') as csvfile:
            reader = csv.reader(csvfile)
            self.M = np.array([list(map(int, row)) for row in reader])
            
    def init_player(self):
        '''
        Coloca o prêmio (quadrado amarelo) e o jogador (quadrado azul)
        em posições aleatórias no corredor do labirinto.

        '''
        #escolhendo a posição aleatória do player em um corredor
        while True:
            posx = random.randint(2, 39)
            posy = random.randint(2, 39)
            if self.M[posx, posy] == Maze.HALL:
                self.init_pos_player = (posx, posy)
                break
        
        #escolhendo a posição aleatória do premio em um corredor
        while True:
            posx = random.randint(2, 39)
            posy = random.randint(2, 39)
            if self.M[posx, posy] == Maze.HALL:
                self.M[posx, posy] = Maze.PRIZE
                break

    def find_prize(self, pos : (int, int)) -> bool:
        '''
        O tabuleiro é dividio 
        Recebe uma posição (x,y) do tabuleiro e indica se o prêmio está contido
        naquela posição.

        Parameters
        ----------
        pos : (int, int)
            Posição do quadrado na matriz do labirinto que se deseja testar se 
            foi encontrado prêmio

        Returns
        -------
        bool
            Retorna True se o quadrado do labirinto na posição 'pos' contiver o prêmio, 
            retorna False em caso contrário.

        '''
        if self.M[pos[0], pos[1]] == Maze.PRIZE:
            return True
        else:
            return False
        
    def is_free(self, pos : (int, int)) -> bool:
        '''
        Indica se a posição fornecida está livre para o jogador acessar, ou seja, 
        se for corredor ou prêmio.

        Parameters
        ----------
        pos : (int, int)
            Posição do quadrado na matriz do labirinto que se deseja testar se 
            está livre.


        Returns
        -------
        bool
            Retorna True.

        '''
        if self.M[pos[0], pos[1]] in [Maze.HALL, Maze.PRIZE]:
            return True
        else:
            return False
        
        
    def mov_player(self, pos : (int, int)) -> None:
        '''
        Move o jogador para uma nova posição do labirinto desde que ela seja uma
        posição corredor na matriz M.

        Parameters
        ----------
        pos : (int, int)
            Nova posição (x,y) no labiritno em que o jogador será movido.

        '''
        if self.M[pos[0], pos[1]] == Maze.HALL:
            self.M[pos[0], pos[1]] = Maze.PLAYER
        

    def get_init_pos_player(self) -> (int, int):
        '''
        Indica a posição inicial do jogador dentro do labirinto que foi gerada 
        de forma aleatória.

        Returns
        -------
        (int, int)
            Posição inicial (x,y) do jogador no labirinto.

        '''
        return self.init_pos_player

    def backtracking(self):
        # pilha
        stack = deque()
        
        # get posição inicial do jogador
        start_pos = self.get_init_pos_player()
        
        # init conjunto para guardar posições visitadas
        visited = set()
        
        # add posição inicial na pilha
        stack.append(start_pos)
        
        # cima, direita, baixo, esquerda
        directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        
        # enquanto a pilha não estiver vazia
        while stack:
            # delete uma posição da pilha
            current_pos = stack.pop()
            
            # se já foi visitada, continuar
            if current_pos in visited:
                continue
            
            # marcar como visitada
            visited.add(current_pos)
            
            # verificar se encontrou o prêmio
            if self.find_prize(current_pos):
                print("prêmio encontrado na posição:", current_pos)
                return True
            
            # mov o jogador para esta posição
            if current_pos != start_pos:  # não mudar a posição inicial
                self.mov_player(current_pos)                
                pygame.time.delay(100)
            
            # verificar as posições adjacentes
            for dx, dy in directions:
                next_pos = (current_pos[0] + dx, current_pos[1] + dy)
                
                # se a próxima posição está livre e não foi visitada, add na pilha
                if (0 <= next_pos[0] < self.M.shape[0] and 
                    0 <= next_pos[1] < self.M.shape[1] and 
                    self.is_free(next_pos) and 
                    next_pos not in visited):
                    stack.append(next_pos)
        
        print("não foi possível resolver o labirinto")
        return False
            
    def run(self):
        '''
        Thread responsável pela atualização da visualização do labirinto.

        '''
        th = threading.Thread(target=self._display)
        th.start()
    
    def _display(self, cell_size=15):
        '''
        Método privado para exibir o labirinto na tela mapeando os valores lógicos
        atribuídos em cada casa da matriz M, seguindo as constantes definidas na classe.

        
        '''
        rows, cols = self.M.shape
        width, height = cols * cell_size, rows * cell_size
        screen = pygame.display.set_mode((width, height))
        pygame.display.set_caption("Labirinto")
    
        # Cores
        BLACK = (0, 0, 0)
        GRAY = (192, 192, 192)
        BLUE = (0, 0, 255)
        GOLD = (255, 215, 0)
    
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
    
            screen.fill(BLACK)
    
            # Desenhar o labirinto
            for y in range(rows):
                for x in range(cols):
                    if self.M[y, x] ==  Maze.WALL:
                        color = BLACK
                    elif self.M[y, x] == Maze.HALL:
                        color = GRAY
                    elif self.M[y, x] == Maze.PLAYER:
                        color = BLUE
                    elif self.M[y, x] == Maze.PRIZE:
                        color = GOLD
                       
                    pygame.draw.rect(screen, color, (x * cell_size, y * cell_size, cell_size, cell_size))
    
            pygame.display.flip()