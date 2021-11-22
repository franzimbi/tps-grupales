#include "post.h"
#include <stdio.h>
#include <string.h>

struct publicacion{
    size_t id;
    char* mensaje;
    size_t id_creador;
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

void publicacion_destruir(publicacion_t* publicacion){
    free(publicacion->mensaje);
    free(publicacion);
}