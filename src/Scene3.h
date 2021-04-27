#include "Scenes.h"
#include "vec3.h"

#ifndef _SCENE3_H_
#define _SCENE3_H_



class Scene3
{
	
private:
	char** output;
	double** zbuffer;

	double dot_product(vec3&,vec3&);

	double aFirst,aSecond; // a = length of any side of the cube.
	int pointDensity; // there are pointDensity number of points on one side of the cube, it is like resolution or sensitivity
	
	vec3 *** pointsFirst; // <- 3-star-programmer (https://wiki.c2.com/?ThreeStarProgrammer) who uses std::vector in c++ anyway.
    vec3 *** pointsSecond; // <- 3-star-programmer (https://wiki.c2.com/?ThreeStarProgrammer) who uses std::vector in c++ anyway.
	void render_frame(double A,double B,double C, double D);

	vec3 rotate(vec3& p,double A, double B);
	void destructor();
	double K1=2,K2 = 10;

	vec3 * normals;
	vec3 lightSourceFirst;
    vec3 lightSourceSecond;
    double xDif;
	
	std::string lightstring;


public:
	Scene3();
	~Scene3();
	void start();

	

	
};



#endif