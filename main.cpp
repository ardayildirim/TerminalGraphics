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

    cout << "Which one do you want to see?\n";
    cout << "1-Rotating donut\n"
    <<		"2-Rotating cube\n";

	char inp;
	cin >> inp;
	if(inp == '1')
	{
		
	}
	else if(inp == '2')
	{
		CubeRotator cubeRotator(screen_width,screen_height);
		cubeRotator.start();
	}
    
    return 0;
}