#include "heap.h"
#include "testing.h"

typedef struct{
    int prioridad;
    void* dato;
}elemento_t;

static elemento_t* elemento_crear(int prioridad, void* dato){
    elemento_t* nuevo = malloc(sizeof(elemento_t));
    if(nuevo == NULL) return NULL;
    nuevo->prioridad = prioridad;
    nuevo ->dato = dato;
    return nuevo
}

static int cmp_elemento(const elemento_t* a, const elemento_t* b){
    return a->prioridad - b->prioridad;
}

static void elemento_destruir(elemento_t* elemento){
    free(elemento->dato);
    free(elemento);
}
static void prueba_heap_vacio(){
    heap_t* heap = heap_crear(cmp_elemento);

    print_test("Se creo un heap", heap);
    print_test("Cantidad de elementos en el heap es 0", heap_cantidad(heap)==0);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("Desencolar devuelve NULL", heap_desencolar(heap)==NULL);
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap)==NULL);
    print_test("Destruir heap vacio" , true);
    heap_destruir(heap, NULL);
}

void pruebas_heap_estudiante(void){

}