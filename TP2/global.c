#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "usuarios.h"

#define CANTIDAD_INICIAL 30

typedef struct{
    usuario_t** usuarios;
    size_t largo_usuarios;
    size_t total_users;
    size_t id_publicacion;
    //char** usuarios;
    hash_t* hash_usuarios;
}global_t;

bool redimensionar_usuarios(global_t* global, size_t nuevo_tamano){
    usuario_t** aux = realloc(global->usuarios, sizeof(usuario_t*) * nuevo_tamano);
    if(aux == NULL){
        return false;
    }

    global->usuarios = aux;
    global->largo_usuarios = nuevo_tamano; 

    return true;
}


global_t* crear_global(FILE* f){
    // FILE* usuarios = fopen(f,"r");
    // if(usuarios == NULL) return NULL;

    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->id_publicacion = 0;
    nuevo->total_users = 0;

    nuevo->usuarios = malloc(sizeof(usuario_t*) * CANTIDAD_INICIAL);
    if(nuevo->usuarios == NULL) retrun NULL;

    nuevo->largo_usuarios = CANTIDAD_INICIAL;


    int largo_linea;
    char* nombre;
    while((largo_linea = getline(nombre,50,f)) != -1){
        if(nuevo->total_users == nuevo->largo_usuarios){
            rediensionar_usuarios(nuevo, nuevo->largo_usuarios * 2);
        }
        usuario_t* nuevo_usuario = usuario_crear(nombre,nuevo->total_users, NULL);
        if(nuevo_usuario == NULL) return NULL;

        nuevo->usuarios[nuevo->total_users] = nuevo_usuario;
        nuevo->total_users++;
    }    
    
    nuevo->hash_usuarios = hash_crear(NULL);
    for (size_t i = 0; i < nuevo->total_users; i++){
        hash_guardar(nuevo->hash_usuarios,nuevo->usuarios[i]->nombre, nuevo->usuarios[i]);
    }
    
    return nuevo;
}


