#include "Scene5.h"

void Scene5::loadOff(const char * filename,float scale)
{
    FILE* file = fopen(filename,"r");
    char s[340];

    int t2;

    fscanf(file,"%s",s);

    fscanf(file,"%d %d %d\n",&N,&faceCount,&t2);

    points = new vec3[N];
    faces = new vec3[2*faceCount];
    facesNormals = new vec3[2*faceCount];
    int i = 0;
    float x,y,z;
    while(i < N)
    {
        fscanf(file,"%f %f %f",&x,&y,&z);
        points[i] = vec3(x,y,z) * scale;
        i++;
    }

	vec3 sums(0,0,0);
    for(int i = 0; i < N; i++)
    {
        sums = sums +  points[i];
    }
    vec3 CoM = sums * (1.0/N);

    double curMax = -1;
    for(int i = 0; i < N; i++)
    {
        points[i] = points[i] - CoM;
        if(points[i].magnitude() > curMax)
        {
            curMax = points[i].magnitude();
        }
    }

    K2 = curMax + 2;
    K1 = screen_width*K2*3/(8 * K2);


    i = 0;
    int v1,v2,v3,v4;
    int ind = 0;
    while(ind < faceCount)
    {
        fscanf(file,"%d %d %d %d",&t2,&v1,&v2,&v3);
        if(t2 == 4)
        {
            fscanf(file,"%d",&v4);
            faces[i] = (points[v1] + points[v2] + points[v3]) * (1.0/3.0);
            facesNormals[i] = vec3::cross_product( (points[v3] - points[v2]), (points[v1] - points[v2]) );

            faces[i+1] = (points[v2] + points[v3] + points[v4]) * (1.0/3.0);
            facesNormals[i+1] = vec3::cross_product( (points[v4] - points[v3]), (points[v2] - points[v3]) );
            i+=2;
            ind++;
            continue;
        }
        if(t2 == 3)
        {
            faces[i] = (points[v1] + points[v2] + points[v3]) * (1.0/3.0);
            facesNormals[i] = vec3::cross_product( (points[v3] - points[v2]), (points[v1] - points[v2]) );
            i++;
            ind++;
            continue;
        }
        assert(false);
        
    }
    fclose(file);



    
}


Scene5::Scene5()
{

    //K1 is closeness of the camera to 2d projection.
    

    //direction of global lightning.
    lightSource = vec3(0,0,-1);
    lightSource.normalize();
	lightstring = ".,-~:;=!*#$@";
    

}

Scene5::~Scene5()
{
    this -> destructor();
}

void Scene5::destructor()
{
   delete [] points;
}

double Scene5::dot_product(vec3 v1, vec3& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void Scene5::start()
{
    double A,B;
    A = 0.0;
    B = 0.0;
    
    while(true)
    {
        
        render_frame(A,B);
        A += 0.05;
        B += 0.03;
        usleep(30000);
    }
    
   
    
}

void Scene5::render_frame(double A, double B)
{
	char output[screen_width][screen_height];
    double zbuffer[screen_width][screen_height];

    
    for(int i = 0; i < screen_width; i++)
    {
        for(int j = 0; j < screen_height; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    
    
    for(int i = 0; i < faceCount; i++)
    {
        vec3 rotated = rotate(faces[i],A,B);

		vec3 rotatedNormal = rotate(facesNormals[i],A,B);
		rotatedNormal.normalize();
		float L = dot_product(rotatedNormal,lightSource);
		if(L < 0)
			continue;
        double x=rotated.x , y=rotated.y, z=rotated.z + K2;
        double ooz = 1.0/z; //one over z

        int xp = (int) (screen_width/2 + K1*ooz*x);
        int yp = (int) (screen_height/2 + K1*ooz*y);

        
        yp = (screen_height/2) + 2 * ((screen_height/2) - yp);
        
        if(xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
			if(zbuffer[xp][yp] < ooz)
			{
				output[xp][yp] = output[xp][yp+1] = lightstring[ (int)(L*11)];
				zbuffer[xp][yp] = ooz;
            }
    }
    
    printf("\x1b[H");
    for(int i = 0; i < screen_width; i++)
    {
        int j =0;
        for(; j < screen_height; j++)
        {
            putchar(output[i][j]);
        }
	if(!(i == screen_width-1 && j == screen_height)) // -1 was added for stopping the occasional trembling
	    putchar('\n');	                          // on the terminal while printing ~ breuis 27.04.2000
    }
}

vec3 Scene5::rotate(vec3& p, double A, double B)
{
    //{{cosB,-sinB,0},{sinB,cosB,0},{0,0,1}}*{{1,0,0},{0,cosA,-sinA},{0,sinA,cosA}}*{{x},{y},{z}}
    double cosA = cos(A), sinA = sin(A);
    double cosB = cos(B), sinB = sin(B);

    double x = p.x,y=p.y,z=p.z;
    double newx = -y*cosA*sinB+z*sinA*sinB+x*cosB;
    double newy = y*cosA*cosB-z*sinA*cosB+x*sinB;
    double newz = y*sinA+z*cosA;

    return vec3(newx,newy,newz);
}



