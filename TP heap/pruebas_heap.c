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
    char* d1 = "Z";
    char* d2 = "Y";
    char* d3 = "X";
    char* d4 = "W";
    char* d5 = "V";
    char* d6 = "U";
    char* d7 = "T";
    char* d8 = "S";

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

    print_test("Encolo un elemento", heap_encolar(heap,(void*) d3));
    print_test("El maximo es correcto", heap_ver_max(heap) == d3);
    print_test("Cantidad de elementos es 1", heap_cantidad(heap)==1);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, (void *)d2));
    print_test("El maximo es correcto", heap_ver_max(heap) == d2);
    print_test("Cantidad de elementos es 2", heap_cantidad(heap)==2);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, (void *)d4));
    print_test("El maximo es correcto", heap_ver_max(heap) == d2);
     
    print_test("Encolo un elemento", heap_encolar(heap,(void*) d8));
    print_test("El maximo es correcto", heap_ver_max(heap) == d2);
    print_test("Cantidad de elementos es 4", heap_cantidad(heap)==4);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, (void *)d1));
    print_test("El maximo es correcto", heap_ver_max(heap) == d1);
    print_test("Cantidad de elementos es 5", heap_cantidad(heap)==5);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, (void *)d7));
    print_test("El maximo es correcto", heap_ver_max(heap) == d1);
    
    print_test("Encolo un elemento", heap_encolar(heap,(void*) d6));
    print_test("El maximo es correcto", heap_ver_max(heap) == d1);
    print_test("Cantidad de elementos es 7", heap_cantidad(heap)==7);
    print_test("Encolo un elemento con mas prioridad", heap_encolar(heap, (void *)d5));
    print_test("El maximo es correcto", heap_ver_max(heap) == d1);
    print_test("Cantidad de elementos es 8", heap_cantidad(heap)==8);

    print_test("Desencolo un elemento", heap_desencolar(heap)==d1);
    print_test("Desencolo un elemento", heap_desencolar(heap)==d2); 
    print_test("Desencolo un elemento", heap_desencolar(heap)==d3);
    print_test("Desencolo un elemento", heap_desencolar(heap)==d4); 
    print_test("Desencolo un elemento", heap_desencolar(heap)==d5);
    print_test("Desencolo un elemento", heap_desencolar(heap)==d6);
    print_test("Desencolo un elemento", heap_desencolar(heap)==d7);
    print_test("Desencolo un elemento", heap_desencolar(heap)==d8); 
     
    

    heap_destruir(heap, NULL);
}

void pruebas_heap_estudiante(void){
    prueba_heap_vacio();
    pruebas_heap_encolar_desencolar();
}

int main(void){
    pruebas_heap_estudiante();
    return 0;
}