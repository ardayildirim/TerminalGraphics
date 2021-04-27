#ifndef _SCENES_H_
#define _SCENES_H_

#include <assert.h> 
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__) ||defined(__unix__) // all unices not caught above
#include <sys/ioctl.h>
#include <unistd.h>
#else
#error "unkown system"
#endif


#define ERROR -574128963

using std::cout;
using std::cin;

const double pi = 3.14159; //this precision is quite enough
const double twoPi = 6.283185;


extern int screen_width;
extern int screen_height;
extern void getDimensions();
extern void cursor_reset();
#endif
