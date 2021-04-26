#include "main.h"
#include "vec3.h"

#ifndef _SCENE_H_
#define _SCENE5_H_



class Scene5
{
	
private:
	

	double dot_product(vec3,vec3&);
    int N;
	int faceCount;

    vec3 * faces;
    vec3 * facesNormals;
	vec3 * points;
	void render_frame(double A,double B);
	vec3 rotate(vec3& p,double A, double B);
	void destructor();
	double K1=2,K2 = 10;


	vec3 lightSource;
	
	std::string lightstring;


public:
	Scene5();
	~Scene5();
	
    void loadOff(const char * filename,float scale);
	void start();

	

	
};



#endif