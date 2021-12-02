#include "procesamiento.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2) return EXIT_FAILURE;

    hash_t* diccionario = iniciar_diccionario();
    if(diccionario == NULL) return EXIT_FAILURE;
    //fprintf(stderr, "diccionario creado\n");
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
    //fprintf(stderr, "global\n");
    fclose(nombres_usuarios);
    char nombre[50];
    while( (fgets(nombre, 50, stdin)) != NULL ){
        nombre[strlen(nombre)-1] = '\0'; //borrar el \n
        comando_t comando = buscar_comando(diccionario, nombre);
        if(comando == NULL){
            printf("Error: comando inexistente");
        }else{
            comando(global);
        }
    }
    global_destruir(global);
    cerrar_diccionario(diccionario);
    return EXIT_SUCCESS;
}
