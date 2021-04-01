#include "Scene2.h"



Scene2::Scene2()
{
    

    //point density can be changed but <20 values do not work well 
    pointDensity = 100;


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
    K1 = screen_width*K2*5/(16*a);

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

    xDif = 0;
    yDif = 0;

    xDir = yDir = 1;

    xStep = 0.05;
    yStep = 0.12;

}

Scene2::~Scene2()
{
    this -> destructor();
}

void Scene2::destructor()
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
}

double Scene2::dot_product(vec3& v1, vec3& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void Scene2::start()
{
    double A,B;
    A = 0.0;
    B = 0.0;

    while(true)
    {
        
        render_frame(A,B);
        A += 0.05;
        B += 0.02;
        usleep(40000);
    }
    
   
    
}

void Scene2::render_frame(double A, double B)
{
	char output[screen_width][screen_height];
    double zbuffer[screen_width][screen_height];

    vec3 rotatedNormals[6];
    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = rotate(normals[i],A,B);
    }

    
    for(int i = 0; i < screen_width; i++)
    {
        for(int j = 0; j < screen_height; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    double dotproducts[6];
    for(int i = 0; i < 6; i++)
    {
        dotproducts[i] = dot_product(rotatedNormals[i],lightSource);
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
                vec3 rotated = rotate(points[side][i][j],A,B);
                double x=rotated.x , y=rotated.y, z=rotated.z + K2;
                
                x += xDif;
                y += yDif;
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (screen_width/2 + K1*ooz*x);
                int yp = (int) (screen_height/2 + K1*ooz*y);

                
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

    xDif += xStep * xDir;
    yDif += yStep * yDir;

    if(xDif >= 0.5 || xDif <= -0.5)
    {
        xDir *= -1;
    }
    if(yDif >= 6 || yDif <= -6)
    {
        yDir *= -1;
    } 

    lightSource = vec3(-xDif/10,-yDif/10,-1);
    lightSource.normalize();

    

}



vec3 Scene2::rotate(vec3& p, double A, double B)
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

void Scene2::pointsPrint()
{
	for(int side = 0; side < 6; side++)
	{
		for(int i = 0; i < pointDensity; i++)
		{
			for(int j = 0; j < pointDensity; j++)
			{
				auto & p = points[side][i][j];
				cout << "x:" << p.x << " y:" << p.y << " z:" << p.z << "\n";
			}

		}
		cout <<"next side\n";
	}
}

