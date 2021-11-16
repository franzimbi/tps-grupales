#include "usuarios.h"
#include "hash.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

struct usuarios{
    hash_t* lista_usuarios;
    char* usuario;
    heap_t* prioridad;
};

#define LARGO_USUARIOS 20

usuarios_t* cargar_usuarios(FILE* listado_usuario){
    char aux[LARGO_USUARIOS];
    hash_t* usuarios = hash_crear(free);
    if(usuarios == NULL) return NULL;

    while(!feof(listado_usuario)){
        fgets(aux, LARGO_USUARIOS, listado_usuario);
        hash_guardar(usuarios, aux, )
    }

}