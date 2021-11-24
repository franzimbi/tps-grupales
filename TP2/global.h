#ifndef GLOBAL_H
#define GLOBAL_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct vector vector_t;
typedef struct global global_t;
typedef struct post_con_prioridad post_con_prioridad_t;

//crea una estructura global a partir de un archivo abierto con todos los nombres de usuario.
//post: devuelve un puntero a la estructura o NULL si fallo/
global_t* global_crear(FILE* f);

//destruye global y todos sus datos
void global_destruir(global_t* global);

//logea a un usuario si no hay ninguno logeado. caso contrario devuelve un error.
//pre: globar fue creada
bool usuario_login(void* global, void* usuario);

bool usuario_logout(void* global, void* _);
bool post_publicar(void* global, void* texto);
bool ver_siguiente_feed(void* global, void* _);
bool likear_post(void* global, void* _);
bool mostrar_likes(void* global, void* id_publicacion);

#endif