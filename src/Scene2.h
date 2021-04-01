#include "main.h"
#include "vec3.h"

#ifndef _SCENE2_H_
#define _SCENE2_H_



class Scene2
{
	
private:
	

	double dot_product(vec3&,vec3&);

	double a; // a = length of any side of the cube.
	int pointDensity; // there are pointDensity number of points on one side of the cube, it is like resolution or sensitivity
	
	vec3 *** points; // <- 3-star-programmer (https://wiki.c2.com/?ThreeStarProgrammer) who uses std::vector in c++ anyway.
	void render_frame(double A,double B);
	vec3 rotate(vec3& p,double A, double B);
	void destructor();
	double K1=2,K2 = 6;

	vec3 * normals;
	vec3 lightSource;
	
	std::string lightstring;

    double xDif,yDif;
    int xDir, yDir;

    double xStep;
    double yStep ;
public:
	Scene2();

	~Scene2();
	
	void start();
	void pointsPrint();
	
	
};



#endif