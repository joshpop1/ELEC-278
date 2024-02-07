// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove "#include "colours.h".

// Make sure to include all relevant libraries
#include <stdio.h>
#include "colours.h"
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <time.h>

// You don't need to use these, but they help make your code look more organized
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

// Below are the required functions for this program, but you will need to create your own as well.
// Make sure to specify the required parameters, if any.

// Declaring all functions
void readMap();
void printMap();
int winCheck();
void movePac();
int loseCheck();
int isWall(int x, int y, char direc);
void moveGhost(int ghostX, int ghostY);

// Declaring all variables
int pacX = 0;
int pacY = 0;
int ghost1X;
int ghost1Y;
int ghost2X;
int ghost2Y;
int ghostNum = 0;
char** map;

// Main function calls other functions
int main() {
    int win = 0;
    int lose = 0;
    // Calling the "readMap" function that reads player
    readMap();
    while(win == 0) {
        // While the player has not one, the various functions can be called
        printMap();
        movePac();
        moveGhost(ghost1X, ghost1Y);
        moveGhost(ghost2X, ghost2Y);

        // Function that checks whether the player has won, and prints a message if true and exits the game
        win = winCheck();
        if(win == 1) {
            printMap();
            printf("Congratulations! You win! Press any key to exit the game");
            getch();
            exit(0);
        }
        // ction that checks whether the player has lost, and prints a message if true and exits the game
        if(loseCheck() == 1) {
            printMap();
            printf("Sorry, you lose. Press any key to exit the game");
            getch();
            exit(0);
        }
    }
}

// Function that moves Pacman based on user inputs
void movePac(){
    char move = getch();
    // If the user input is the W key, Pacman will move up
    if (move == UP && !isWall(pacX, pacY, UP)) {
        map[pacX - 1][pacY] = PACMAN;
        map[pacX][pacY] = EMPTY;
        pacX--;
    // If the user input is the S key, Pacman will move down
    } else if (move == DOWN && !isWall(pacX, pacY, DOWN)) {
        map[pacX + 1][pacY] = PACMAN;
        map[pacX][pacY] = EMPTY;
        pacX++;
    // If the user input is the A key, Pacman will move left
    } else if (move == LEFT && !isWall(pacX, pacY, LEFT)) {
        map[pacX][pacY - 1] = PACMAN;
        map[pacX][pacY] = EMPTY;
        pacY--;
    // If the user input is the D key, Pacman will move right
    } else if (move == RIGHT && !isWall(pacX, pacY, RIGHT)) {
        map[pacX][pacY + 1] = PACMAN;
        map[pacX][pacY] = EMPTY;
        pacY++;
    }
}

// Function that reads the map.txt file
void readMap() {
    // Opening the map.txt file
    FILE *fp;
    fp = fopen("map.txt", "r");
    map = (char **) malloc(11 * sizeof(char *));

    // Initializes the map (in the form of a pointer) into an 11x11 array
    for (int i = 0; i < 11; i++) {
        map[i] = (char *) malloc(11 * sizeof(char));
    }
    for(int i = 0; i < 11; i++) {
        map[i][0] = WALL;
        map[i][10] = WALL;
    }
    for(int i = 0; i < 11; i++) {
        map[0][i] = WALL;
        map[10][i] = WALL;
    }
    // Retrieving the map.txt file
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            fscanf(fp, "%c ", &map[i][j]);
        }
    }

    // CLose the file to save memory
    fclose(fp);

    // Reads the position of Pacman and both ghosts on the map
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (map[i][j] == PACMAN) {
                pacX = j;
                pacY = i;
            } else if (map[i][j] == GHOST && ghostNum == 0) {
                ghost1X = j;
                ghost1Y = i;
                ghostNum++;
            } else if(map[i][j] == GHOST && ghostNum == 1) {
                ghost2X = j;
                ghost2Y = i;
            }
        }
    }
}

