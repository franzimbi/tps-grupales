#include "usuarios.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct usuario{
    heap_t* publicaciones;
    char* nombre;
    size_t id;
};

usuario_t* usuario_crear(char* nombre, size_t id, cmp_func_t cmp_publicaciones){
    usuario_t* nuevo = malloc(sizeof(usuario_t));
    if(nuevo == NULL) return NULL;
    nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    if(nuevo->nombre == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->publicaciones = heap_crear(cmp_publicaciones);
    if(nuevo->publicaciones == NULL){
        free(nuevo->nombre);
        free(nuevo);
        return NULL;
    }
    return nuevo;
}

void usuario_destruir(usuario_t* usuario){
    free(usuario->nombre);
    heap_destruir(usuario->publicaciones, NULL);
    free(usuario);
}

size_t usuario_ver_id(const usuario_t* usuario){
    return usuario->id;
}

char* usuario_ver_nombre(const usuario_t* usuario){
    return usuario->nombre;
}

bool usuario_guardar_publicacion(usuario_t* usuario, publicacion_t* publicacion){
    return heap_encolar(usuario, publicacion);
}

publicacion_t* usuario_ver_siguiente_publicacion(usuario_t* usuario){ 
    return heap_desencolar(usuario->publicaciones);
}