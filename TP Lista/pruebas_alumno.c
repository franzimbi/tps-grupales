#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_lista_vacia(){
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    print_test("ver si lista esta vacia", lista_esta_vacia(lista)==true);
    print_test("ver si lista tiene algo en el primer lugar", lista_ver_primero(lista)==NULL);
    print_test("ver si lista tiene algo en el ultimo lugar", lista_ver_ultimo(lista)==NULL);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_insertar_borrar(){
    printf("\nINICIO DE PRUEBAS DE INSERTAR Y BORRAR\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    //creo elementos para insertar y los uso
    int* dato1=malloc(sizeof(int));
    if(dato1==NULL){
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato1 =  45;

    float* dato2=malloc(sizeof(float));
    if(dato2==NULL){
        free(dato1);
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato2 = 234.576f;

    char* dato3=malloc(sizeof(char));
    if(dato2==NULL){
        free(dato1);
        free(dato2);
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato3='A';

    print_test("ver si lista esta vacia", lista_esta_vacia(lista));
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    
    print_test("insertar primero en la lista", lista_insertar_primero(lista, dato1));
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato1);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato1);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==1);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato1);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    print_test("ver si lista esta vacia", lista_esta_vacia(lista));
    
    print_test("volver a insertar elemento ultimo en la lista", lista_insertar_ultimo(lista, dato1));
    print_test("insertar 2do elemento ultimo en la lista", lista_insertar_ultimo(lista, dato2));
    print_test("insertar 3er elemento ultimo en la lista", lista_insertar_ultimo(lista, dato3));
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato1);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato3);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==3);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato1);
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato2);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==2);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato2);
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato3);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato3);
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato3);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    print_test("ver si lista esta vacia", lista_esta_vacia(lista));

    print_test("volver a insertar elementos a la lista", lista_insertar_ultimo(lista, dato1) 
    && lista_insertar_ultimo(lista, dato2) && lista_insertar_ultimo(lista, dato3));
    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, free);
}

static void prueba_lista_destruir_null(){
    printf("\nINICIO PRUEBAS DESTRUIR LISTA CON NULL\n");
    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    int dato1 = 45;
    float dato2 = 234.576f;
    char dato3 = 'A';

    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato1));
    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato2));
    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato3));

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_iterador_interno(){
    
}

void pruebas_pila_estudiante(){
    prueba_lista_vacia();
    prueba_lista_insertar_borrar();
    prueba_lista_destruir_null();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
