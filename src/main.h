#ifndef _MAIN_H_
#define _MAIN_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#define Path "../meshes/offs/gorilla.off"
#elif defined(__linux__) || defined(__unix__)
#define Path "meshes/offs/weirdSphere.off"
#endif

#define CentaurPath "meshes/offs/centaur.off"
#define WomanPath "meshes/offs/woman.off"
#define weirdSpherePath "meshes/offs/weirdSphere.off"
#define DragonPath "meshes/offs/dragon.off"

#endif
