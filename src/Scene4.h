#include "main.h"
#include "vec3.h"

#ifndef _SCENE4_H_
#define _SCENE4_H_



class Scene4
{
	
private:
	

	double dot_product(vec3&,vec3&);

	double a; // a = length of any side of the cube.
	int pointDensity; // there are pointDensity number of points on one side of the cube, it is like resolution or sensitivity
	
	vec3 *** points; // <- 3-star-programmer (https://wiki.c2.com/?ThreeStarProgrammer) who uses std::vector in c++ anyway.
	void render_frame(double A,double B,double C, double D);
	vec3 rotate(vec3& p,double A, double B);
	void destructor();
	double K1=2,K2 = 7.5;
    double diff;

	vec3 * normals;
	vec3 lightSource1,lightSource2;
	
	std::string lightstring;

    float thetaInterval,phiInterval,R1,R2;

public:
	Scene4();

	~Scene4();
	
	void start();
	void pointsPrint();
	

	
};



#endif