#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_INICIAL 20
#define CONSTANTE_REDIMENSION_DESENCOLAR 4

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

static size_t minimo(void** arr, cmp_func_t cmp, size_t padre, size_t hijo_izq, size_t hijo_der){
    size_t minimo = padre;
    if(cmp(arr[minimo], arr[hijo_izq]) < 0)
        minimo = hijo_izq;
    return cmp(arr[minimo], arr[hijo_der]) < 0 ? hijo_der : minimo;
}

static void upheap(void** arr, size_t hijo, cmp_func_t cmp){
    if(hijo == 0) return;

    size_t padre = (hijo - 1)/2;
    if(cmp(arr[padre], arr[hijo]) < 0){
        swap(arr, padre, hijo);
        upheap(arr, padre, cmp);
    }
}

static void downheap(void** arr, size_t cant, size_t padre, cmp_func_t cmp){
    if(padre == cant) return;

    size_t hijo_izq = (2 * padre) + 1;
    size_t hijo_der = (2 * padre) + 2;
    size_t min =  minimo(arr, cmp, padre, hijo_izq, hijo_der);
    if(min != padre){
        swap(arr, padre, min);
        downheap(arr, cant, min, cmp);
    }
}

static bool heap_redimensionar(heap_t* heap, size_t nuevo_tamano){
    void** aux = realloc(heap->datos, sizeof(void*) * nuevo_tamano);
    if(aux == NULL){
        return false;
    }
    heap->datos = aux;
    heap->tam = nuevo_tamano;
    return true;
}

static void heapify(void** arr, size_t n, cmp_func_t cmp){
    for(size_t i=n-1; i<=0; i--){
        downheap(arr, n, i, cmp);
    }
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);
    size_t tamano = cant;
    while(tamano>1){
        swap(elementos, 0, tamano);
        downheap(elementos, tamano-1, 0, cmp);
    }
}

static heap_t* heap_crear_(cmp_func_t cmp, size_t tamano, size_t cantidad){
    heap_t* nuevo = malloc(sizeof(heap_t));
    if(nuevo == NULL) return NULL;

    nuevo->datos = malloc(sizeof(void*) * tamano);
    if(nuevo->datos == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->cant = cantidad;
    nuevo->tam = tamano;
    nuevo->cmp = cmp;
    return nuevo;
}

heap_t* heap_crear(cmp_func_t cmp){
    return heap_crear_(cmp, TAMANO_INICIAL, 0);
}
//es como un heapify
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    size_t tamano = TAMANO_INICIAL;
    if(tamano < n)
        tamano = n;
    
    heap_t* heap = heap_crear_(cmp, tamano, n);
    if(heap == NULL) return NULL;

    memcpy(heap->datos, arreglo, sizeof(void*) * n);
    heapify(heap->datos, heap->cant, cmp);
    return heap;
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
    if(heap->tam == heap->cant)
        if(!heap_redimensionar(heap, heap->tam * 2)) return false;
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant ++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;

    if(heap->cant * CONSTANTE_REDIMENSION_DESENCOLAR <= heap->tam){
        if(heap->tam /2 <= TAMANO_INICIAL){
            heap_redimensionar(heap, TAMANO_INICIAL);
        }else{
            heap_redimensionar(heap, heap->tam/2 );
        }
    }
    void* dato = heap->datos[0];
    heap->cant --;
    swap(heap->datos, 0, heap->cant);
    downheap(heap->datos, heap->cant, 0, heap->cmp);
    return dato;
}

void imprimir_heap(const heap_t* heap){
    fprintf(stderr, "CANTIDAD: %zu\n TAMANO: %zu\n", heap->cant, heap->tam);
    for(size_t i=0; i<heap->cant; i++){
        void* aux = heap->datos[i];
        fprintf(stderr, "%i\t", (int*) *aux);
    }
    fprintf(stderr, "\n");
}