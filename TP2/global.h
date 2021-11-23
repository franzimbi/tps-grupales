#ifndef GLOBAL_H
#define GLOBAL_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct vector vector_t;
typedef struct global global_t;
typedef struct post_con_prioridad post_con_prioridad_t;

global_t* global_crear(FILE* f);
void global_destruir(global_t* global);
bool usuario_login(void* global, void* usuario);
bool usuario_logout(void* global, void* _);
bool post_publicar(void* global, void* texto);
bool ver_siguiente_feed(void* global, void* _);
bool likear_post(void* global, void* _);

#endif