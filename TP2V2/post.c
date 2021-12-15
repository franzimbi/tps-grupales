#include "post.h"
#include "abb.h"
#include <stdio.h>
#include <string.h>

struct publicacion{
    size_t id;
    char* mensaje;
    size_t id_creador;
    abb_t* likes;
};

publicacion_t* publicacion_nueva(size_t id, char* texto, size_t id_creador){
    publicacion_t* publicacion = malloc(sizeof(publicacion_t));
    if(publicacion == NULL) return NULL;

    publicacion->id = id;
    publicacion->id_creador = id_creador;
    size_t tamano_texto = strlen(texto) + 1;
    publicacion->mensaje = malloc(sizeof(char) * tamano_texto);
    strcpy(publicacion->mensaje, texto);
    if(publicacion->mensaje == NULL){
        free(publicacion);
        return NULL;
    }

    publicacion->likes = abb_crear(strcmp, NULL);
    if(publicacion->likes == NULL) return NULL;

    return publicacion;
}

size_t publicacion_ver_id(const publicacion_t* publicacion){
    return publicacion->id;
}

const char* publicacion_ver_mensaje(const publicacion_t* publicacion){
    return publicacion->mensaje;
}

size_t publicacion_ver_id_creador(const publicacion_t* publicacion){
    return publicacion->id_creador;
}

size_t likes_publicacion(const publicacion_t* publicacion){
    return abb_cantidad(publicacion->likes);
}

void likear_publicacion(const publicacion_t* publicacion, char* usuario){
    abb_guardar(publicacion->likes,usuario,NULL);
}

void printear_likes(const publicacion_t* publicacion, void* funcion){
    abb_in_order(publicacion->likes,((bool) (*)(const char*,void*,void*)) funcion,NULL);
}

void publicacion_destruir(publicacion_t* publicacion){
    free(publicacion->mensaje);
    abb_destruir(publicacion->likes);
    free(publicacion);
}