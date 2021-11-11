#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const int* a, const int* b){
    return (*a) - (*b);
}

static void prueba_heap_vacio(){
    heap_t* heap = heap_crear((int (*)(const void *, const void *)) cmp_int);

    print_test("Se creo un heap", heap);
    print_test("Cantidad de elementos en el heap es 0", heap_cantidad(heap)==0);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("Desencolar devuelve NULL", heap_desencolar(heap)==NULL);
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap)==NULL);
    print_test("Destruir heap vacio" , true);
    heap_destruir(heap, NULL);
}
#define CANTIDAD_ELEMENTOS 20
static void pruebas_heap_crear_con_arreglo(){
    int* arr[CANTIDAD_ELEMENTOS];
    for(int i=0; i<CANTIDAD_ELEMENTOS; i++){
        arr[i] = malloc(sizeof(int));
        *arr[i] =  i + 11;
    }


    heap_t* heap = heap_crear_arr((void**) &arr, CANTIDAD_ELEMENTOS, (int (*)(const void *, const void *)) cmp_int);

    print_test("Creo un heap con un arreglo desordenado", heap);
    print_test("Ver maximo devuelve el maximo", heap_ver_max(heap)== arr[CANTIDAD_ELEMENTOS-1]);
    //fprintf(stderr, "max: %i\n", (int) heap_ver_max(heap));
    print_test("Cantidad de elementos es 7", heap_cantidad(heap));

    heap_destruir(heap, NULL);
}

void pruebas_heap_estudiante(void){
    prueba_heap_vacio();
    pruebas_heap_crear_con_arreglo();
}

int main(void){
    pruebas_heap_estudiante();
    return 0;
}