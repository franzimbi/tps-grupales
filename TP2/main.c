#include "procesamiento.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2) return EXIT_FAILURE;

    hash_t* diccionario = iniciar_diccionario();
    if(diccionario == NULL) return EXIT_FAILURE;
    fprintf(stderr, "diccionario creado\n");
    FILE* nombres_usuarios = fopen(argv[1], "r");
    if(nombres_usuarios == NULL){
        cerrar_diccionario(diccionario);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "archivo abierto\n");
    global_t* global = global_crear(nombres_usuarios);
    if(global == NULL){
        cerrar_diccionario(diccionario);
        fclose(nombres_usuarios);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "global creado\n");
    fclose(nombres_usuarios);
    int largo_linea = 0;
    size_t largo_nombre = 50;
    char nombre[50];
    
    while( ( largo_linea = getline(&nombre, &largo_nombre, stdin) ) != EOF ){
        fprintf(stderr, "en el while\n");
        nombre[largo_linea-1] = '\0'; // para no guardar el \n
        comando_t comando = buscar_comando(diccionario, nombre);
        if(comando == NULL){
            fprintf(stderr, "Error: comando inexistente");
        }else{
            comando(global);
        }
    }
    global_destruir(global);
    cerrar_diccionario(diccionario);
    return EXIT_SUCCESS;
}
