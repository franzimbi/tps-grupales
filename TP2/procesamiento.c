#include "procesamiento.h"
#include "global.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_COMANDOS 6

const char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes"};
comando_t funciones_comandos[] = {usuario_login, usuario_logout, post_publicar, ver_siguiente_feed, likear_post, mostrar_likes}; 


hash_t* iniciar_diccionario(){
    hash_t* diccionario = hash_crear(NULL);
    if(diccionario == NULL) return NULL;

    for(size_t i=0; i<CANTIDAD_COMANDOS; i++){
        if(!hash_guardar(diccionario, (char*) tabla_comandos[i], (void*) funciones_comandos[i]));
            hash_destruir(diccionario);
    }
    return diccionario;
}

void cerrar_diccionario(hash_t* diccionario){
    hash_destruir(diccionario);
}

comando_t* buscar_comando(hash_t* diccionario, char* clave){
    return (comando_t*) hash_obtener(diccionario, clave);
}

bool string_a_nro(char* str, long* nro){
    char* ptr;
    *nro = strtol(str, &ptr, 10);
    if(ptr != '\0')
        return false;
    return true;
}