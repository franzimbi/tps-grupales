#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct vector{
    void** datos;
    size_t tamano;
    size_t capacidad;
};

vector_t* vector_crear(size_t tam){
    vector_t* nuevo = malloc(sizeof(vector_t));
    if(nuevo == NULL) return NULL;
    nuevo->datos = malloc(sizeof(void*) * tam);
    if(nuevo->datos == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->tamano = 0;
    nuevo->capacidad = tam;
    return nuevo;
}

void vector_destruir(vector_t* vector, void (*destruir_dato)(void *)){
    for(size_t i=0; i<vector->tamano; i++){
        if(destruir_dato == NULL)
            break;
        destruir_dato(vector->datos[i]);
    }
    free(vector->datos);
    free(vector);
}

static bool vector_redimensionar(vector_t* vector, size_t nuevo_tamano){
    void** aux = realloc(vector->datos, sizeof(void*) * nuevo_tamano);
    if(aux == NULL){
        return false;
    }
    vector->datos = aux;
    vector->capacidad = nuevo_tamano;
    return true;
}

bool vector_agregar(vector_t* vector, void* dato){
    if(vector->tamano == vector->capacidad)
        if(!vector_redimensionar(vector, (vector->tamano)*2)) return false;
    vector->datos[vector->tamano] = dato;
    vector->tamano ++;
    return true;
}

size_t vector_tamano(vector_t* vector){
    return vector->tamano;
}

void* vector_obtener(vector_t* vector, size_t pos){
    return vector->datos[pos];
} 