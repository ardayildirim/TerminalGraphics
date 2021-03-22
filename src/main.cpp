#include "CubeRotator.h"
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
    cout << "2- \n\n";
    

	CubeRotator cubeRotator;

	
	cubeRotator.setLightning(true);
	
   

	//rotating cube
	cubeRotator.start();
	

    
    return 0;
}