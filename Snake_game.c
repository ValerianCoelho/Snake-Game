#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// Define the height and width of the game board
#define Height 20
#define Width 20

// Define the numerical values for each direction
#define Up 1
#define Down -1
#define Left 2
#define Right -2

// Define the ASCII codes for arrow keys
#define ArrowUp 72
#define ArrowDown 80
#define ArrowLeft 75
#define ArrowRight 77

// Initialize the starting location of the fruit
int fruitX = Width/3, fruitY = Height/3;

// Initialize the starting location of the snake's head and tail
int snakeX[50], snakeY[50];
int Len=2;
int PrevTailX, PrevTailY;

// Initialize the direction and score variables
int  direction = Right, score = 0;

// Initialize a variable to track whether the snake has eaten a fruit
int fruitEaten = 0;

// Function to move the cursor to a specified location on the console
void gotoxy(int x,int y)    {
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
void setup()
{
    // Initialize the snake's position array to all -1's
    for(int i=0; i<50; i++){
        snakeX[i] = -1;
        snakeY[i] = -1;
    }

    // Clear the console screen and set the snake's starting position
    system("cls");
    snakeX[0]=snakeY[0]=1;

    // Loop through the game board and print each cell's color based on its contents
    int snakePresent;
    for(int i=0; i<Height; i++)
    {
        for(int j=0; j<Width; j++)
        {
            // Print a white cell with a black border for the edges of the game board
            snakePresent = 0;
            if(i==0 || j==0 || i==Height-1 || j==Width-1){
                printf("\033[107m  \033[0m");
                continue;
            }

            // Print a red cell for the fruit's location
            if(i==fruitY && j==fruitX){
                printf("\033[101m  \033[0m");
                continue;
            }

            // Print a green cell for the snake's body
            for(int k=0; k<Len; k++){
                if(i==snakeY[k] && j==snakeX[k]){
                    printf("\033[102m  \033[0m");
                    snakePresent = 1;
                    break;
                }
            }

            // Print a black cell for empty spaces on the game board
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
    if(snakeX[0] == Width-1 || snakeY[0] == Height-1 || snakeX[0] == 0 || snakeY[0] == 0)
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
    delay(100); // Add a delay to slow down the movement of the snake

    if(!fruitEaten){ // If a fruit hasn't been eaten, store the position of the previous tail
        PrevTailX = snakeX[Len-1];
        PrevTailY = snakeY[Len-1];
    }
    fruitEaten = 0; // Reset the flag for fruit being eaten

    // Move each segment of the snake's body to the position of the segment in front of it
    for(int i=Len-1; i>0; i--){
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    
    // Move the head of the snake in the direction specified by the user input
    switch(direction){
        case Up:    snakeY[0]--; break;
        case Down:  snakeY[0]++; break;
        case Left:  snakeX[0]--; break;
        case Right: snakeX[0]++; break;
    }
    
    // Check if the snake's head has collided with a fruit
    if(snakeX[0] == fruitX && snakeY[0] == fruitY){
        // If the head has collided with a fruit, generate a new position for the fruit
        srand(time(0));
        fruitX = rand()%(Width-2)+1;
        fruitY = rand()%(Height-2)+1;
        
        // Increase the length and score of the snake, and set the flag for fruit being eaten
        Len++;
        score++;
        fruitEaten = 1;
    }
}

void redraw(){
    if(fruitEaten){
        // If fruit has been eaten, draw the snake's head at the new position
        gotoxy(snakeX[0]*2+1, snakeY[0]+1);
        printf("\033[102m  \033[0m");
    }
    else{
        // If fruit has not been eaten, erase the tail and draw the head at the new position
        gotoxy(snakeX[0]*2+1, snakeY[0]+1);
        printf("\033[102m  \033[0m");

        gotoxy(PrevTailX*2+1, PrevTailY+1);
        printf("  ");        
    }
    // Draw the fruit at its new position
    gotoxy(fruitX*2+1, fruitY+1);
        printf("\033[101m  \033[0m");

    // Display the score
    gotoxy(0,Height+1);
        printf("Score  : %d",score);
}

int main(){
    // Call the setup function to initialize the game
    setup();
    while(GameNotOver()){ // Keep looping until the game is over 
        move(); // Call the move function to move the snake   
        redraw(); // Call the redraw function to redraw the screen
        input(); // Call the input function to read input from the user
    }
    printf("\n");
    system("pause");
    return 0;
}