#include "global.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef hash_t diccionario_t;
typedef bool (*validacion_t)(void *a, void *b);


//typedef enum {LOGIN, LOGOUT, PUBLICAR, SIGUIENTE, LIKEAR, MOSTRAR} comandos_t;
#define CANTIDAD_COMANDOS 6

const char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes"};
validacion_t funciones_comandos[] = {usuario_login, usuario_logout, post_publicar, ver_siguiente_feed, likear_post}; 


diccionario_t* iniciar_diccionario(){
    hash_t* diccionario = hash_crear(free);
    if(diccionario == NULL) return NULL;

    for(size_t i=0; i<CANTIDAD_COMANDOS; i++){
        hash_guardar(diccionario, (char*) tabla_comandos[i], (void*) funciones_comandos[i]); 
    }
    
}

