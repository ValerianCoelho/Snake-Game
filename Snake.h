#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define Up 1
#define Down -1
#define Left 2
#define Right -2

#define ArrowUp 72
#define ArrowDown 80
#define ArrowLeft 75
#define ArrowRight 77

int snakeX[50], snakeY[50]; // Snake position
int fruitX, fruitY; // Fruit position
int PrevTailX, PrevTailY; // Previous tail position
int  direction, fruitEaten = 0, score = 0; // Direction of the snake, whether fruit has been eaten, and score

int HEIGHT; // Height of the game board
int WIDTH; // Width of the game board
int Len; // Length of the snake

// Function to move the cursor to a specified location on the console
void gotoXY(int x,int y)    {
    printf("%c[%d;%df",0x1B,y,x);
}

// Function to add a delay to the program
void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

// Function to set up the game board
void setup(int height, int width, int length, int snakeR, int snakeG, int snakeB, int fruitR, int fruitG, int fruitB, int boardR, int boardG, int boardB)
{
    // Initialize the snake's position array to all -1's
    for(int i=0; i<50; i++)
    {
        snakeX[i] = -1;
        snakeY[i] = -1;
    }
    // Initializing default values to the variables
    direction = Right;
    score = 0;
    WIDTH = width;
    HEIGHT = height;
    fruitX = WIDTH/3, fruitY = HEIGHT/3;
    Len = length;

    system("cls");
    snakeX[0]=snakeY[0]=1;
    int snakePresent;
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            snakePresent = 0;

            //Printing Borders
            if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1){
                printf("\033[48;2;%d;%d;%dm  \033[0m",boardR, boardG, boardB);
                continue;
            }
            // Print fruit
            if(i==fruitY && j==fruitX){
                printf("\033[48;2;%d;%d;%dm  \033[0m",fruitR, fruitG, fruitB);
                continue;
            }
            // Print snake
            for(int k=0; k<Len; k++){
                if(i==snakeY[k] && j==snakeX[k]){
                    printf("\033[48;2;%d;%d;%dm  \033[0m",snakeR, snakeG, snakeB);
                    snakePresent = 1;
                    break;
                }
            }
            // If there is no snake or fruit at this position, print a blank space
            if(!snakePresent)
                printf("  ");
        }
        printf("\n");
    }
}

// Function to check if the game is over
int GameNotOver()
{
    // Check if the snake has collided with the game board's edges
    if(snakeX[0] == WIDTH-1 || snakeY[0] == HEIGHT-1 || snakeX[0] == 0 || snakeY[0] == 0)
        return 0;

    // Check if the snake hit itself
    for(int i=1; i<Len; i++)
        if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            return 0;
    // If the snake has not hit any borders or itself, the game is still ongoing
    return 1;
}

// This function listens for user input from the keyboard
void input()
{
    // Check if there is input waiting in the keyboard buffer
    if(kbhit()){
        // Clear any previous input from the buffer
        fflush(stdin);
        // Switch statement to handle the arrow key input
        switch(getch()){
            case ArrowUp:
                if (direction == Down)
                    break;
                direction = Up; break;
            case ArrowDown:
                if (direction == Up)
                    break;
                direction = Down; break;
            case ArrowLeft:
                if (direction == Right)
                    break;
                direction = Left; break;
            case ArrowRight:
                if (direction == Left)
                    break;
                direction = Right; break;
        }
    }
}

void move()
{
    delay(100);  // Add a delay to slow down the movement of the snake

    if(!fruitEaten) // If a fruit hasn't been eaten, store the position of the previous tail
    {
        PrevTailX = snakeX[Len-1];
        PrevTailY = snakeY[Len-1];
    }
    fruitEaten = 0; // Reset the flag for fruit being eaten
    
    // Move each segment of the snake's body to the position of the segment in front of it
    for(int i=Len-1; i>0; i--)
    {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    
    // Move the head of the snake in the direction specified by the user input
    switch(direction)
    {
        case Up:    snakeY[0]--; break;
        case Down:  snakeY[0]++; break;
        case Left:  snakeX[0]--; break;
        case Right: snakeX[0]++; break;
    }
    
    // Check if the snake's head has collided with a fruit
    if(snakeX[0] == fruitX && snakeY[0] == fruitY)
    {
        // If the head has collided with a fruit, generate a new position for the fruit
        srand(time(0));
        fruitX = rand()%(WIDTH-2)+1;
        fruitY = rand()%(HEIGHT-2)+1;
        
        // Increase the length and score of the snake, and set the flag for fruit being eaten
        Len++;
        score++;
        fruitEaten = 1;
    }
}

void redraw(int snakeR, int snakeG, int snakeB, int fruitR, int fruitG, int fruitB)
{
    if(fruitEaten){
        // If fruit has been eaten, draw the snake's head at the new position
        gotoXY(snakeX[0]*2+1, snakeY[0]+1);
        printf("\033[48;2;%d;%d;%dm  \033[0m",snakeR, snakeG, snakeB);
    }
    else{
        // If fruit has not been eaten, erase the tail and draw the head at the new position
        gotoXY(snakeX[0]*2+1, snakeY[0]+1);
        printf("\033[48;2;%d;%d;%dm  \033[0m",snakeR, snakeG, snakeB);

        gotoXY(PrevTailX*2+1, PrevTailY+1);
        printf("  ");        
    }
    // Draw the fruit at its new position
    gotoXY(fruitX*2+1, fruitY+1);
        printf("\033[48;2;%d;%d;%dm  \033[0m",fruitR, fruitG, fruitB);

    // Display the score
    gotoXY(0,HEIGHT+1);
        printf("Score  : %d",score);
}

void snake(int Height, int Width, int snakeLen, int snakeR, int snakeG, int snakeB, int fruitR, int fruitG, int fruitB, int boardR, int boardG, int boardB)
{
    setup(Height, Width, snakeLen, snakeR, snakeG, snakeB, fruitR, fruitG, fruitB, boardR, boardG, boardB);
    while(GameNotOver())
    {
        move();
        redraw(snakeR, snakeG, snakeB, fruitR, fruitG, fruitB);
        input();
    }
    printf("\n");
    getch();
}