#ifndef _MAIN_H_
#define _MAIN_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#define OffPath "../meshes/offs/"
#elif defined(__linux__) || defined(__unix__)
#define OffPath "meshes/offs/"
#endif


#endif
