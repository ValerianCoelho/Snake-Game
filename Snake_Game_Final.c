#include <stdio.h>
#include "TUI.h"
#include "Snake.h"
#include <stdio.h>


int Height = 20;
int Width = 20;
int SnakeLen = 5;
int snakeR = 0;
int snakeG = 255;
int snakeB = 0;
int fruitR = 255;
int fruitG = 0;
int fruitB = 0;
int boardR = 255;
int boardG = 255;
int boardB = 255;

int main()
{
    // options for the main menu
    char HeaderQuestion[40] = "Do Your Want to Play Again ?";
    char PlayAgainOption[][20] = {"Yes", "No"};
    char Header[40] = "Select One Of the Following :-";
    char colourChoice[][20] = {"Red", "Green", "Blue", "Yellow", "Cyan", "Pink", "Back"};
    char OptionI[][20] = {"Play Game", "Settings"};
    char OptionII[][20] = {"Snake Length", "Grid Size", "Snake Colour", "Fruit Colour", "Border Colour", "Back"};

    // label for the main menu
    jumpI:

    // display main menu and get user input
    switch(WhiteHighlight(Header, OptionI, 2, 1))
    {
        // if user chooses to play game
        case 1:
            // start snake game with current settings
            snake(Height, Width, SnakeLen, snakeR, snakeG, snakeB, fruitR, fruitG, fruitB, boardR, boardG, boardB);

            // ask if user wants to play again
            switch(WhiteHighlight(HeaderQuestion, PlayAgainOption, 2, 1))
            {
                // if user wants to play again, jump back to main menu
                case 1: goto jumpI;
                // if user doesn't want to play again, exit the program
                case 2: break;
            }
            break;

        // if user chooses settings
        case 2:
            // label for the settings menu
            jumpII:

            // display settings menu and get user input
            switch(WhiteHighlight(Header, OptionII, 6, 1))
            {
                // if user chooses to change snake length
                case 1:
                    printf("Enter Snake Length : ");
                    scanf("%d", &SnakeLen);
                    break;

                // if user chooses to change grid size
                case 2:
                    printf("Enter Grid Width :");
                    scanf("%d", &Width);
                    printf("Enter Grid Height :");
                    scanf("%d", &Height);
                    break;
                
                // if user chooses to change snake color
                case 3:
                    switch(WhiteHighlight(Header, colourChoice, 7, 1))
                    {
                        // if user chooses red colour
                        case 1: 
                            snakeR = 255;
                            snakeG = 0;
                            snakeB = 0;
                            break;

                        // if user chooses green colour
                        case 2: 
                            snakeR = 0;
                            snakeG = 255;
                            snakeB = 0;
                            break;

                        // if user chooses blue colour
                        case 3: 
                            snakeR = 0;
                            snakeG = 0;
                            snakeB = 255;
                            break;

                        // if user yellow chooses colour
                        case 4: 
                            snakeR = 255;
                            snakeG = 255;
                            snakeB = 0;
                            break;

                        // if user cyan chooses colour
                        case 5: 
                            snakeR = 0;
                            snakeG = 255;
                            snakeB = 255;
                            break;

                        // if user pink chooses colour
                        case 6: 
                            snakeR = 255;
                            snakeG = 0;
                            snakeB = 255;
                            break;
                            
                        // if user chooses to go back
                        case 7: 
                            goto jumpII;
                    }
                    break;

                // if user chooses to change fruit colour
                case 4:
                    switch(WhiteHighlight(Header, colourChoice, 7, 1))
                    {
                        // if user chooses red colour
                        case 1: 
                            fruitR = 255;
                            fruitG = 0;
                            fruitB = 0;
                            break;

                        // if user chooses green colour
                        case 2: 
                            fruitR = 0;
                            fruitG = 255;
                            fruitB = 0;
                            break;

                        // if user chooses blue colour
                        case 3: 
                            fruitR = 0;
                            fruitG = 0;
                            fruitB = 255;
                            break;

                        // if user yellow chooses colour
                        case 4: 
                            fruitR = 255;
                            fruitG = 255;
                            fruitB = 0;
                            break;

                        // if user cyan chooses colour
                        case 5: 
                            fruitR = 0;
                            fruitG = 255;
                            fruitB = 255;
                            break;

                        // if user pink chooses colour
                        case 6: 
                            fruitR = 255;
                            fruitG = 0;
                            fruitB = 255;
                            break;
                        
                        // if user chooses to go back
                        case 7: 
                            goto jumpII;
                    }
                    break;

                // if user chooses to change border colour
                case 5:
                    switch(WhiteHighlight(Header, colourChoice, 7, 1))
                    {
                        case 1: 
                            boardR = 255;
                            boardG = 0;
                            boardB = 0;
                            break;
                        case 2: 
                            boardR = 0;
                            boardG = 255;
                            boardB = 0;
                            break;
                        case 3: 
                            boardR = 0;
                            boardG = 0;
                            boardB = 255;
                            break;
                        case 4: 
                            boardR = 255;
                            boardG = 255;
                            boardB = 0;
                            break;
                        case 5: 
                            boardR = 0;
                            boardG = 255;
                            boardB = 255;
                            break;
                        case 6: 
                            boardR = 255;
                            boardG = 0;
                            boardB = 255;
                            break;
                        case 7: 
                            goto jumpII;
                    }
                    break;

                // if user chooses to go back
                case 6:
                    goto jumpI;
                    break;
            }
            goto jumpII;
    }
    return 0;
}