#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "main.h"

void getDimensions();

int screen_width;
int screen_height;


int main()
{


    cout << "Welcome to Terminal Graphics App\n";
    cout << "You can resize the window before choosing\n\n";
    cout << "1- Rotating Cube at the Center\n";
    cout << "2- A moving and rotating cube\n";
    cout << "3- Two cubes at one screen\n";
    cout << "4- A cube and a donut!\n";
    cout << "5- Off Loader\n";

    char input;
    cin >> input;

    //finding screen_height and width
    getDimensions();

    if(input == '1')
    {
        Scene1 scene1;
        scene1.start();
    }
    else if(input == '2')
    {
        Scene2 scene2;
        scene2.start();
    }
    else if(input == '3')
    {
        Scene3 scene3;
        scene3.start();
    }
    else if(input == '4')
    {
        Scene4 scene4;
        scene4.start();
    }
    else if(input == '5')
    {
        Scene5 scene5;
        scene5.loadOff(Path);
        scene5.start();
    }

        
    
    return 0;
}
void getDimensions()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      
    screen_width = csbi.srWindow.Right - csbi.srWindow.Left;
    screen_height = csbi.srWindow.Bottom - csbi.srWindow.Top;
#elif defined(__linux__) || defined(__unix__) // all unices not caught above
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    screen_height = w.ws_row; 
    screen_width = w.ws_col;
#endif
}
void cursor_reset() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
    COORD cursor;
    cursor.X = 0;
    cursor.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
#elif defined(__linux__) || defined(__unix__) // all unices not caught above
    printf("\x1b[H");
#endif
}