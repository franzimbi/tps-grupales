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
    fprintf(stderr,"ANTES DEL SWAP ESTO ES A[0] %s\n\n Y ESTO ES A[ULT] %s\n\n", (char*)arr[p1],(char*)arr[p2]);
    void* aux = arr[p1];
    arr[p1] = arr[p2];
    arr[p2]= aux;
    fprintf(stderr,"ESTO ES A[0] %s\n\n Y ESTO ES A[ULT] %s\n\n", (char*)arr[p1],(char*)arr[p2]);

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
    fprintf(stderr, "upheap\n\n");
    if(cmp(arr[padre], arr[hijo]) < 0){
        fprintf(stderr,"ANTES DEL SWAP ESTO ES A[0] %s\n\n Y ESTO ES A[ULT] %s\n\n", (char*)arr[padre],(char*)arr[hijo]);
        fprintf(stderr, "dentro del if upheap\n\n");
        swap(arr, padre, hijo);
        upheap(arr, padre, cmp);
    }

}

static void downheap(void** arr, size_t cant, size_t padre, cmp_func_t cmp){
    if(padre == cant) return;
    fprintf(stderr,"entrando a downheap\n");
    size_t min;
    size_t hijo_izq = (2 * padre) + 1;
    size_t hijo_der = (2 * padre) + 2;

    if(hijo_izq>=cant){
        fprintf(stderr, "IZQUIERDA>=CANT\n\n");
        return;
    }
    if(hijo_der>=cant){
        fprintf(stderr,"hijo der\n");
        if(cmp(arr[padre],arr[hijo_izq]) <= 0 ){
             min = hijo_izq;
        }
        else min = padre;
    }
    else{
        min =  minimo(arr, cmp, padre, hijo_izq, hijo_der);
    }

    fprintf(stderr,"casi al final de downheap\n");
    
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
     fprintf(stderr,"%ls\n\n",(int*)heap->datos[0]);
    fprintf(stderr,"%p\n\n",*aux);
    fprintf(stderr,"%p\n\n",heap->datos);
    heap->datos = aux;
    fprintf(stderr,"%p\n\n",heap->datos);
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
    fprintf(stderr,"entrando a destruir\n");
    while(!heap_esta_vacio(heap)){
         fprintf(stderr,"ciclo heap\n");
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
    //fprintf(stderr,"element %p\n\n",elem);
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
     //fprintf(stderr,"ACA\n");
    /*if(heap->cant * CONSTANTE_REDIMENSION_DESENCOLAR <= heap->tam){
        if(heap->tam /2 <= TAMANO_INICIAL){
             fprintf(stderr,"ACA\n");
            heap_redimensionar(heap, TAMANO_INICIAL);
        }else{
            heap_redimensionar(heap, heap->tam/2 );
        }
    }
    */
   
     //fprintf(stderr,"ACA\n");
     //fprintf(stderr,"%p\n\n",&heap->datos);
     //fprintf(stderr," dato %s\n\n",(char*)heap->datos[0]);
     //fprintf(stderr," dato %p\n\n",heap->datos[1]);
     //fprintf(stderr," dato %p\n\n",heap->datos[2]);
    
    void* dato = heap->datos[0];
    swap(heap->datos, 0, heap->cant - 1);
    heap->cant--;
    fprintf(stderr,"ESTO ES CANTIDAD%ld\n\n", heap->cant);
    fprintf(stderr,"pre downheap\n");
    downheap(heap->datos, heap->cant, 0, heap->cmp);
    return dato;
}