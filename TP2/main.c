#include "procesamiento.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argv != 2) return EXIT_FAILURE;

    hash_t* diccionario = iniciar_diccionario();
    if(diccionario == NULL) return EXIT_FAILURE;

    FILE* nombres_usuarios = fopen(argv[1], "r");
    if(nombres_usuarios == NULL){
        cerrar_diccionario(diccionario);
        return EXIT_FAILURE;
    }
    global_t* global = global_crear(nombres_usuarios);
    if(global == NULL){
        cerrar_diccionario(diccionario);
        fclose(nombres_usuarios);
        return EXIT_FAILURE;
    }
    fclose(nombres_usuarios);
    int largo_linea = 0;
    size_t largo_nombre = 50;
    char nombre[50];
    while( ( largo_linea = getline(&nombre, &largo_nombre, stdin) ) != EOF ){
        nombre[largo_linea-1] = '\0'; // para no guardar el \n
        comando_t* comando = buscar_comando(nombre);
        if(comando == NULL){
            fprintf(stderr, "Error: comando inexistente");
        }else{
            // LLAMO A LAS FUNCIONES
        }
    }
    global_destruir(global);
    cerrar_diccionario(diccionario);
    return EXIT_SUCCESS;
}
