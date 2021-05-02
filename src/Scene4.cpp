#include "Scene4.h"



Scene4::Scene4()
{
    output = new char* [screen_height];
    zbuffer = new double* [screen_height];
    for (int i = 0; i < screen_height; i++)
    {
        output[i] = new char[screen_width];
        zbuffer[i] = new double[screen_width];
    }

    //point density can be changed but <20 values do not work well 
    pointDensity = 90;


    a = 5;

    //getting memory for points
    points = new vec3**[6];
    for(int side = 0; side < 6; side++)
    {
        points[side] = new vec3*[pointDensity];
        for(int x = 0; x < pointDensity; x++)
        {
            points[side][x] = new vec3[pointDensity];
        }
    }
    
    //finding unrotated values of all points
    double interval = a / (pointDensity - 1);
    double x,y,z;

    x = -a/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -a/2;
        for(int j = 0; j < pointDensity; j++)
        {
            points[0][i][j] = vec3(x,y,a/2);
            points[1][i][j] = vec3(x,y,-a/2);
            y += interval;
        }
        x += interval;
        
    }
    

    z = a/2;
    for(int i = 0; i < pointDensity; i++)
    {
        y = -a/2;
        for(int j = 0; j < pointDensity; j++)
        {
            points[2][i][j] = vec3(a/2,y,z);
            points[3][i][j] = vec3(-a/2,y,z);

            y += interval;
        }
        z -= interval;
    }

	x = -a/2;
	for(int i = 0; i < pointDensity; i++)
	{
		z = a/2;
		for(int j = 0; j < pointDensity; j++)
		{
			points[4][i][j] = vec3(x,a/2,z);
			points[5][i][j] = vec3(x,-a/2,z);
			z -= interval;
		}
		x += interval;
	}

    //normals of unrotated sides of the cube initialized
    normals = new vec3[6];

    normals[0] = vec3(0,0,1);
    normals[1] = vec3(0,0,-1);

    normals[2] = vec3(1,0,0);
    normals[3] = vec3(-1,0,0);

    normals[4] = vec3(0,1,0);
    normals[5] = vec3(0,-1,0);



    
	lightstring = ".,-~:;=!*#$@";

    thetaInterval = 0.02f;
    phiInterval = 0.02f;
    R1 = 1.779f;
    R2 = 3;

    diff = 3.3;

    //direction of global lightning.
    lightSource1 = vec3(diff,0,-K2);
    lightSource1.normalize();

    lightSource2 = vec3(-diff*1.666,0,-K2);
    lightSource2.normalize();

    //K1 is closeness of the camera to 2d projection.
    K1 = screen_width*K2*3/(24*(R1+R2));

    projection1 = (int) (screen_width/2 + K1*(-1.0/K2)*(diff));
    projection2 = (int) (screen_width/2 + K1*(-1.0/K2)*(-diff));

}

Scene4::~Scene4()
{
    this -> destructor();
}

void Scene4::destructor()
{
    for(int side = 0; side < 6; side++)
    {
        for(int x = 0; x < pointDensity; x++)
        {
            delete [] points[side][x];
        }
    }
    for(int side = 0; side < 6; side++)
    {
        delete [] points[side];
    }
    delete [] points;
    delete [] normals;

    for (int i = 0; i < screen_height; i++)
    {
        delete[] output[i];
        delete[] zbuffer[i];
    }

    delete[] output;
    delete[] zbuffer;
}

void Scene4::start()
{
    double A,B,C,D;
    A = B = C = D = 0.0;

    while(true)
    {
        
        render_frame(A,B,C,D);
        A += 0.05;
        B += 0.03;
        C += 0.06;
        D += 0.02;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        Sleep(27);
#elif defined(__linux__) ||defined(__unix__) 
        usleep(27000);
#endif
    }
}

