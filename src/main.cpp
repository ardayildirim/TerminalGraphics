#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "main.h"

int screen_width;
int screen_height;
long ERROR = -574128963;


int main()
{
	//finding screen_height and width

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	screen_width = w.ws_row;
	screen_height = w.ws_col;

    
    cout << "Welcome to Terminal Graphics App\n\n";
    cout << "1- Rotating Cube at the Center\n";
    cout << "2- A moving and rotating cube\n";
    cout << "3- Two cubes at one screen\n";

    char input;
    cin >> input;

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
        
    
    return 0;
}