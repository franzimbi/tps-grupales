#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "usuarios.h"
#include "heap.h"
#include "post.h"

#define CANTIDAD_INICIAL 30

typedef struct{
    void** datos;
    size_t tamano;
    size_t capacidad;
}vector_t;

typedef struct{
    usuario_t* usr_logeado;
    vector_t* usuarios;
    vector_t* publicaciones;
    hash_t* hash_usuarios;
    destructor_publicacion post_destruir;
    destructor_usuario usr_destruir;
}global_t;

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
        if(destruir_dato != NULL)
            destruir_dato(vector->datos[i]);
    }
    free(vector->datos);
    free(vector);
}

static bool redimensionar_vector(vector_t* vector, size_t nuevo_tamano){
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
        if(!redimensionar_vector(vector, (vector->tamano)*2)) return false;
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

global_t* crear_global(FILE* f){
    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->usuarios = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->usuarios == NULL){
        free(nuevo);
        return NULL;
    }
    int largo_linea = 0;
    char* nombre = malloc(sizeof(char) * 50);

    while( (largo_linea = getline(nombre,50,f)) != -1  ){
        nombre[largo_linea-1] = '\0'; // para no guardar el \n
        usuario_t* nuevo_usuario = usuario_crear(nombre, vector_tamano(nuevo->usuarios), publicacion_cmp);
        if(nuevo_usuario == NULL){
            vector_destruir (nuevo->usuarios, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
        if(!vector_agregar(nuevo->usuarios, nuevo_usuario)){
            vector_destruir (nuevo->usuarios, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
    }
    free(nombre);
    nuevo->hash_usuarios = hash_crear(NULL);
    for (size_t i = 0; i < vector_tamano(nuevo->usuarios); i++){
        hash_guardar(nuevo->hash_usuarios,usuario_ver_nombre(vector_obtener(nuevo->usuarios, i)), vector_obtener(nuevo->usuarios, i));
    }
    nuevo->publicaciones = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->publicaciones == NULL){
        vector_destruir(nuevo->usuarios, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usuarios, NULL);
        free(nuevo);
        return NULL;
    }
    nuevo->usr_destruir = usuario_destruir;
    nuevo->post_destruir = publicacion_destruir;
    nuevo->usr_logeado = NULL;
    return nuevo;
}

void destruir_global(global_t* global){
    vector_destruir(global->usuarios, (void (*) (void*)) global->usr_destruir);
    vector_destruir(global->publicaciones, (void (*) (void*)) global->post_destruir);
    hash_destruir(global->hash_usuarios);
    free(global);
}

