#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "main.h"

int screen_width;
int screen_height;
long ERROR = -574128963;


int main()
{
	//finding screen_height and width

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	screen_height = w.ws_col;
	screen_width = w.ws_row; 
    
    cout << "Welcome to Terminal Graphics App\n\n";
    cout << "1- Rotating Cube at the Center\n";
    cout << "2- A moving and rotating cube\n";
    cout << "3- Two cubes at one screen\n";
    cout << "4- A cube and a donut!\n";
    cout << "5- Off Loader\n";

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
    else if(input == '4')
    {
        Scene4 scene4;
        scene4.start();
    }
    else if(input == '5')
    {
        Scene5 scene5;
        scene5.loadOff(Path,0.1f);
        scene5.start();
    }
        
    
    return 0;
}
