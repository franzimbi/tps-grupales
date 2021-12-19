#include "procesamiento.h"
#include "file_reader.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char* argv[]){
    if(argc != 2) return EXIT_FAILURE;

    hash_t* diccionario = iniciar_diccionario();
    if(diccionario == NULL) return EXIT_FAILURE;
    FILE* nombres_usuarios = fopen(argv[1], "r");
    if(nombres_usuarios == NULL){
        cerrar_diccionario(diccionario);
        return EXIT_FAILURE;
    }
    global_t* global = global_crear(leer_linea(nombres_usuarios));
    if(global == NULL){
        cerrar_diccionario(diccionario);
        fclose(nombres_usuarios);
        return EXIT_FAILURE;
    }
    fclose(nombres_usuarios);
    char buffer[50];
    while( (fgets(buffer, 50, stdin)) != NULL ){
        buffer[strlen(buffer)-1] = '\0'; //borrar el \n
        comando_t comando = buscar_comando(diccionario, buffer);
        if(comando == NULL){
            printf("Error: comando inexistente\n");
        }else{
            comando(global);
        }
    }
    global_destruir(global);
    cerrar_diccionario(diccionario);
    return EXIT_SUCCESS;
}
