

// ============================================
// HAAVATA 2.0 - Snake Game 
// UVCE - ISE Department
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 40
#define HEIGHT 20
#define MAX_LENGTH 400

// Structure for positions
typedef struct {
    int x, y;
} Position;

// Global variables
Position snake[MAX_LENGTH];
int length = 3;
Position food;
int score = 0;
int gameOver = 0;
int direction = 0;  // 0=right, 1=down, 2=left, 3=up
int speed = 100;

// ============================================
// PERSON 1: SHREYAS - INITIALIZATION & MAIN
// ============================================
// Your responsibility: setup() and main()
// You handle: Starting the game, initializing variables

void setup() {
    system("cls");
    srand(time(NULL));
    
    // Place snake in center
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    snake[1].x = WIDTH / 2 - 1;
    snake[1].y = HEIGHT / 2;
    snake[2].x = WIDTH / 2 - 2;
    snake[2].y = HEIGHT / 2;
    
    direction = 0;
    score = 0;
    length = 3;
    gameOver = 0;
    
    // Spawn first food
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

int main() {
    setup();
    
    while (!gameOver) {
        draw();      // Person 2's function
        input();     // Person 3's function
        logic();     // Person 4's function
        Sleep(speed);
    }
    
    printf("\n\n\tGAME OVER!\n");
    printf("\tYour Score: %d\n", score);
    printf("\n\tPress any key to exit...");
    getch();
    
    return 0;
}

// ============================================
// PERSON 2: Amit Airodagi - DISPLAY & GRAPHICS
// ============================================
// Your responsibility: draw()
// You handle: Displaying the game on screen

void draw() {
    system("cls");
    int x, y, i;
     printf("\n\t========================================\n");
    printf("\t          HAAVATA 2.0 - SNAKE           \n");
    printf("\t              UVCE - ISE                \n");
    printf("\t========================================\n\n");
    
    // Top border
    printf("\n\t");
    for (i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");
    
    // Game area
    for (y = 0; y < HEIGHT; y++) {
        printf("\t|");
        for (x = 0; x < WIDTH; x++) {
            int printed = 0;
            
            // Print snake
            for (i = 0; i < length; i++) {
                if (snake[i].x == x && snake[i].y == y) {
                    if (i == 0)
                        printf("O");  // Head
                    else
                        printf("o");  // Body
                    printed = 1;
                    break;
                }
            }
            
            // Print food
            if (!printed && food.x == x && food.y == y) {
                printf("*");
                printed = 1;
            }
            
            // Empty space
            if (!printed)
                printf(" ");
        }
        printf("|\n");
    }
    
    // Bottom border
    printf("\t");
    for (i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");
    
    // Score display
    printf("\n\tScore: %d\n", score);
    printf("\tControls: W=Up, S=Down, A=Left, D=Right, X=Exit\n");
}

// ============================================
// PERSON 3: Rajdeep - USER INPUT
// ============================================
// Your responsibility: input()
// You handle: Taking keyboard input from user

void input() {
    if (_kbhit()) {
        char key = _getch();
        
        // Exit game
        if (key == 'x' || key == 'X') {
            gameOver = 1;
            return;
        }
        
        // Change direction (prevent 180 degree turn)
        if ((key == 'w' || key == 'W') && direction != 1)
            direction = 3;  // Up
        
        if ((key == 's' || key == 'S') && direction != 3)
            direction = 1;  // Down
        
        if ((key == 'a' || key == 'A') && direction != 0)
            direction = 2;  // Left
        
        if ((key == 'd' || key == 'D') && direction != 2)
            direction = 0;  // Right
    }
}

// ============================================
// PERSON 4: [NAME] - GAME LOGIC
// ============================================
// Your responsibility: logic()
// You handle: Snake movement, collision detection, eating food

void logic() {
    int i;
    
    // Move body segments
    for (i = length - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    
    // Move head based on direction
    if (direction == 0) snake[0].x++;      // Right
    if (direction == 1) snake[0].y++;      // Down
    if (direction == 2) snake[0].x--;      // Left
    if (direction == 3) snake[0].y--;      // Up
    
    // Check wall collision
    if (snake[0].x < 0 || snake[0].x >= WIDTH || 
        snake[0].y < 0 || snake[0].y >= HEIGHT) {
        gameOver = 1;
        return;
    }
    
    // Check self collision
    for (i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = 1;
            return;
        }
    }
    
    // Check if snake ate food
    if (snake[0].x == food.x && snake[0].y == food.y) {
        score += 10;
        length++;
        
        // Spawn new food
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
        
        // Sound effect
        Beep(800, 100);
    }
}

// ============================================
// END OF CODE
// ============================================
