#ifndef POST_H
#define POST_H

#include <stdlib.h>

typedef struct publicacion publicacion_t;
typedef void (*destructor_publicacion)(publicacion_t*);

//crear una publicacion con su id y creador
//devuelve un puntero a la publicacion o NULL si falla
publicacion_t* publicacion_nueva(size_t id, char* texto, size_t id_creador);

//devuelve el id de la publciacion
//pre: la publicacion fue creada
size_t publicacion_ver_id(const publicacion_t* publicacion);

//devuelve la cadena con el mensaje de la publicacion
//pre: la publicacion fue creada
const char* publicacion_ver_mensaje(const publicacion_t* publicacion);

size_t publicacion_ver_id_creador(const publicacion_t* publicacion);

//desturye la publicacion
//pre: la publacion fue creada
void publicacion_destruir(publicacion_t* publicacion);

#endif