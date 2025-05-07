#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// KEY ARROW CONTROL
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// MAZE TEMPLATE
const int MAZE_X = 15;
const int MAZE_Y = 15;

struct Maze {
    char maze[MAZE_X][MAZE_Y];
    int pX; 
	int pY;

    Maze() : pX(1), pY(1) {
        char maze[MAZE_X][MAZE_Y] = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '#', '.', '#', '#', '.', '#', '.', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'E', '#', '#', '#', '#'},
        };

        for (int i = 0; i < MAZE_X; ++i) {
            for (int j = 0; j < MAZE_Y; ++j) {
                this->maze[i][j] = maze[i][j];
            }
        }
    }
};

void DisplayMaze(const Maze &maze, int playerX, int playerY) {
    for (int i = 0; i < MAZE_X; ++i) {
        for (int j = 0; j < MAZE_Y; ++j) {
            if (i == playerY && j == playerX) {
                printf("P "); // PLAYER
            } else {
                printf("%c ", maze.maze[i][j]);
            }
        }
        printf("\n");
    }
}

void PlayerMovementEasy(int &pX, int &pY, const Maze &maze) {
    int move = getch();

    switch (move) {
        case KEY_UP:
            if (pY - 1 >= 0) {
                if (maze.maze[pY - 1][pX] != '#') {
                    pY--;
                }
            }
            break;
        case KEY_DOWN:
            if (pY + 1 < MAZE_X) {
                if (maze.maze[pY + 1][pX] != '#') {
                    pY++;
                }
            }
            break;
        case KEY_RIGHT:
            if (pX + 1 < MAZE_Y) {
                if (maze.maze[pY][pX + 1] != '#') {
                    pX++;
                }
            }
            break;
        case KEY_LEFT:
            if (pX - 1 >= 0) {
                if (maze.maze[pY][pX - 1] != '#') {
                    pX--;
                }
            }
            break;
    }
};

struct MazeM {
    char mazeM[MAZE_X][MAZE_Y];
    int pX; 
	int pY;

    MazeM() : pX(1), pY(1) {
        char mazeM[MAZE_X][MAZE_Y] = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '#', '.', '#', '#', '.', '#', '.', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#'},
            {'#', '#', '#', 'E', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        };

        for (int i = 0; i < MAZE_X; ++i) {
            for (int j = 0; j < MAZE_Y; ++j) {
                this->mazeM[i][j] = mazeM[i][j];
            }
        }
    }
};

void DisplayMazeM(const MazeM &mazeM , int playerX, int playerY) {
    for (int i = 0; i < MAZE_X; ++i) {
        for (int j = 0; j < MAZE_Y; ++j) {
            if (i == playerY && j == playerX) {
                printf("P "); // PLAYER
            } else {
                printf("%c ", mazeM.mazeM[i][j]);
            }
        }
        printf("\n");
    }
}

void PlayerMovementMedium(int &pX, int &pY, const MazeM &mazeM) {
    int move = getch();

    switch (move) {
        case KEY_UP:
            if (pY - 1 >= 0) {
                if (mazeM.mazeM[pY - 1][pX] != '#') {
                    pY--;
                }
            }
            break;
        case KEY_DOWN:
            if (pY + 1 < MAZE_X) {
                if (mazeM.mazeM[pY + 1][pX] != '#') {
                    pY++;
                }
            }
            break;
        case KEY_RIGHT:
            if (pX + 1 < MAZE_Y) {
                if (mazeM.mazeM[pY][pX + 1] != '#') {
                    pX++;
                }
            }
            break;
        case KEY_LEFT:
            if (pX - 1 >= 0) {
                if (mazeM.mazeM[pY][pX - 1] != '#') {
                    pX--;
                }
            }
            break;
    }
};
struct MazeH {
    char mazeH[MAZE_X][MAZE_Y];
    int pX;
    int pY;

