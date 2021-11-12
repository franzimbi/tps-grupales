#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const int* a, const int* b){
    return (*a) - (*b);
}

static void prueba_heap_vacio(){
    printf("\n\nPRUEBAS HEAP VACIO\n\n");
    heap_t* heap = heap_crear((int (*)(const void *, const void *)) cmp_int);
    print_test("Se creo un heap", heap);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap)==0);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("Desencolar devuelve NULL", heap_desencolar(heap)==NULL);
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap)==NULL);
    print_test("Destruir heap vacio" , true);
    heap_destruir(heap, NULL);
}

static void pruebas_heap_encolar_desencolar(){
    printf("\n\nPRUEBAS HEAP ENCOLAR DESENCOLAR\n\n");
    int* d1 = malloc(sizeof(int));
    *d1 = 10;
    int* d2 = malloc(sizeof(int));
    *d2 = 12;
    int* d3 = malloc(sizeof(int));
    *d3 = 8;
    int* d4 = malloc(sizeof(int));
    *d4 = 20;

    heap_t* heap = heap_crear((int (*)(const void *, const void *)) cmp_int);

    print_test("Se creo un heap", heap);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap)==0);
    print_test("Encolo un elemento", heap_encolar(heap, (void*) d1));
    print_test("Cantidad de elementos es 1", heap_cantidad(heap)==1);
    print_test("El maximo es correcto", heap_ver_max(heap) == d1);
    print_test("Esta vacio da false", !heap_esta_vacio(heap));
    print_test("Desencolo un elemento", heap_desencolar(heap)==d1);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap)==0);
    print_test("Esta vacio da true", heap_esta_vacio(heap));
    print_test("El maximo es NULL", heap_ver_max(heap) == NULL);

    print_test("Encolo un elemento", heap_encolar(heap, d3));
    print_test("Cantidad de elementos es 1", heap_cantidad(heap)==1);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, d2));
    print_test("El maximo es correcto", heap_ver_max(heap) == d2);
    print_test("Cantidad de elementos es 2", heap_cantidad(heap)==2);
    imprimir_heap(heap);

    heap_destruir(heap, free);
}

void pruebas_heap_estudiante(void){
    prueba_heap_vacio();
    pruebas_heap_encolar_desencolar();
}

int main(void){
    pruebas_heap_estudiante();
    return 0;
}