#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "usuarios.h"
#include "post.h"
#include "abb.h"

#define CANTIDAD_INICIAL 30

typedef struct{
    void** datos;
    size_t tamano;
    size_t capacidad;
}vector_t;

typedef struct{
    vector_t* vector_usr;
    hash_t* hash_usr;
    vector_t* vector_likes; //guarda abb con los likes de cada post segun su id
    vector_t* vector_posts;
    size_t id_post_global;
    usuario_t* login;
}global_t;

typedef struct{
    size_t id_publicacion;
    size_t prioridad;
}post_con_prioridad_t;

//- - - - - - - - - - - - -  - - - - VECTOR DINAMICO - - - - - - - - - - - - - - - - - - - - 
static vector_t* vector_crear(size_t tam){
    vector_t* nuevo = malloc(sizeof(vector_t));
    if(nuevo == NULL) return NULL;
    nuevo->datos = malloc(sizeof(void*) * tam);
    if(nuevo->tamano == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->tamano = 0;
    nuevo->capacidad = tam;
    return nuevo;
}

void vector_destruir(vector_t* vector, void (*destruir_dato)(void *)){
    for(size_t i=0; i<vector->tamano; i++){
        if(destruir_dato == NULL)
            break;
        destruir_dato(vector->datos[i]);
    }
    free(vector->datos);
    free(vector);
}

static bool vector_redimensionar(vector_t* vector, size_t nuevo_tamano){
    void** aux = realloc(vector->datos, sizeof(void*) * nuevo_tamano);
    if(aux == NULL){
        return false;
    }
    vector->datos = aux;
    vector->capacidad = nuevo_tamano;
    return true;
}

static bool vector_agregar(vector_t* vector, void* dato){
    if(vector->tamano == vector->capacidad)
        if(!vector_redimensionar(vector, (vector->tamano)*2)) return false;
    vector->datos[vector->tamano] = dato;
    vector->tamano ++;
    return true;
}

static vector_tamano(vector_t* vector){
    return vector->tamano;
}

static void* vector_obtener(vector_t* vector, size_t pos){
    return vector->datos[pos];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int publicacion_cmp(post_con_prioridad_t* a, post_con_prioridad_t* b){
    a->prioridad - b->prioridad;
}

global_t* global_crear(FILE* f){
    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->vector_usr = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_usr == NULL){
        free(nuevo);
        return NULL;
    }
    int largo_linea = 0;
    char* nombre = malloc(sizeof(char) * 50);
    while( ( largo_linea = getline(nombre,50,f) ) != -1 ){
        nombre[largo_linea-1] = '\0'; // para no guardar el \n
        usuario_t* nuevo_usuario = usuario_crear(nombre, vector_tamano(nuevo->vector_usr), (int (*)(const void*, const void*)) publicacion_cmp);
        if(nuevo_usuario == NULL){
            vector_destruir (nuevo->vector_usr, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
        if(!vector_agregar(nuevo->vector_usr, (void*) nuevo_usuario)){
            vector_destruir(nuevo->vector_usr, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
    }
    free(nombre);
    nuevo->hash_usr = hash_crear(NULL);
    for (size_t i = 0; i < vector_tamano(nuevo->vector_usr); i++){
        hash_guardar(nuevo->hash_usr,usuario_ver_nombre(vector_obtener(nuevo->vector_usr, i)), vector_obtener(nuevo->vector_usr, i));
    }
    nuevo->vector_posts = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_posts == NULL){
        vector_destruir(nuevo->vector_usr, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usr, NULL);
        free(nuevo);
        return NULL;
    }
    nuevo->vector_likes = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_posts == NULL){
        vector_destruir(nuevo->vector_usr, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usr, NULL);
        vector_destruir(nuevo->vector_likes, NULL);
        free(nuevo);
        return NULL;
    }
    nuevo->id_post_global = 0;
    nuevo->login = NULL;
    return nuevo;
}

void global_destruir(global_t* global){
    vector_destruir(global->vector_usr, (void (*) (void*)) usuario_destruir);
    vector_destruir(global->vector_posts, (void (*) (void*)) publicacion_destruir);
    vector_destruir(global->vector_likes, abb_destruir);
    hash_destruir(global->hash_usr);
    free(global);
}

bool usuario_login(global_t* global, char* usuario){
    if(global->login != NULL)
        return false;
    
    usuario_t* usr_logeado = hash_obtener(global->hash_usr, usuario);
    if(usr_logeado == NULL)
        return false;
    global->login = usr_logeado;
    return true;
}

bool usuario_logout(global_t* global){
    if(global->login == NULL)
        return false;
    global->login = NULL;
    return true;
}

bool post_publicar(global_t* global, char* texto){
    if(global->login == NULL)
        return false;
    publicacion_t* nuevo_post = publicacion_nueva(global->id_post_global, texto, usuario_ver_id(global->login));
    if(nuevo_post == NULL) return false;

    if(!vector_agregar(global->vector_posts, (void*) nuevo_post)){
        destructor_publicacion(nuevo_post);
        return false;
    }
    abb_t* likes_post = abb_crear(strcmp, NULL);
    if(!vector_agregar(global->vector_likes, (void*) likes_post)){
        publicacion_destruir(nuevo_post);
        abb_destruir(likes_post);
        return false;
    }
    for(size_t i=0; i<vector_tamano(global->vector_usr); i++){
        if( !usuario_guardar_publicacion(vector_obtener(global->vector_usr, i), (void*) nuevo_post) ){
            publicacion_destruir(nuevo_post);
            abb_destruir(likes_post);
            return false;
        }
    }
    global->id_post_global ++;
    return true;
}


