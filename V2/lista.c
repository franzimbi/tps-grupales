#include "lista.h"

typedef struct nodo{
    void* dato;
    struct nodo* proximo;
}nodo_t;

typedef struct lista{
    struct nodo* primero;
    struct nodo* ultimo;
    size_t largo;
} lista_t;

nodo_t* nodo_crear(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL) return NULL;
    
    nodo->dato = dato;
    nodo->proximo = NULL;

    return nodo;
}

lista_t* lista_crear(void){
    lista_t* nueva_lista = malloc(sizeof(lista_t));
    if(nueva_lista == NULL) return NULL;

    nueva_lista->largo = 0;
    nueva_lista->primero = NULL;
    nueva_lista->ultimo  = NULL;

    return nueva_lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if(nuevo_nodo == NULL) return false;

    lista->largo++;

    if(lista_esta_vacia(lista)){
        lista->primero = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
        return true;
    }
    nuevo_nodo->proximo = lista->primero;
    lista->primero = nuevo_nodo;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if(nuevo_nodo == NULL) return false;
    
    lista->largo++;

    if(lista_esta_vacia(lista)){
        lista->primero = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
        return true;
    }

    lista->ultimo->proximo = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;

    void* dato = lista->primero->dato;
    nodo_t* aux = lista->primero;
    lista->primero = aux->proximo;
    free(aux);

    return dato;
}


void *lista_ver_primero(const lista_t *lista){
    return lista->largo == 0 ? NULL : lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista->largo == 0 ? NULL : lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    nodo_t* nodo = lista->primero;

    while(nodo!= NULL){
        if(destruir_dato != NULL)
            destruir_dato(nodo->dato);
        
        nodo_t* siguiente_nodo = nodo->proximo;
        free(nodo);  
        nodo = siguiente_nodo;
    }

    free(lista);

}