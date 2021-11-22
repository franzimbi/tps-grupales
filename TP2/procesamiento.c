#include "global.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef hash_t diccionario_t;

typedef struct{
    char* comando;
    (bool (*) (void*)) funcion;
}

typedef enum {LOGIN, LOGOUT, PUBLICAR, SIGUIENTE, LIKEAR, MOSTRAR} comandos_t;
#define CANTIDAD_COMANDOS 6

char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes"};

diccionario_t* iniciar_diccionario(){
    hash_t* diccionario = hash_crear(free);
    if(diccionario == NULL) return NULL;

    for(size_t i=0; i<CANTIDAD_COMANDOS; i++){
        hash_guardar(diccionario, tabla_comandos[i], )
    }
}

