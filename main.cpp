#include "main.h"
#include "CubeRotator.h"


int main()
{
	//finding screen_height and width
	int screen_width;
	int screen_height;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	screen_width = w.ws_row;
	screen_height = w.ws_col;


	CubeRotator cubeRotator(screen_width,screen_height);

	cout << "Rotating cube on terminal\n\n";
	cout << "Do you want lightning? Type '1' for yes, '0' for no\n";

	char c;
	cin >> c;
	if(c == '1')
	{
		cubeRotator.setLightning(true);
	}
	else cubeRotator.setLightning(false);


	//rotating cube
	cubeRotator.start();
	

    
    return 0;
}