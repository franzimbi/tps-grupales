#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void prueba_heap_vacio(){
    printf("\n\nPRUEBAS HEAP VACIO\n\n");
    heap_t* heap = heap_crear((int (*)(const void *, const void *)) strcmp);
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

    heap_t* heap = heap_crear((int (*)(const void *, const void *)) strcmp);

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


#define CANTIDAD_DATOS 200
static void pruebas_destruir_heap(){
    printf("\n\nINICIO PRUEBA DESTRUCCION DEL HEAP\n\n");

    char* datos[CANTIDAD_DATOS];
    for(size_t i=0; i<CANTIDAD_DATOS;i++){
        datos[i] = malloc(sizeof(char) * 10);
        strcpy(datos[i], "hola");
    }
    heap_t* heap = heap_crear((int (*)(const void *, const void *)) strcmp);
    print_test("Se creo un heap", heap);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap)==0);
    bool ok = true;
    for(size_t i=0; i<CANTIDAD_DATOS;i++){
        ok &= heap_encolar(heap, datos[i]);
    }
    print_test("Se encolaron varios elementos", ok);
    print_test("La cantidad es correcta", heap_cantidad(heap) == CANTIDAD_DATOS);
    heap_destruir(heap, free);
    print_test("Se destruyo correctamente el heap", true);
}

static void pruebas_elementos_igual_prioridad(){
    char* d1 = "Z";
    char* d2 = "Y";
    char* d3 = "Z";
    char* d4 = "A";

    heap_t* heap = heap_crear((int (*)(const void *, const void *)) strcmp);
    print_test("Se creo un heap", heap);

    print_test("Se encola un elemento", heap_encolar(heap, d1));
    print_test("Se encola un elemento de menor prioridad", heap_encolar(heap, d2));
    print_test("Se encola un elemento de prioridad igual al maximo", heap_encolar(heap, d3));
    print_test("Se encola un elemento de minima prioridad", heap_encolar(heap, d4));
    print_test("Verifico que la cantidad es 4", heap_cantidad(heap)==4);
    print_test("Verifico el primer elemento del heap", heap_ver_max(heap)==d1);
    print_test("Desencolo el maximo", heap_desencolar(heap)==d1);
    print_test("Verifico nuevo maximo", heap_ver_max(heap)==d3);
    print_test("Verifico que la cantidad es 3", heap_cantidad(heap)==3);
    print_test("Desencolo maximo", heap_desencolar(heap)==d3);
    print_test("Verifico que la cantidad es 2", heap_cantidad(heap)==2);
    print_test("Verifico nuevo maximo", heap_ver_max(heap)==d2);

    heap_destruir(heap, NULL);
}


#define CANTIDAD_ARREGLO 8
static void prueba_crear_con_arreglo(){
    printf("\n\nINICIO PRUEBAS CREAR CON UN ARREGLO\n\n");
    char* arreglo[CANTIDAD_ARREGLO] = {"ggg", "bbb", "aaa", "zzz", "ccc", "xxx", "qqq", "ddd"};
    
    heap_t* heap = heap_crear_arr( (void**)arreglo, CANTIDAD_ARREGLO, (int (*)(const void *, const void *)) strcmp);
    print_test("Creo un heap desde un arreglo", heap);
    print_test("Verifico cantidad", heap_cantidad(heap)==CANTIDAD_ARREGLO);
    print_test("Verifico maximo", heap_ver_max(heap)==arreglo[3]);
    print_test("Desencolo", heap_desencolar(heap)==arreglo[3]);
    print_test("Ver nuevo maximo", heap_ver_max(heap)==arreglo[5]);
    print_test("Verifico cantidad", heap_cantidad(heap)==CANTIDAD_ARREGLO-1);
    print_test("Desencolo", heap_desencolar(heap)==arreglo[5]);
    print_test("Verifico cantidad", heap_cantidad(heap)==CANTIDAD_ARREGLO-2);
    print_test("Verifico nuevo maximo", heap_ver_max(heap)==arreglo[6]);

    heap_destruir(heap, NULL);
}

static void prueba_heapsort(){
    printf("\n\nINICIO PRUEBAS ORDENAR CON HEAPSORT\n\n");
    char* arreglo[CANTIDAD_ARREGLO] = {"ggg", "bbb", "aaa", "zzz", "ccc", "xxx", "qqq", "ddd"};
    char* ordenado[CANTIDAD_ARREGLO] = {"aaa", "bbb", "ccc", "ddd", "ggg", "qqq", "xxx", "zzz"};

    heap_sort((void**) arreglo, CANTIDAD_ARREGLO, (int (*)(const void *, const void *)) strcmp);
    print_test("Ordeno un arreglo desordenado con heapsort", true);

    bool ok = true;
    for(size_t i=0; i<CANTIDAD_ARREGLO; i++){
        if(strcmp(arreglo[i], ordenado[i])!=0)
            ok = false;
    }
    print_test("Verifico que el arreglo este bien ordenado", ok);
}

static void prueba_volumen(size_t largo, bool debug){
    printf("\n\nINICIO PRUEBA DE VOLUMEN\n\n");

    heap_t* heap = heap_crear((int (*)(const void *, const void *)) strcmp);
    print_test("Se creo un heap", heap);

    bool ok = true;
//-------------------STRINGS RANDOM-----------------------------
    char** string = calloc(largo, sizeof(char*));
    char* random;
    
    for(size_t j = 0; j < largo; j++){
        random = malloc(sizeof(char)* 5 +1);
        for(size_t i = 0; i < 5; i++){
            int aux = rand() % 126;
            while(aux < 36){
                aux = rand() % 126;
            }
            random[i] = (char) aux;
        }
        random[4] = '\0';
        string[j] = malloc(sizeof(char) * 6 + 1);
        strcpy(string[j], random);
        free(random);
    }
//-------------------------------------------    
    for (int i = 0; i < largo; i++) {
        ok = heap_encolar(heap, (void*) string[i]);
        if (!ok) break;   
    }
    if(debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if(debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    
    heap_sort((void**)string,largo,(int (*)(const void *, const void *)) strcmp);

    for(size_t i = 0; i < largo; i++){
        void* aux = heap_desencolar(heap);
        if( strcmp((char*)aux, string[largo - i - 1]) != 0)
            ok = false;
        if (!ok) break;
    }
    if (debug) print_test("Prueba heap desencolar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_desencolar(heap) == 0);
    
    for(size_t i = 0; i<largo;i++){
        free(string[i]);
    }
    free(string);
    heap_destruir(heap, NULL);
}
void pruebas_heap_estudiante(void){
    prueba_heap_vacio();
    pruebas_heap_encolar_desencolar();
    pruebas_destruir_heap();
    pruebas_elementos_igual_prioridad();
    prueba_crear_con_arreglo();
    prueba_heapsort();
    prueba_volumen(5000, true);
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif