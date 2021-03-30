#ifndef _VEC3_H
#define _VEC3_H

class vec3
{
public:
	double x,y,z;
	vec3();
	vec3(double,double,double);
	vec3 operator*(const double& rhs);
	vec3 operator+(const vec3& rhs);
	double operator[](int ind);
	void normalize();
	double magnitude();
};

#endif