// Function that prints the map from the map.txt
void printMap() {
    system("CLS");
    // Printing the map from the map.txt file
    for (int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            // Assigning colours to the various elements of the game
            switch (map[i][j]){
                case PACMAN:
                    colourChange(YELLOW);
                    break;
                case WALL:
                    colourChange(BLUE);
                    break;
                case GHOST:
                    colourChange(PINK);
                    break;
                case DOT:
                    colourChange(WHITE);
                    break;
            }
            // Printing the colours to the map
            printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}

// Function that prints the walls on the map
int isWall(int x, int y, char direction) {
    // If Pacman is going up into a wall while going up
    switch (direction) {
        case UP:
            if(map[x-1][y] == WALL) {
                return 1;
            }
            // If Pacman is not going into a wall while going up
            else
                return 0;
        // If Pacman is going up into a wall while going left
        case LEFT:
            if(map[x][y-1] == WALL) {
                return 1;
            }
            // If Pacman is not going into a wall while going left
            else
                return 0;
        // If Pacman is going up into a wall while going down
        case DOWN:
            if(map[x+1][y] == WALL) {
                return 1;
            }
            // If Pacman is not going into a wall while going down
            else
                return 0;
        // If Pacman is going up into a wall while going right
        case RIGHT:
            if(map[x][y+1] == WALL) {
                return 1;
            }
            // If Pacman is not going into a wall while going right
            else
                return 0;
        }
    }

// Function that checks whether the user has won or not
int winCheck() {
    int key;
    // If there are no more dots on the map, the player has won
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            if(map[i][j] == DOT)
                return 0;
        }
    }
    return 1;
}


int loseCheck() {
    // If Pacman and the ghost are at the same location, the user has lost
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            if(map[i][j] == GHOST && pacX == i && pacY == j) {
                return 1;
            }
        }
    }
    return 0;
}

// Function that determines the movement of the ghosts
void moveGhost(int ghostX, int ghostY) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (map[i][j] == GHOST) {
                // Checks distance between pacman for both x and y coordinates
//                int distanceX = abs(i - pacX);
//                int distanceY = abs(j - pacY);
                if(pacX == i || pacY == j){
                    if (i < pacX && !isWall(i,j, DOWN)) {
                        map[i][j] = EMPTY;
                        map[i + 1][j] = GHOST;
                    } else if (i > pacX && !isWall(i,j,UP))  {
                        map[i][j] = EMPTY;
                        map[i - 1][j] = GHOST;
                    } else if (j > pacY && !isWall(i,j,LEFT)) {
                        map[i][j] = EMPTY;
                        map[i][j-1] = GHOST;
                    } else if (j < pacY && !isWall(i,j, RIGHT)) {
                        map[i][j] = EMPTY;
                        map[i][j+1] = GHOST;
                    }
                }else {
                    char move = rand() % 4;

                    if(move == 0 && !isWall(i,j,UP)){
                        map[i][j] = EMPTY;
                        map[i-1][j] = GHOST;
                    }
                    else if(move == 1 && !isWall(i,j,LEFT)){
                        map[i][j] = EMPTY;
                        map[i][j-1] = GHOST;
                    }
                    else if(move == 2 && !isWall(i,j, DOWN)){
                        map[i][j] = EMPTY;
                        map[i+1][j] = GHOST;
                    }
                    else if(move == 3 && !isWall(i,j, RIGHT)){
                        map[i][j] = EMPTY;
                        map[i][j+1] = GHOST;
                    }
                }
                // Checks if y distance is larger than x distances, and chooses whether its moved vertically or horizontally
                //if (distanceX < distanceY) {
                    // Compares Pacman distance in the x direction to ghost and moves ghost accordingly
//                    if (i < pacX) {
//                        map[i][j] = EMPTY;
//                        map[i + 1][j] = GHOST;
//
//                    } else if (i > pacX) {
//                        map[i][j] = EMPTY;
//                        map[i - 1][j] = GHOST;
//                    }
//                    // Compares Pacman distance in the y direction to ghost and moves ghost accordingly
//                } else {
//                    if (j < pacY) {
//                        map[i][j] = EMPTY;
//                        map[i][j + 1] = GHOST;
//                    } else if (j > pacY) {
//                        map[i][j] = EMPTY;
//                        map[i][j - 1] = GHOST;
//                    }
                //}
            }
        }
    }
}

