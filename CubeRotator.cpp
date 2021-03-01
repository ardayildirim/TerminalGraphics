#include "CubeRotator.h"


CubeRotator::CubeRotator()
{

}

CubeRotator::CubeRotator(int screen_width,int screen_height)
{
    
    this->sw = screen_width;
    this->sh = screen_height;

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
    K1 = sw*K2*5/(16*a);

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

CubeRotator::~CubeRotator()
{
    this -> destructor();
}

void CubeRotator::destructor()
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

double CubeRotator::dot_product(vec3& v1, vec3& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void CubeRotator::start()
{
    double A,B;
    A = 0.0;
    B = 0.0;
    if(lightningOn)
        while(true)
        {
            
            render_frame(A,B);
            A += 0.05;
            B += 0.02;
            usleep(40000);
        }
    else while(true)
    {
        render_frame_nolight(A,B);
        A += 0.05;
        B += 0.02;
        usleep(40000);
    } 
   
    
}

void CubeRotator::render_frame(double A, double B)
{
	char output[sw][sh];
    double zbuffer[sw][sh];

    vec3 rotatedNormals[6];
    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = rotate(normals[i],A,B);
    }

    
    for(int i = 0; i < sw; i++)
    {
        for(int j = 0; j < sh; j++)
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
                double x=rotated.x, y=rotated.y, z=rotated.z + K2;
                
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (sw/2 + K1*ooz*x);
                int yp = (int) (sh/2 - K1*ooz*y);

                
                if(zbuffer[xp][yp] < ooz)
                {
                    output[xp][yp] = lightstring[ (int)(L*11)];
                    zbuffer[xp][yp] = ooz;
                }
                
                
            }
        }
    }
	
    printf("\x1b[H");
    for(int i = 0; i < sw; i++)
    {
        for(int j = 0; j < sh; j++)
        {
            putchar(output[i][j]);
        }
        putchar('\n');
    }
}

void CubeRotator::render_frame_nolight(double A, double B)
{
	char output[sw][sh];
    double zbuffer[sw][sh];

    

    
    for(int i = 0; i < sw; i++)
    {
        for(int j = 0; j < sh; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    
    
    for(int side = 0; side < 6; side++)
    {
        
        for(int i = 0; i < pointDensity; i++)
        {
            for(int j = 0; j < pointDensity; j++)
            {
                vec3 rotated = rotate(points[side][i][j],A,B);
                double x=rotated.x, y=rotated.y, z=rotated.z + K2;
                
                
                double ooz = 1.0/z; //one over z

                int xp = (int) (sw/2 + K1*ooz*x);
                int yp = (int) (sh/2 - K1*ooz*y);

                
                if(zbuffer[xp][yp] < ooz)
                {
                    output[xp][yp] = 'a' + side;
                    zbuffer[xp][yp] = ooz;
                }
                
                
            }
        }
    }
	
    printf("\x1b[H");
    for(int i = 0; i < sw; i++)
    {
        for(int j = 0; j < sh; j++)
        {
            putchar(output[i][j]);
        }
        putchar('\n');
    }
}

CubeRotator::vec3 CubeRotator::rotate(vec3& p, double A, double B)
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

void CubeRotator::pointsPrint()
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

void CubeRotator::setLightning(bool val)
{
	lightningOn = val;
}