void Scene4::render_frame(double A, double B,double C, double D)
{
    vec3 rotatedNormals[6];
    for(int i = 0; i < 6; i++)
    {
        rotatedNormals[i] = vec3::rotate(normals[i],A,B);
    }
    
    for (int i = 0; i < screen_height; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    double dotproducts[6];
    for(int i = 0; i < 6; i++)
    {
        dotproducts[i] = vec3::dot_product(rotatedNormals[i],lightSource1);
    }
    
    for(int side = 0; side < 6; side++)
    {
        double L = dotproducts[side]; //lightning of the face
        if(L <= 0)
            continue;
        for(int i = 0; i < pointDensity; i++)
        {
            for (int j = 0; j < pointDensity; j++)
            {
                vec3 rotated = vec3::rotate(points[side][i][j], A, B);
                double x = rotated.x , y = rotated.y , z = rotated.z + K2;


                double ooz = 1.0 / z; //one over z

                int xp = (int)(screen_width / 2 + K1 * ooz * x);
                int yp = (int)(screen_height / 2 + K1 * ooz * y);

                xp = projection1 + 2*(projection1 - xp);
                xp -= diff;
                //xp = (screen_width / 2) + 2 * ((screen_width / 2) - xp);
                if (xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
                {
                    if (zbuffer[yp][xp] < ooz)
                    {
                        output[yp][xp] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp] = ooz;
                    }
                    if (zbuffer[yp][xp+1] < ooz)
                    {
                        output[yp][xp+1] = lightstring[(int)(L * 11)];
                        zbuffer[yp][xp+1] = ooz;
                    }
                }
                
            }
        }
    }

     float cosC = cos(C), sinC = sin(C);
	float cosD = cos(D), sinD = sin(D);  

    for(float theta = 0.0f; theta < twoPi; theta += thetaInterval )
    {
        float cost = cos(theta), sint = sin(theta);
		for(float phi = 0; phi < twoPi; phi += phiInterval)
		{
			float cosp = cos(phi), sinp = sin(phi);

			float circleX = R2 + R1*cost;
			float circleY = R1*sint;
            
        
			float x = circleX * (cosD*cosp + sinC*sinD*sinp) - circleY*cosC*sinD ;
			float y = circleX * (sinD*cosp-sinC*cosD*sinp) + circleY*cosC*cosD ; 
			float z = K2 + cosC*circleX*sinp+circleY*sinC;

			float ooz = 1.0/z; 

			int xp = (int)  (screen_width/2 + K1*ooz*x);
			int yp = (int) (screen_height/2 + K1*ooz*y);

            xp = projection2 + 2*(projection2-xp);
            xp += diff;

            vec3 center = vec3(R2*cosp,0,R2*sinp);
       
            center = vec3::rotate(center,C,D);
            vec3 normal = vec3(x-diff,y,z-K2) - center;
            normal.normalize();

			
            double L = vec3::dot_product(normal,lightSource2);
            if (L < 0)
                continue;
            if (xp >= 0 && yp >= 0 && xp < screen_width && yp < screen_height)
            {
			    if(ooz > zbuffer[yp][xp])
				{
					zbuffer[yp][xp] = ooz;
					output[yp][xp] = lightstring[ (int) (11*L)];
				}
                if(ooz > zbuffer[yp][xp+1])
				{
					zbuffer[yp][xp+1] = ooz;
					output[yp][xp+1] = lightstring[ (int) (11*L)];
				}
			}
		}
    }



	
    cursor_reset();
    for(int i = 0; i < screen_height-1; i++)
    {
        for(int j = 0; j < screen_width; j++)
        {
            putchar(output[i][j]);
        }
        putchar('\n');
    }
    for (int j = 0; j < screen_width; j++)
    {
        putchar(output[screen_height-1][j]);
    }

}

void Scene4::pointsPrint()
{
	for(int side = 0; side < 6; side++)
	{
		for(int i = 0; i < pointDensity; i++)
		{
			for(int j = 0; j < pointDensity; j++)
			{
				auto & p = points[side][i][j];
				cout << "x:" << p.x << " y:" << p.y << " z:" << p.z << "\n";
			}

		}
		cout <<"next side\n";
	}
}

