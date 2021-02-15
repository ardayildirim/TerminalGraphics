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
    points = new double**[6];
    for(int side = 0; side < 6; side++)
    {
        points[side] = new double*[screen_width];
        for(int x = 0; x < screen_width; x++)
        {
            points[side][x] = new double[screen_height];
        }
    }
    

    double interval = a / (pointDensity - 1);
    


}

CubeRotator::~CubeRotator()
{
    this -> destructor();
}

void CubeRotator::destructor()
{
    for(int side = 0; side < 6; side++)
    {
        for(int x = 0; x < screen_width; x++)
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

