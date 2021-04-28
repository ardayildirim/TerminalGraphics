#include "Scene1.h"

Scene1::Scene1()
{
    output = new char* [screen_height];
    zbuffer = new double* [screen_height];
    for (int i = 0; i < screen_height; i++)
    {
        output[i] = new char[screen_width];
        zbuffer[i] = new double[screen_width];
    }

    //point density can be changed but <20 values do not work well 
    pointDensity = 75;

    a = 5;

    //getting memory for points
    points = new vec3**[6];
    for(int side = 0; side < 6; side++)
    {
        points[side] = new vec3*[pointDensity];
        for(int x = 0; x < pointDensity; x++)
        {
            points[side][x] = new vec3[pointDensity];
        }
    }
    
    //finding unrotated values of all points
    double interval = a / (pointDensity - 1);
    double x,y,z;

    x = -a/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -a/2;
        for(int j = 0; j < pointDensity; j++)
        {
            points[0][i][j] = vec3(x,y,a/2);
            points[1][i][j] = vec3(x,y,-a/2);
            y += interval;
        }
        x += interval;
        
    }
    

    z = a/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -a/2;
        for(int j = 0; j < pointDensity; j++)
        {
            points[2][i][j] = vec3(a/2,y,z);
            points[3][i][j] = vec3(-a/2,y,z);

            y += interval;
        }
        z -= interval;
    }

	x = -a/2;
	for(int i = 0; i < pointDensity; i++)
	{
		z = a/2;
		for(int j = 0; j < pointDensity; j++)
		{
			points[4][i][j] = vec3(x,a/2,z);
			points[5][i][j] = vec3(x,-a/2,z);
			z -= interval;
		}
		x += interval;
	}

    //K1 is closeness of the camera to 2d projection.
    K1 = screen_width*K2*3/(24*a);

    //normals of unrotated sides of the cube initialized
    normals = new vec3[6];

    normals[0] = vec3(0,0,1);
    normals[1] = vec3(0,0,-1);

    normals[2] = vec3(1,0,0);
    normals[3] = vec3(-1,0,0);

    normals[4] = vec3(0,1,0);
    normals[5] = vec3(0,-1,0);

    //direction of global lightning.
    lightSource = vec3(0,0,-1);
    lightSource.normalize();

    
	lightstring = ".,-~:;=!*#$@";
    

}

Scene1::~Scene1()
{
    this -> destructor();
}

void Scene1::destructor()
{
    for(int side = 0; side < 6; side++)
    {
        for(int x = 0; x < pointDensity; x++)
        {
            delete [] points[side][x];
        }
    }
    for(int side = 0; side < 6; side++)
    {
        delete [] points[side];
    }
    delete [] points;
    delete [] normals;

    for (int i = 0; i < screen_height; i++)
    {
        delete[] output[i];
        delete[] zbuffer[i];
    }

    delete[] output;
    delete[] zbuffer;
}


void Scene1::start()
{
    double A,B;
    A = 0.0;
    B = 0.0;
    while(true)
    {
        
        render_frame(A,B);
        A += 0.05;
        B += 0.03;
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        Sleep(30);
        #elif defined(__linux__) ||defined(__unix__) 
        usleep(30000);
        #endif
    }
    
   
    
}

void Scene1::render_frame(double A, double B)
{
    vec3 rotatedNormals[6];
    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = vec3::rotate(normals[i],A,B);
    }

    
    for(int i = 0; i < screen_height; i++)
    {
        for(int j = 0; j < screen_width; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    double dotproducts[6];
    for(int i = 0; i < 6; i++)
    {
        dotproducts[i] = vec3::dot_product(rotatedNormals[i],lightSource);
    }
    
    for(int side = 0; side < 6; side++)
    {
        double L = dotproducts[side]; //lightning of the face
        if(L <= 0)
            continue;
        for(int i = 0; i < pointDensity; i++)
        {
            for(int j = 0; j < pointDensity; j++)
            {
                vec3 rotated = vec3::rotate(points[side][i][j],A,B);
                double x=rotated.x , y=rotated.y, z=rotated.z + K2;
                
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 + K1*ooz*y);

                xp = (screen_width / 2) + 2 * ((screen_width / 2) - xp);

                if (xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
                {
                    if (zbuffer[yp][xp] < ooz)
                    {
                        output[yp][xp] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp] = ooz;
                    }
                    if(zbuffer[yp][xp+1] < ooz)
                    {
                        output[yp][xp+1] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp+1] = ooz;
                    }
                }
                
            }
        }
    }
	
    cursor_reset();

    for(int i = 0; i < screen_height-1; i++)
    {
        for(int j = 0; j < screen_width; j++)
        {
            putchar(output[i][j]);
        }
        putchar('\n');
    }
    for (int j = 0; j < screen_width; j++)
    {
        putchar(output[screen_height-1][j]);
    }
}