    MazeH() : pX(1), pY(1) {
        char mazeH[MAZE_X][MAZE_Y] = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '#', '.', '#', '#', '.', '#', '.', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '#', '#', '#'},
            {'#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '.', '.', '#', '.', '.', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#', '#'},
            {'#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'E', '#', '#', '#', '#'},
        };

        for (int i = 0; i < MAZE_X; ++i) {
            for (int j = 0; j < MAZE_Y; ++j) {
                this->mazeH[i][j] = mazeH[i][j];
            }
        }
    }
};

void DisplayMazeH(const MazeH &mazeH, int playerX, int playerY) {
    for (int i = 0; i < MAZE_X; ++i) {
        for (int j = 0; j < MAZE_Y; ++j) {
            if (i == playerY && j == playerX) {
                printf("P "); // PLAYER
            } else {
                printf("%c ", mazeH.mazeH[i][j]);
            }
        }
        printf("\n");
    }
}

void PlayerMovementHard(int &pX, int &pY, const MazeH &mazeH) {
    int move = getch();

    switch (move) {
        case KEY_UP:
            if (pY - 1 >= 0) {
                if (mazeH.mazeH[pY - 1][pX] != '#') {
                    pY--;
                }
            }
            break;
        case KEY_DOWN:
            if (pY + 1 < MAZE_X) {
                if (mazeH.mazeH[pY + 1][pX] != '#') {
                    pY++;
                }
            }
            break;
        case KEY_RIGHT:
            if (pX + 1 < MAZE_Y) {
                if (mazeH.mazeH[pY][pX + 1] != '#') {
                    pX++;
                }
            }
            break;
        case KEY_LEFT:
            if (pX - 1 >= 0) {
                if (mazeH.mazeH[pY][pX - 1] != '#') {
                    pX--;
                }
            }
            break;
    }
};

int main() {
    int option;

    printf("===============================\n");
    printf("Main Menu:\n");
    printf("1. Start\n");
    printf("2. Exit\n");
    printf("Please Enter your Choice (1,2): ");

    scanf("%d", &option);
    
        
    int playerX, playerY;
    
	Maze mazeEasy; 
	MazeM mazeM; 
	MazeH mazeH; 

    switch (option) {
        case 1:
            printf("Choose Your Maze Level:\n");
            printf("1. EASY\n");
            printf("2. MEDIUM\n");
            printf("3. HARD\n");
            printf("Please Enter Your Choice (1,2,3): ");

            int level;
            scanf("%d", &level);

            if (level == 1) {
                printf("Activating The Game......");
            
            playerX = mazeEasy.pX;
            playerY = mazeEasy.pY;

            // Loop for player movement in the selected maze
            while (true) {
                system("CLS"); // Clear console screen
                DisplayMaze(mazeEasy, playerX, playerY);

                // Get input and move the player
                PlayerMovementEasy(playerX, playerY, mazeEasy);

                // Check if the player reached the exit
                if (playerX == 10 && playerY == 13){
                    printf("Congratulations! You reached the exit!\n");
                    break;
                }
            }
        }
            
			if (level == 2) {
            printf("Activating The Game......");
            
           
            
            playerX = mazeM.pX;
            playerY = mazeM.pY;
            
            // Loop for player movement in the selected maze
            while (true) {
                system("CLS"); // Clear console screen
                DisplayMazeM(mazeM, playerX, playerY);

                // Get input and move the player
                PlayerMovementMedium(playerX, playerY, mazeM);

                // Check if the player reached the exit
                if (playerX == 10 && playerY == 13) {
                    printf("Congratulations! You reached the exit!\n");
                    break;
                }
           }
    }
            if (level == 3) {
            printf("Activating The Game......");
            
           
            
            playerX = mazeH.pX;
            playerY = mazeH.pY;

            // Loop for player movement in the selected maze
            while (true) {
                system("CLS"); // Clear console screen
                DisplayMazeH(mazeH, playerX, playerY);

                // Get input and move the player
                PlayerMovementHard(playerX, playerY, mazeH);

                // Check if the player reached the exit
                if (playerX == 10 && playerY == 13) {
                    printf("Congratulations! You reached the exit!\n");
                    break;
                
                 
                   }   
				}
        }
            break;

        case 2:
            printf("Exiting The Game.........");
            break;

        default:
            
            break;

}
    getch();
    return 0;
 }
  

