#include "CubeRotator.h"
#include "main.h"


CubeRotator::CubeRotator()
{

}

CubeRotator::CubeRotator(int screen_width,int screen_height)
{
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    pointDensity = 6;
    a = 3;
    points = new vec3**[6];

    for(int side = 0; side < 6; side++)
    {
        points[side] = new vec3*[pointDensity];
        for(int x = 0; x < pointDensity; x++)
        {
            points[side][x] = new vec3[pointDensity];
        }
    }
    
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
            points[3][i][j] = vec3(-x/2,y,z);

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
		}
		x += interval;
		z -= interval;
	}


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
}

void CubeRotator::start()
{
    double A,B;
    A = 0.0;
    B = 0.0;
    while(true)
    {
        render_frame(A,B);
        A += 0.07;
        B += 0.02;
        usleep(10000);
    }
    
}

CubeRotator::vec3::vec3()
{
    x = y = z = 0;
}

CubeRotator::vec3::vec3(double _x,double _y,double _z)
{
    x = _x; y = _y; z = _z;
}

CubeRotator::vec3 CubeRotator::vec3::operator*(const double& rhs)
{
    return vec3(x*rhs,y*rhs,z*rhs);
}

CubeRotator::vec3 CubeRotator::vec3::operator+(const vec3& rhs)
{
    return vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

double CubeRotator::vec3::operator[](int ind)
{
    switch(ind)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            break;
    }
}