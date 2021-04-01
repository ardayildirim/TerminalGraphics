#include "Scene3.h"



Scene3::Scene3()
{
    

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

    

    //K1 is closeness of the camera to 2d projection.
    K1 = screen_width*K2*5/(16*aFirst);

    //normals of unrotated sides of the cube initialized
    normals = new vec3[6];

    normals[0] = vec3(0,0,1);
    normals[1] = vec3(0,0,-1);

    normals[2] = vec3(1,0,0);
    normals[3] = vec3(-1,0,0);

    normals[4] = vec3(0,1,0);
    normals[5] = vec3(0,-1,0);

    yDif = 8;

    //direction of global lightning.
    lightSourceFirst = vec3(0,yDif/10,-1);
    lightSourceFirst.normalize();

    lightSourceSecond = vec3(0,-yDif/10,-1);
    lightSourceSecond.normalize();


	lightstring = ".,-~:;=!*#$@";
    

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
        A += 0.05;
        B += 0.02;
        C += 0.04;
        D += 0.02;
        usleep(30000);
    }

   
    
}

void Scene3::render_frame(double A, double B,double C,double D)
{
	char output[screen_width][screen_height];
    double zbuffer[screen_width][screen_height];

    for(int i = 0; i < screen_width; i++)
    {
        for(int j = 0; j < screen_height; j++)
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
                double x=rotated.x , y=rotated.y, z=rotated.z + K2;
                
                y -= yDif;
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 - K1*ooz*y);

                
                if(zbuffer[xp][yp] < ooz)
                {
                    output[xp][yp] = lightstring[ (int)(L*11)];
                    zbuffer[xp][yp] = ooz;
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
                double x=rotated.x , y=rotated.y, z=rotated.z + K2;
                
                y += yDif;
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 - K1*ooz*y);

                
                if(zbuffer[xp][yp] < ooz)
                {
                    output[xp][yp] = lightstring[ (int)(L*11)];
                    zbuffer[xp][yp] = ooz;
                }
                
                
            }
        }
    }
	
    printf("\x1b[H");
    for(int i = 0; i < screen_width; i++)
    {
        for(int j = 0; j < screen_height; j++)
        {
            putchar(output[i][j]);
        }
        putchar('\n');
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

