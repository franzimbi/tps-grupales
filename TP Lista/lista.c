#include "lista.h"
#include "stdlib.h"

typedef struct nodo{
    void* dato;
    struct nodo* proximo;
}nodo_t;

struct lista{
    struct nodo* primero;
    struct nodo* ultimo;
    size_t largo;
};

struct lista_iter{
    struct nodo* actual;
    struct nodo* anterior;
    struct lista* lista;
};

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

    if(lista_esta_vacia(lista)){
        lista->primero = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
        lista->largo++;
        return true;
    }
    nuevo_nodo->proximo = lista->primero;
    lista->primero = nuevo_nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if(nuevo_nodo == NULL) return false;

    if(lista_esta_vacia(lista)){
        lista->primero = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
        lista->largo++;
        return true;
    }

    lista->ultimo->proximo = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;

    void* dato = lista->primero->dato;
    nodo_t* aux = lista->primero;
    lista->primero = aux->proximo;
    free(aux);
    lista->largo--;
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
    while(lista->largo != 0){
        if(destruir_dato != NULL)
            destruir_dato(lista_borrar_primero(lista));
        else{
            lista_borrar_primero(lista);
        }
    }
    free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* actual = lista->primero;
    while(actual!=NULL){
        if(!visitar(actual->dato, extra))
            return;
        actual = actual->proximo;
    }
}

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iterador_creado = malloc(sizeof(lista_iter_t));
    if(iterador_creado==NULL) return NULL;

    iterador_creado->actual = lista->primero;
    iterador_creado->anterior = NULL;
    iterador_creado->lista = lista;
    return iterador_creado;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(lista_iter_al_final(iter))
        return false;
    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(iter->actual==NULL) return NULL;
    return iter->actual->dato;
}
bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual==NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if(iter->actual==iter->lista->primero){
        if(!lista_insertar_primero(iter->lista, dato)) return false;
        iter->actual = iter->lista->primero;
        return true; 
}
    if(lista_iter_al_final(iter)){  
        if(!lista_insertar_ultimo(iter->lista, dato)) return false;
        iter->anterior=iter->lista->ultimo;
        return true;
}
    nodo_t* nuevo=nodo_crear(dato);
    if(nuevo==NULL) return false;
    nuevo->proximo=iter->actual;
    iter->anterior->proximo=nuevo;
    iter->actual=nuevo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)) return NULL;
    if(iter->actual==iter->lista->primero){
        void* dato = lista_borrar_primero(iter->lista);
        if(dato==NULL) return NULL;
        iter->actual=iter->lista->primero;
        return dato;
    }
    
    nodo_t* aux = iter->actual;
    void* dato = aux->dato;
    iter->actual = iter->actual->proximo;
    free(aux);
    iter->lista->largo--;
    return dato;
}
