#include "procesamiento.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_COMANDOS 6

static char* leer_linea(size_t n){
    int largo_linea = 0;
    char* texto = malloc(sizeof(char) * n); 
    if(texto == NULL) return NULL;
    largo_linea = getline(&texto, &n, stdin);
    texto[largo_linea-1] = '\0';
    return texto;
}

bool string_a_nro(char* str, long* nro){
    char* ptr;
    *nro = strtol(str, &ptr, 10);
    if( (*ptr) != '\0')
        return false;
    return true;
}

bool login(global_t* global){
    char* nombre = leer_linea(20);
    if(nombre == NULL){
        fprintf(stderr, "Error de memoria\n");
        return false;
    }
    bool status = usuario_login(global, nombre);
    free(nombre);
    return status;
}

bool publicar(global_t* global){
    char* texto = leer_linea(70);
    if(texto == NULL){
        fprintf(stderr, "Error de memoria\n");
        return false;
    }
    bool status = post_publicar(global, texto);
    free(texto);
    return status;
}

bool mostrar_likes_(global_t* global){
    char* id = leer_linea(3);
    if(id == NULL){
        fprintf(stderr, "Error de memoria\n");
        return false;
    }
    long nro;
    if( !string_a_nro(id, &nro) ){
        fprintf(stderr, "Error: id invalido\n");
        free(id);
        return false;
    }
    free(id);
    return mostrar_likes(global, nro);
}

const char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes"};
comando_t funciones_comandos[] = {login, usuario_logout, publicar, ver_siguiente_feed, likear_post, mostrar_likes_}; 


hash_t* iniciar_diccionario(){
    hash_t* diccionario = hash_crear(NULL);
    if(diccionario == NULL) return NULL;

    for(size_t i=0; i<CANTIDAD_COMANDOS; i++){
        if(!hash_guardar(diccionario, (char*) tabla_comandos[i], (void*) funciones_comandos[i]))
            hash_destruir(diccionario);
    }
    return diccionario;
}

void cerrar_diccionario(hash_t* diccionario){
    hash_destruir(diccionario);
}

comando_t buscar_comando(hash_t* diccionario, char* clave){
    return (comando_t) hash_obtener(diccionario, clave);
}
