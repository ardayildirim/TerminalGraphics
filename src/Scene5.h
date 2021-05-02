#include "Scenes.h"
#include "vec3.h"

#ifndef _SCENE5_H_
#define _SCENE5_H_



class Scene5
{
	
private:
	char** output;
	double** zbuffer;
    int N;
	int faceCount;
    vec3 * faces;
    vec3 *facesNormals,*vertexNormals;
	vec3 * points;
	void render_frame(double A,double B);
	void destructor();
	double K1=2,K2 = 10;

	vec3 lightSource;
    bool highPoly;
	
	std::string lightstring;

public:
	Scene5();
	~Scene5();
	
    void loadOff(const char * filename,int Distance);
	void start();

	

	
};



#endif