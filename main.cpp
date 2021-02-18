#include "main.h"
#include "CubeRotator.h"


int main()
{
	int screen_width;
	int screen_height;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	screen_width = w.ws_row;
	screen_height = w.ws_col;



	CubeRotator cubeRotator(screen_width,screen_height);
	cubeRotator.start();
	
	//cubeRotator.start();
	//cubeRotator.pointsPrint();
	//}
    
    return 0;
}