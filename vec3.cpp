#include "vec3.h"
#include "main.h"

vec3::vec3()
{
    x = y = z = 0;
}

vec3::vec3(double _x,double _y,double _z)
{
    x = _x; y = _y; z = _z;
}

vec3 vec3::operator*(const double& rhs)
{
    return vec3(x*rhs,y*rhs,z*rhs);
}

vec3 vec3::operator+(const vec3& rhs)
{
    return vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

double vec3::operator[](int ind)
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
	return ERROR;
}

void vec3::normalize()
{
    double mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

double vec3::magnitude()
{
    return sqrt(x*x + y*y + z*z);
}