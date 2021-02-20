#include "main.h"

#ifndef __CUBE_ROTATOR_H
#define __CUBE_ROTATOR_H



class CubeRotator
{
	
private:
	struct vec3
		{
			double x,y,z;
			vec3();
			vec3(double,double,double);
			vec3 operator*(const double& rhs);
			vec3 operator+(const vec3& rhs);
			double operator[](int ind);
			void normalize();
			double magnitude();
		};

	double dot_product(vec3&,vec3&);

	double a; // a = length of any side of the cube.
	int pointDensity; // there are pointDensity number of points on one side of the cube, it is like resolution or sensitivity
	int sw,sh; //screen width , screen height.
	vec3 *** points; // <- 3-star-programmer (https://wiki.c2.com/?ThreeStarProgrammer) who uses std::vector in c++ anyway.
	void render_frame(double A,double B);
	void render_frame_nolight(double A,double B);
	vec3 rotate(vec3& p,double A, double B);
	void destructor();
	double K1=2,K2 = 6;

	vec3 * normals;
	vec3 lightSource;
	
	std::string lightstring;
	bool lightningOn;

public:
	CubeRotator();
	CubeRotator(int scrWidth,int scrHeight); 
	~CubeRotator();
	
	void start();
	void pointsPrint();
	
	void setLightning(bool val);
	
};



#endif