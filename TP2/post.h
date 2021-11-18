#ifndef post_H
#define post_H

#include <stdlib.h>

typedef struct publicacion publicacion_t;

//crear una publicacion con su id y creador
//devuelve un puntero a la publicacion o NULL si falla
publicacion_t* publicarcion_nueva(size_t id, char* texto, char* creador);

size_t publicacion_ver_id(publicacion_t* publicacion);

bool publicacion_likear(publicacion_t* publicacion, char* usuario);

void imprimir_publicacion(const publicacion_t* publicacion);

bool imprimir_likes_publicacion(const publicacion_t* publicacion);

void publicacion_destruir(publicacion_t* publicacion);

#endif