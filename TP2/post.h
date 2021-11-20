#ifndef POST_H
#define POST_H

#include <stdlib.h>
#include "usuarios.h"

typedef struct publicacion publicacion_t;
typedef void (*destructor_publicacion)(publicacion_t*);
typedef int (*cmp_post) (publicacion_t*, publicacion_t*, usuario_t*);

//crear una publicacion con su id y creador
//devuelve un puntero a la publicacion o NULL si falla
publicacion_t* publicarcion_nueva(size_t id, char* texto, usuario_t* creador);

size_t publicacion_ver_id(publicacion_t* publicacion);

bool publicacion_likear(publicacion_t* publicacion, char* usuario);

void imprimir_publicacion(const publicacion_t* publicacion);

bool imprimir_likes_publicacion(const publicacion_t* publicacion);

void publicacion_destruir(publicacion_t* publicacion);

//compara la publicacion a con la b respecto al usuario lector.
//a, b y lector fueron creados previamente.
int publicacion_cmp(publicacion_t* a, publicacion_t* b, usuario_t* lector);

#endif