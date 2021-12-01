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
    char nombre[50];
    while( (fgets(nombre, 50, stdin)) != NULL ){
        fprintf(stderr, "en el while\n");
        for(size_t i = strlen(nombre); i>0; --i){
            if(nombre[i] == '\n'){
                nombre[i] = '\0';
                break;
            }
        }
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
