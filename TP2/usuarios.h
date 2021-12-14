#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdbool.h>
#include "post.h"
#include "heap.h"


// - - - - - - - - - - - - - - - - - - - structura auxiliar para guardar posts en cada feed- - - - - - - - - - - - - 
typedef struct{
    size_t id_publicacion;
    size_t prioridad;
}post_con_prioridad_t;


post_con_prioridad_t* post_con_prioridad_crear(size_t id_post, size_t id_creador, size_t id_lector);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct usuario usuario_t;
typedef void (*destructor_usuario)(usuario_t*);

//recibe el nombre del nuevo usuario, su id y la funcion de comparacion de las publicaciones.
//devuelve el usuario o NULL si fallo.
usuario_t* usuario_crear(char* nombre, size_t id);

//destruye el usuario, pero no las publicaciones.
//pre: el usuario fue creado
void usuario_destruir(usuario_t* usuario);

//devuelve el id del usuario.
//pre: el usuario fue creado
size_t usuario_ver_id(const usuario_t* usuario);

//devuelve la cadena con el nombre del usuario.
//pre: el usuario fue creado
char* usuario_ver_nombre(const usuario_t* usuario);

//se guarda en el feed del usuario la publicacion y devuelve true. si falla devuelve false.
//pre: el usuario y la publicacion fue creado
bool usuario_guardar_publicacion(usuario_t* usuario, publicacion_t* publicacion, size_t id_creador);

//se devuelve la siguiente publicacion con mayor prioridad o NULL si no hay mas publicaciones para ver.
//pre: el usuario fue creado
size_t usuario_ver_siguiente_publicacion(usuario_t* usuario);

//devuelve ture si el feed no tiene mas publicaciones
//pre: el usuario fue creado
bool feed_esta_al_final(usuario_t* usuario);

#endif
