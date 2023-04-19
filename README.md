# Snake-Game
This is a simple snake game written in C language. The program uses various C libraries such as stdio.h, conio.h, and time.h for console input/output and adding delay. The program also uses ASCII codes for arrow keys and defines numerical values for each direction.

The game board is defined by Height and Width variables and initialized by printing each cell's color based on its contents using printf statements with escape sequences.

The game setup is done by initializing the snake's position array to all -1's and then setting the snake's starting position using the snakeX and snakeY arrays. The fruit's location is also initialized randomly within the game board.

The GameNotOver function checks whether the game is still ongoing by checking whether the snake has collided with the game board's edges or hit itself. The input function listens for user input from the keyboard using the kbhit function and switch statement to handle arrow key input.

The move function updates the position of each segment of the snake's body based on the direction of movement and also checks whether the snake has eaten the fruit. If the snake has eaten the fruit, the PrevTailX and PrevTailY variables store the position of the previous tail. If the snake hasn't eaten the fruit, the flag for fruit being eaten is reset.

The program is run in a loop until the game is over, where the snake's movement and score are updated each time. Overall, the program is a basic implementation of the classic snake game using C language and console input/output.
