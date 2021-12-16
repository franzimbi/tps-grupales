#include "procesamiento.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_COMANDOS 7
#define CANT_INI 200


static char* tabla_error[] = {  "\0", 
                                "Error: Ya habia un usuario loggeado\n", 
                                "Error: usuario no existente\n",
                                "Error: no habia usuario loggeado\n",
                                "Usuario no loggeado o no hay mas posts para ver\n", 
                                "Error: Usuario no loggeado o Post inexistente\n", 
                                "Error: Post inexistente o sin likes\n"
                                }; 


char* leer_linea(FILE* f){
    char* texto = malloc(sizeof(char) * CANT_INI);
    if(texto == NULL) return NULL;
    size_t counter = 0;
    size_t n = CANT_INI;
    char caracter;
    while((caracter = (char) fgetc(f)) != '\n' && caracter != EOF ){
        if(counter == n - 1){
            n *= 2;
            char* aux = realloc(texto, sizeof(char) * n);
            if(aux == NULL) return NULL;
            texto = aux;
        }
        texto[counter] = caracter;
        counter++;
    }
    if(caracter == EOF){
        free(texto);
        return NULL;
    }
    texto[counter] = '\0';
    return texto;        
}

static long string_a_nro(char* str){
    char* ptr;
    long nro = strtol(str, &ptr, 10);
    if( (*ptr) != '\0')
        return -1;
    return nro;
}

static void imprimir_error(status_t status){
    if(status != TODO_OK)
        printf("%s", tabla_error[status]);
}

void login(global_t* global){
    char* nombre = leer_linea(stdin);
    if(nombre == NULL){
        printf("Error de memoria\n");
    }
    imprimir_error(usuario_login(global, nombre));
    free(nombre);
}

void logout(global_t* global){
    imprimir_error(usuario_logout(global));
}

void publicar(global_t* global){
    char* texto = leer_linea(stdin);
    if(texto == NULL){
        printf("Error de memoria\n");
    }
    imprimir_error(post_publicar(global, texto));
    free(texto);
}

void siguiente(global_t* global){
    imprimir_error(ver_siguiente_feed(global));
}

void mostrar_likes_(global_t* global){
    char* id = leer_linea(stdin);
    if(id == NULL){
        printf("Error de memoria\n");
    }
    long nro = string_a_nro(id);
    free(id);
    imprimir_error(mostrar_likes(global, nro));
}

void likear_post_(global_t* global){
    char* id = leer_linea(stdin);
    if(id == NULL){
        printf("Error de memoria\n");
    }
    long nro = string_a_nro(id);
    free(id);
    imprimir_error(likear_post(global, nro));
}
void help_comandos(global_t* _);

const char* tabla_comandos[] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes", "help"};
comando_t funciones_comandos[] = {login, logout, publicar, siguiente, likear_post_, mostrar_likes_, help_comandos}; 

void help_comandos(global_t* _){
    printf("\nCOMANDOS DISPONIBLES:\n\n");
    for(size_t i=0; i<CANTIDAD_COMANDOS-1; i++){
    printf("%s\n", tabla_comandos[i]);
    }
    printf("\n");
}

hash_t* iniciar_diccionario(){
    hash_t* diccionario = hash_crear(NULL);
    if(diccionario == NULL) return NULL;

    for(size_t i=0; i<CANTIDAD_COMANDOS; i++){
        if(!hash_guardar(diccionario, (char*) tabla_comandos[i], *(void**) (&funciones_comandos[i])))
            hash_destruir(diccionario);
    }
    return diccionario;
}

void cerrar_diccionario(hash_t* diccionario){
    hash_destruir(diccionario);
}

comando_t buscar_comando(hash_t* diccionario, char* clave){
    void* comando = hash_obtener(diccionario, clave);
    return  **(comando_t*) &comando;
}
