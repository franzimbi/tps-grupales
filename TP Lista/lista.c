#include "lista.h"

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
    struct nodo* elemento_actual;
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

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
nodo_t* actual = lista->primero;
while(actual!=NULL){
    if(!visitar(actual->dato, extra))
        return;
}
}

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iterador_creado = malloc(sizeof(lista_iter_t));
    if(iterador_creado==NULL) return NULL;

    iterador_creado->elemento_actual = lista->primero;
    return iterador_creado;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(iter->elemento_actual->proximo==NULL) return false;
    iter->elemento_actual = iter->elemento_actual->proximo;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(iter->elemento_actual==NULL) return NULL;
    return iter->elemento_actual->dato;
}
bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->elemento_actual->proximo == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* nuevo = nodo_crear(dato);
    if(nuevo==NULL) return false;

    if()
}
void *lista_iter_borrar(lista_iter_t *iter);