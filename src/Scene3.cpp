#include "Scene3.h"



Scene3::Scene3()
{
    output = new char*[screen_height];
    zbuffer = new double*[screen_height];
    for (int i = 0; i < screen_height; i++)
    {
        output[i] = new char[screen_width];
        zbuffer[i] = new double[screen_width];
    }
    //point density can be changed but <20 values do not work well 
    pointDensity = 120;


    aFirst = 5;
    aSecond = 4;


    //getting memory for pointsFirst
    pointsFirst = new vec3**[6];
    for(int side = 0; side < 6; side++)
    {
        pointsFirst[side] = new vec3*[pointDensity];
        for(int x = 0; x < pointDensity; x++)
        {
            pointsFirst[side][x] = new vec3[pointDensity];
        }
    }
    
    //finding unrotated values of all points
    double interval = aFirst / (pointDensity - 1);
    double x,y,z;

    x = -aFirst/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -aFirst/2;
        for(int j = 0; j < pointDensity; j++)
        {
            pointsFirst[0][i][j] = vec3(x,y,aFirst/2);
            pointsFirst[1][i][j] = vec3(x,y,-aFirst/2);
            y += interval;
        }
        x += interval;
        
    }
    

    z = aFirst/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -aFirst/2;
        for(int j = 0; j < pointDensity; j++)
        {
            pointsFirst[2][i][j] = vec3(aFirst/2,y,z);
            pointsFirst[3][i][j] = vec3(-aFirst/2,y,z);

            y += interval;
        }
        z -= interval;
    }

	x = -aFirst/2;
	for(int i = 0; i < pointDensity; i++)
	{
		z = aFirst/2;
		for(int j = 0; j < pointDensity; j++)
		{
			pointsFirst[4][i][j] = vec3(x,aFirst/2,z);
			pointsFirst[5][i][j] = vec3(x,-aFirst/2,z);
			z -= interval;
		}
		x += interval;
	}

    //getting memory for pointsSecond
    
    pointsSecond = new vec3**[6];
    for(int side = 0; side < 6; side++)
    {
        pointsSecond[side] = new vec3*[pointDensity];
        for(int x = 0; x < pointDensity; x++)
        {
            pointsSecond[side][x] = new vec3[pointDensity];
        }
    }
    
    //finding unrotated values of all points
    interval = aSecond / (pointDensity - 1);


    x = -aSecond/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -aSecond/2;
        for(int j = 0; j < pointDensity; j++)
        {
            pointsSecond[0][i][j] = vec3(x,y,aSecond/2);
            pointsSecond[1][i][j] = vec3(x,y,-aSecond/2);
            y += interval;
        }
        x += interval;
        
    }
    

    z = aSecond/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -aSecond/2;
        for(int j = 0; j < pointDensity; j++)
        {
            pointsSecond[2][i][j] = vec3(aSecond/2,y,z);
            pointsSecond[3][i][j] = vec3(-aSecond/2,y,z);

            y += interval;
        }
        z -= interval;
    }

	x = -aSecond/2;
	for(int i = 0; i < pointDensity; i++)
	{
		z = aSecond/2;
		for(int j = 0; j < pointDensity; j++)
		{
			pointsSecond[4][i][j] = vec3(x,aSecond/2,z);
			pointsSecond[5][i][j] = vec3(x,-aSecond/2,z);
			z -= interval;
		}
		x += interval;
	}

    

    

    //normals of unrotated sides of the cube initialized
    normals = new vec3[6];

    normals[0] = vec3(0,0,1);
    normals[1] = vec3(0,0,-1);

    normals[2] = vec3(1,0,0);
    normals[3] = vec3(-1,0,0);

    normals[4] = vec3(0,1,0);
    normals[5] = vec3(0,-1,0);

    xDif = 8;
    //direction of global lightning.
    lightSourceFirst = vec3(xDif, 0,-K2);
    lightSourceFirst.normalize();

    lightSourceSecond = vec3(-xDif, 0,-K2);
    lightSourceSecond.normalize();


	lightstring = ".,-~:;=!*#$@";
    

    //K1 is closeness of the camera to 2d projection.
    K1 = screen_width*K2*3/(8*(aFirst));

}

Scene3::~Scene3()
{
    this -> destructor();
}

void Scene3::destructor()
{
    for(int side = 0; side < 6; side++)
    {
        for(int x = 0; x < pointDensity; x++)
        {
            delete [] pointsFirst[side][x];
            delete [] pointsSecond[side][x];
        }
    }
    for(int side = 0; side < 6; side++)
    {
        delete [] pointsFirst[side];
        delete [] pointsSecond[side];
    }
    delete [] pointsFirst;
    delete [] pointsSecond;
    

    delete [] normals;

    for (int i = 0; i < screen_height; i++)
    {
        delete[] output[i];
        delete[] zbuffer[i];
    }

    delete[] output;
    delete[] zbuffer;
}

double Scene3::dot_product(vec3& v1, vec3& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void Scene3::start()
{
    double A,B,C,D;
    A = 0.0;
    B = 0.0;

    C = 0.0;
    D = 0.0;
    while(true)
    {
        
        render_frame(A,B,C,D);
        A += 0.06;
        B += 0.02;
        C += 0.04;
        D += 0.03;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        Sleep(25);
#elif defined(__linux__) ||defined(__unix__) 
        usleep(25000);
#endif
    }

   
    
}

void Scene3::render_frame(double A, double B,double C,double D)
{
    for (int i = 0; i < screen_height; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    vec3 rotatedNormals[6];
    double dotproducts[6];

    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = rotate(normals[i],A,B);
    }

    
    for(int i = 0; i < 6; i++)
    {
        dotproducts[i] = dot_product(rotatedNormals[i],lightSourceFirst);
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
                vec3 rotated = rotate(pointsFirst[side][i][j],A,B);
                double x=rotated.x - xDif, y=rotated.y, z=rotated.z + K2;
                

                
                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 + K1*ooz*y);

                if (xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
                {
                    if (zbuffer[yp][xp] < ooz)
                    {
                        output[yp][xp] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp] = ooz;
                    }
                }
                
            }
        }
    }

    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = rotate(normals[i],C,D);
    }

    
    for(int i = 0; i < 6; i++)
    {
        dotproducts[i] = dot_product(rotatedNormals[i],lightSourceSecond);
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
                vec3 rotated = rotate(pointsSecond[side][i][j],C,D);
                double x=rotated.x + xDif, y=rotated.y, z=rotated.z + K2;

                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 + K1*ooz*y);

                if (xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
                {
                    if (zbuffer[yp][xp] < ooz)
                    {
                        output[yp][xp] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp] = ooz;
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



vec3 Scene3::rotate(vec3& p, double A, double B)
{
    //{{cosB,-sinB,0},{sinB,cosB,0},{0,0,1}}*{{1,0,0},{0,cosA,-sinA},{0,sinA,cosA}}*{{x},{y},{z}}
    double cosA = cos(A), sinA = sin(A);
    double cosB = cos(B), sinB = sin(B);

    double x = p.x,y=p.y,z=p.z;
    double newx = -y*cosA*sinB+z*sinA*sinB+x*cosB;
    double newy = y*cosA*cosB-z*sinA*cosB+x*sinB;
    double newz = y*sinA+z*cosA;

    return vec3(newx,newy,newz);
}

