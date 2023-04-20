#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define HighlightLen 30

int NewChoice, OldChoice;

void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

void space(int n)
{
    //Prints HighlightLen-strlen() spaces
    for(int i=0; i<n ;i++)
        printf(" ");
}

void display(char header[], char options[][20], int n, int initialOptionHighlight)
{
    system("cls");
    printf("%s\n", header);
    for(int i=0; i<n; i++)
    {
        if(i+1 == initialOptionHighlight)
        {
            printf("%d) \033[30;107m%s",i+1, options[i]);
            space(HighlightLen-strlen(options[i]));
            printf("\n\033[0m");
            continue;
        }
        printf("%d) %s\n",i+1, options[i]);
    }
    printf("Enter : ");
}

void UpdateDisplay(char options[][20], int n)
{
    if(NewChoice == OldChoice)
        return;

    //Removing Highlight From Previous Choice
    gotoxy(4, OldChoice+2);
    printf("%s", options[OldChoice]);
    space(HighlightLen-strlen(options[OldChoice]));

    //Printing Highlight to new Choice
    gotoxy(4, NewChoice+2);
    printf("\033[30;107m%s", options[NewChoice]);
    space(HighlightLen-strlen(options[NewChoice]));
    printf("\033[0m");

    OldChoice = NewChoice;

}

int WhiteHighlight(char header[], char options[][20], int NumberOfOptions, int initialOptionHighlight)
{
    char ch;
    NewChoice = OldChoice = initialOptionHighlight-1;
    display(header, options, NumberOfOptions, initialOptionHighlight);
    do
    {
        ch = getch();

        //Takes Input From the Keyboard
        if(ch==75 || ch==72)
        {
            if(NewChoice==0)
                continue;
            NewChoice--;
        }
        else if(ch==77 || ch==80)
        {
            if(NewChoice==NumberOfOptions-1)
                continue;
            NewChoice++;
        }
        UpdateDisplay(options, NumberOfOptions);
    }while(ch!=13);
    system("cls");
    return NewChoice+1;
}