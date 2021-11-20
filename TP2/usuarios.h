#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdbool.h>
#include "post.h"

typedef struct usuario usuario_t;
typedef void (*destructor_usuario)(usuario_t*);

//recibe el nombre del nuevo usuario, su id y la funcion de comparacion de las publicaciones.
//devuelve el usuario o NULL si fallo.
usuario_t* usuario_crear(char* nombre, size_t id, cmp_func_t cmp_publicaciones);

//destruye el usuario, pero no las publicaciones.
//el usuario se creo previamente.
void usuario_destruir(usuario_t* usuario);

//devuelve el id del usuario.
//el usuario se creo previamente.
size_t usuario_ver_id(const usuario_t* usuario);

//devuelve la cadena con el nombre del usuario.
//el usuario se creo previamente.
char* usuario_ver_nombre(const usuario_t* usuario);

//se guarda en el feed del usuario la publicacion y devuelve true. si falla devuelve false.
// el usuario y la publicacion fueron creados previamente.
bool usuario_guardar_publicacion(usuario_t* usuario, publicacion_t* publicacion);

//se devuelve la siguiente publicacion con mayor prioridad o NULL si no hay mas publicaciones para ver.
//el usuario fue creado previamente.
publicacion_t* usuario_ver_publicacion(usuario_t* usuario);

#endif
