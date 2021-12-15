#include "usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct usuario{
    char* nombre;
    size_t id;
    heap_t* feed;
};

static int publicacion_cmp(post_con_prioridad_t* a, post_con_prioridad_t* b){
    if(b->prioridad == a->prioridad)
        return (int) b->id_publicacion - (int) a->id_publicacion;
    
    return (int) b->prioridad - (int) a->prioridad; 
}

post_con_prioridad_t* post_con_prioridad_crear(size_t id_post, size_t id_creador, size_t id_lector){
    post_con_prioridad_t* p_prioridad = malloc(sizeof (post_con_prioridad_t));
    if(p_prioridad == NULL) return NULL;
    
    long dif_id = id_creador - id_lector;
    if(dif_id < 0)
        dif_id *= -1;
    
    p_prioridad->id_publicacion = id_post;
    p_prioridad->prioridad =  dif_id;
    return p_prioridad;
}

usuario_t* usuario_crear(char* nombre, size_t id){
    usuario_t* nuevo = malloc(sizeof(usuario_t));
    if(nuevo == NULL) return NULL;
    nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    if(nuevo->nombre == NULL){
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->id = id;
    nuevo->feed = heap_crear( (int (*)(const void *, const void *)) publicacion_cmp);
    if(nuevo->feed == NULL){
        free(nuevo->nombre);
        free(nuevo);
        return NULL;
    }
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

bool usuario_guardar_publicacion(usuario_t* usuario, publicacion_t* publicacion, size_t id_creador){
    post_con_prioridad_t* p_prioridad = post_con_prioridad_crear(publicacion_ver_id(publicacion), id_creador, usuario_ver_id(usuario));
    return heap_encolar(usuario->feed, p_prioridad);
}

size_t usuario_ver_siguiente_publicacion(usuario_t* usuario){ 
    post_con_prioridad_t* p_prioridad = (post_con_prioridad_t*) heap_desencolar(usuario->feed);
    size_t id = p_prioridad->id_publicacion;
    free(p_prioridad);
    return id;
}

bool feed_esta_al_final(usuario_t* usuario){
    return usuario == NULL ? false : heap_ver_max(usuario->feed) == NULL;
}