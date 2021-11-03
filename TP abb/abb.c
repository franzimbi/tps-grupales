#include "abb.h"
#include <stdlib.h>
#include <string.h>

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
};

static abb_nodo_t* nodo_crear(char* clave, void* dato){
    abb_nodo_t* nuevo=malloc(sizeof(abb_nodo_t));
    if(nuevo==NULL) return NULL;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    nuevo->clave=malloc(sizeof(char)*strlen(clave));
    if(nuevo->clave==NULL){
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->clave, clave);
    nuevo->dato = dato;

}
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* nuevo=malloc(sizeof(abb_t));
    if(nuevo==NULL) return NULL;

    nuevo->raiz=NULL;
    nuevo->cmp = cmp;
    nuevo->destruir_dato = destruir_dato;
    return nuevo;
}

static bool abb_guardar_(abb_nodo_t* raiz, const char *clave, void *dato, abb_t* arbol){
    if(raiz==NULL){
        raiz = nodo_crear(clave, dato);
        if(raiz==NULL) return false;
        return true;
    }
    if(arbol->cmp(clave, raiz->clave)){
        if(arbol->destruir_dato!= NULL)
            arbol->destruir_dato(raiz->dato);
        raiz->dato=dato;
    }
    if(arbol->cmp(clave, raiz->clave)<0){
        return abb_guardar_(raiz->izq, clave, dato, arbol);
    }else{
        return abb_guardar_(raiz->der, clave, dato, arbol);
    }
    
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    return abb_guardar_(arbol->raiz, clave, dato, arbol);
}

static void *abb_obtener_(const abb_nodo_t *raiz, const char *clave, abb_t* arbol){
    if(raiz==NULL)
        return NULL;
    if(arbol->cmp(clave, raiz->clave))
        return raiz->dato;
    if(arbol->cmp(clave, raiz->clave)<0){
        return abb_obtener_(raiz->izq, clave, arbol);
    }else{
        return abb_obtener_(raiz->der, clave, arbol);
    }
}

void* abb_obtener(const abb_t *arbol, const char *clave){
    return abb_obtener_(arbol->raiz, clave, arbol);
}

static bool abb_pertenece_(const abb_nodo_t *raiz, const char *clave, abb_t* arbol){
    if(raiz==NULL)
        return false;
    if(arbol->cmp(clave, raiz->clave))
        return true;
    if(arbol->cmp(clave, raiz->clave)<0){
        return abb_pertenece_(raiz->izq, clave, arbol);
    }else{
        return abb_pertenece_(raiz->der, clave, arbol);
    }
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    return abb_pertenece_(arbol->raiz, clave, arbol);
}

static size_t abb_cantidad_(const abb_nodo_t* raiz){
    if(raiz==NULL)
        return 0;
    size_t izq = abb_cantidad_(raiz->izq);
    size_t der = abb_cantidad_(raiz->der);
    return izq + der + 1;
}

size_t abb_cantidad(const abb_t *arbol){
    return abb_cantidad_(arbol->raiz);
}

static abb_destruir_(abb_nodo_t* raiz, abb_t* arbol){
    if(raiz!=NULL){
        abb_destruir_(raiz->izq, arbol);
        abb_destruir_(raiz->der, arbol);
        if(arbol->destruir_dato!=NULL);
            arbol->destruir_dato(raiz->dato);
        free(raiz);
        raiz=NULL;
    }
}

void abb_destruir(abb_t *arbol){
    return abb_destruir_(arbol->raiz, arbol);
}

void* abb_borrar(abb_t *arbol, const char *clave){
    
}