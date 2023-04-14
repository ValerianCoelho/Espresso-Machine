#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <string>

using namespace std;

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
        cout << " ";
}

void display(string header, string options[], int n, int initialOptionHighlight)
{
    system("cls");
    cout << header << endl;
    for(int i=0; i<n; i++)
    {
        if(i+1 == initialOptionHighlight)
        {
            cout << i+1 << ") \033[30;107m" << options[i];
            space(HighlightLen-options[i].length());
            cout << "\n\033[0m";
            continue;
        }
        cout << i+1 << ") " << options[i] << endl;
    }
    cout << "Enter : ";
}

void UpdateDisplay(string options[], int n)
{
    if(NewChoice == OldChoice)
        return;

    //Removing Highlight From Previous Choice
    gotoxy(4, OldChoice+2);
    cout << options[OldChoice];
    space(HighlightLen-options[OldChoice].length());

    //Printing Highlight to new Choice
    gotoxy(4, NewChoice+2);
    cout << "\033[30;107m" << options[NewChoice];
    space(HighlightLen-options[NewChoice].length());
    cout << "\033[0m";

    OldChoice = NewChoice;

}

int WhiteHighlight(string header, string options[], int NumberOfOptions, int initialOptionHighlight)
{
    char ch;
    cout << header;
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