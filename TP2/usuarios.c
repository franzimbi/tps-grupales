#include "usuarios.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct usuario{
    char* nombre;
    size_t id;
    heap_t* feed;
    long id_p_ultima;
};

usuario_t* usuario_crear(char* nombre, size_t id, cmp_func_t cmp_publicaciones){
    usuario_t* nuevo = malloc(sizeof(usuario_t));
    if(nuevo == NULL) return NULL;
    nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    if(nuevo->nombre == NULL){
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->id = id;
    nuevo->feed = heap_crear(cmp_publicaciones);
    if(nuevo->feed == NULL){
        free(nuevo->nombre);
        free(nuevo);
        return NULL;
    }
    nuevo->id_p_ultima = -1;
    return nuevo;
}

void usuario_destruir(usuario_t* usuario){
    free(usuario->nombre);
    heap_destruir(usuario->feed, free);
    free(usuario);
}

size_t usuario_ver_id(const usuario_t* usuario){
    return usuario->id;
}

char* usuario_ver_nombre(const usuario_t* usuario){
    return usuario->nombre;
}

bool usuario_guardar_publicacion(usuario_t* usuario, void* publicacion){
    return heap_encolar(usuario->feed, publicacion);
}

void* usuario_ver_siguiente_publicacion(usuario_t* usuario){ 
    return heap_desencolar(usuario->feed);
}

bool feed_esta_al_final(usuario_t* usuario){
    return heap_ver_max(usuario->feed) == NULL;
}

void set_id_ultima_publicacion(usuario_t* usuario, size_t id_p_ultimo){
    usuario->id_p_ultima = (long) id_p_ultimo;
}

long ver_id_ultima_publicacion(usuario_t* usuario){
    return usuario->id_p_ultima;
}