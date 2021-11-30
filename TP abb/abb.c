#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct abb_nodo{
    struct abb_nodo* izq;
    struct abb_nodo* der;
    void* dato;
    char* clave;
}abb_nodo_t;

struct abb{
    struct abb_nodo* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t tamano;
};

struct abb_iter{
    pila_t* pila;
    abb_nodo_t* raiz;
};

typedef bool (*funcion_recursiva_bool)(abb_nodo_t**, const char*, void*, abb_t*);
typedef void* (*funcion_recursiva_void_pointer) (const abb_nodo_t*, const char*, const abb_t*);

static abb_nodo_t* nodo_crear(char* clave, void* dato){
    abb_nodo_t* nuevo = malloc(sizeof(abb_nodo_t));
    if (nuevo == NULL) return NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->clave = malloc(sizeof(char) * (strlen(clave) + 1));
    if (nuevo->clave == NULL) {
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->clave, clave);
    nuevo->dato = dato;
    return nuevo;
}

static void* nodo_destruir(abb_nodo_t* nodo){
    free(nodo->clave);
    void* aux = nodo->dato;
    free(nodo);
    return aux;
}

static abb_nodo_t** nodo_obtener(abb_nodo_t** raiz, const char* clave, const abb_t* arbol){
    if ((*raiz) == NULL)
        return raiz;
    if (arbol->cmp(clave, (*raiz)->clave) == 0)
        return raiz;
    if (arbol->cmp(clave, (*raiz)->clave) < 0)
        return nodo_obtener(&(*raiz)->izq, clave, arbol);
    else 
        return nodo_obtener(&(*raiz)->der, clave, arbol);
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* nuevo = malloc(sizeof(abb_t));
    if (nuevo==NULL) return NULL;    

    nuevo->raiz=NULL;
    nuevo->cmp = cmp;
    nuevo->destruir_dato = destruir_dato;
    nuevo->tamano = 0;
    return nuevo;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    //return abb_guardar_( (abb_nodo_t**) &(arbol)->raiz, clave, dato, arbol);
    abb_nodo_t** nodo = nodo_obtener(&(arbol)->raiz, clave, arbol);
    if(*nodo == NULL){
        *nodo = nodo_crear((char*) clave, dato);
        arbol->tamano++;
        return (*nodo) != NULL;
    }else{
        if (arbol->destruir_dato != NULL)
            arbol->destruir_dato((*nodo)->dato);
        (*nodo)->dato = dato;
        return true;
    }
}

void* abb_obtener(const abb_t *arbol, const char *clave){
    abb_nodo_t** nodo = nodo_obtener( (abb_nodo_t**) &(arbol)->raiz, clave, arbol);
    return (*nodo) != NULL ? (*nodo)->dato : NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    abb_nodo_t** nodo = nodo_obtener( (abb_nodo_t**) &(arbol)->raiz, clave, arbol);
    return (*nodo) != NULL;
}

size_t abb_cantidad(const abb_t *arbol){
    return arbol->tamano;
}

static void abb_destruir_(abb_nodo_t* raiz, abb_t* arbol){
    if (raiz == NULL)
        return;
    abb_destruir_(raiz->izq, arbol);
    abb_destruir_(raiz->der, arbol);
    void* dato = nodo_destruir(raiz);
    if (arbol->destruir_dato != NULL)
        arbol->destruir_dato(dato);
    raiz=NULL;
}

void abb_destruir(abb_t *arbol){
    abb_destruir_(arbol->raiz, arbol);
    free(arbol);
}

static abb_nodo_t* nodo_todo_der(abb_nodo_t** raiz){
    if ((*raiz)->der == NULL){
        abb_nodo_t* aux = (*raiz);
        (*raiz) = (aux)->izq;
        return aux;
    }
    return nodo_todo_der(&(*raiz)->der);
}

void* abb_borrar(abb_t *arbol, const char *clave){
    abb_nodo_t** nodo = nodo_obtener(&(arbol)->raiz, clave, arbol);
    if (*nodo == NULL)
        return NULL;
    arbol->tamano--;
    if ((*nodo)->izq == NULL && (*nodo)->der == NULL){
        void* dato = nodo_destruir(*nodo); 
        *nodo = NULL;
        return dato;
    }
    if ((*nodo)->izq == NULL){
        abb_nodo_t* reemplazo = (*nodo)->der;
        void* dato = nodo_destruir(*nodo);
        *nodo = reemplazo;
        return dato;
    }
    if ((*nodo)->der == NULL){
        abb_nodo_t* reemplazo = (*nodo)->izq;
        void* dato = nodo_destruir(*nodo);
        *nodo = reemplazo;
        return dato;
    }else{
            abb_nodo_t* reemplazo_de_borrado = nodo_todo_der(&(*nodo)->izq);
            abb_nodo_t* izq = (*nodo)->izq;
            abb_nodo_t* der = (*nodo)->der;
            void* dato = nodo_destruir(*nodo);
            (*nodo) = reemplazo_de_borrado;
            if (reemplazo_de_borrado!=izq)
                reemplazo_de_borrado->izq = izq;
            if (reemplazo_de_borrado!=der)
                reemplazo_de_borrado->der = der;
            return dato;
        }
}

//- - - - - - - - - - - - - - - - - - - - - - - ITERADORES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static bool abb_in_order_(abb_nodo_t *raiz, bool visitar(const char *, void *, void *), void *extra){
    if (raiz==NULL)
        return true;

    if (!abb_in_order_(raiz->izq, visitar, extra)) return false;
    if (!visitar(raiz->clave, raiz->dato, extra)) return false;
    if (!abb_in_order_(raiz->der, visitar, extra)) return false;
    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    abb_in_order_(arbol->raiz, visitar, extra);
}

static void ciclo_apilar(abb_iter_t* iter, abb_nodo_t* raiz){
    while (raiz != NULL){
        pila_apilar(iter->pila, raiz);
        raiz = raiz->izq;
    }
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(iter==NULL)
        return NULL;
    
    iter->pila = pila_crear();
    if(iter->pila==NULL){
        free(iter);
        return NULL;
    }
    abb_nodo_t* raiz = arbol->raiz;
    iter->raiz = raiz;

    ciclo_apilar(iter, raiz);
    return iter;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    abb_nodo_t* aux = pila_ver_tope(iter->pila);
    return aux!=NULL ? aux->clave : NULL;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;
    abb_nodo_t* aux = pila_desapilar(iter->pila);
    if(aux->der!=NULL){
        aux = aux->der;
        ciclo_apilar(iter, aux);
    }
    return true;
}
