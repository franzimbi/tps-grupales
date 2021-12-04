#include "procesamiento.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_COMANDOS 7

static char* leer_linea(size_t n){

    char* texto = malloc(sizeof(char) * n); 
    if(texto == NULL) return NULL;
    fgets(texto, (int) n, stdin);
    size_t len = strlen(texto);
    if(len < n)
    texto[len-1] = '\0';
    return texto;
}

long string_a_nro(char* str){
    char* ptr;
    long nro = strtol(str, &ptr, 10);
    if( (*ptr) != '\0')
        return -1;
    return nro;
}

bool login(global_t* global){
    char* nombre = leer_linea(20);
    if(nombre == NULL){
        printf("Error de memoria\n");
        return false;
    }
    bool status = usuario_login(global, nombre);
    free(nombre);
    return status;
}

bool publicar(global_t* global){
    char* texto = leer_linea(200);
    if(texto == NULL){
        printf("Error de memoria\n");
        return false;
    }
    bool status = post_publicar(global, texto);
    free(texto);
    return status;
}

bool mostrar_likes_(global_t* global){
    char* id = leer_linea(10);
    if(id == NULL){
        printf("Error de memoria\n");
        return false;
    }
    long nro = string_a_nro(id);
    free(id);
    return mostrar_likes(global, nro);
}

bool likear_post_(global_t* global){
    char* id = leer_linea(10);
    if(id == NULL){
        printf("Error de memoria\n");
        return false;
    }
    long nro = string_a_nro(id);
    free(id);
    likear_post(global, nro);
    return true;
}
bool help_comandos(global_t* _);

const char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes", "help"};
comando_t funciones_comandos[] = {login, usuario_logout, publicar, ver_siguiente_feed, likear_post_, mostrar_likes_, help_comandos}; 

bool help_comandos(global_t* _){
    printf("\nCOMANDOS DISPONIBLES:\n\n");
    for(size_t i=0; i<CANTIDAD_COMANDOS-1; i++){
    printf("%s\n", tabla_comandos[i]);
    }
    printf("\n");
    return true;
}

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
