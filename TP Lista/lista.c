#include "lista.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
    void* dato;
    struct nodo* prox;
}nodo_t;

typedef struct lista{
    struct nodo* prim;
    struct nodo* ult;
    size_t largo;
} lista_t;

nodo_t* nodo_crear(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL) return NULL;
    
    nodo->dato = dato;
    nodo->prox = NULL;

    return nodo;
}

lista_t* lista_crear(void){
    lista_t* nueva_lista = malloc(sizeof(lista_t));
    if(nueva_lista == NULL) return NULL;

    nueva_lista->largo = 0;
    nueva_lista->prim = NULL;
    nueva_lista->ult  = NULL;

    return nueva_lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0 ? true : false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    if(lista_esta_vacia(lista)){
        nodo_t* nuevo_nodo = nodo_crear(dato);
        lista->prim = nuevo_nodo;
        lista->ult = nuevo_nodo;
        lista->largo++;

        return true;
    }

    nodo_t* nuevo_nodo = nodo_crear(dato);
    nuevo_nodo->prox = lista->prim;
    lista->prim = nuevo_nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    if(lista_esta_vacia(lista)){
        nodo_t* nuevo_nodo = nodo_crear(dato);
        lista->prim = nuevo_nodo;
        lista->ult = nuevo_nodo;
        lista->largo++;

        return true;
    }

    nodo_t* nuevo_nodo = nodo_crear(dato);
    lista->ult->prox = nuevo_nodo;
    lista->ult = nuevo_nodo;
    lista->largo++;
    return true;

}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia) return NULL;

    void* dato = lista->prim->dato;
    nodo_t* aux = lista->prim;
    lista->prim = aux->prox;
    free(aux);

    return dato;
}


void *lista_ver_primero(const lista_t *lista){
    return lista->largo == 0 ? NULL : lista->prim;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista->largo == 0 ? NULL : lista->ult;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    nodo_t* nodo = lista->prim;

    while(nodo!= NULL){
        if(destruir_dato != NULL){
            destruir_dato(nodo->dato);
        }
        
        nodo_t* aux = nodo->prox;
        free(nodo);  
        nodo = aux;
    }

    free(lista);
    return;
}