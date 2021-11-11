#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define TAMANO_INICIAL 20

struct heap{
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

static void swap(void** arr, size_t p1, size_t p2){
    void* aux = arr[p1];
    arr[p1] = arr[p2];
    arr[p2]= aux;
}

static int minimo(void** arr, cmp_func_t cmp, size_t padre, size_t hijo_izq, size_t hijo_der){
    size_t minimo = padre;
    if(cmp(arr[minimo], arr[hijo_izq]) > 0)
        minimo = hijo_izq;
    return cmp(arr[minimo], arr[hijo_der] > 0) ? hijo_der : minimo;
}

static void upheap(void** arr, size_t hijo, cmp_func_t cmp){
    if(hijo == 0) return;

    size_t padre = (hijo - 1)/2;
    if(cmp(arr[padre], arr[hijo]) > 0){
        swap(arr, padre, hijo);
        upheap(arr, padre, cmp);
    }
}

static void downheap(void** arr, size_t cant, size_t padre, cmp_func_t cmp){
    if(padre == cant -1) return;

    size_t hijo_izq = (2 * padre) + 1;
    size_t hijo_der = (2 * padre) + 2;
    size_t min =  minimo(arr, cmp, padre, hijo_izq, hijo_der);
    if(min != padre){
        swap(arr, padre, min);
        downheap(arr, cant, min, cmp);
    }
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

}

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* nuevo = malloc(sizeof(heap_t));
    if(nuevo == NULL) return NULL;

    nuevo->datos = malloc(sizeof(void*) * TAMANO_INICIAL);
    if(nuevo->datos == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->cant = 0;
    nuevo->tam = TAMANO_INICIAL;
    nuevo->cmp = cmp;
    return nuevo;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *)){
    while(!heap_esta_vacio(heap)){
        void* dato = heap_desencolar(heap);
        if(destruir_elemento != NULL)
            destruir_elemento(dato);
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

bool heap_encolar(heap_t *heap, void *elem){
    
}

void *heap_ver_max(const heap_t *heap){

}

void *heap_desencolar(heap_t *heap){

}