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
};

struct abb_iter{
    pila_t* pila;
    abb_nodo_t* raiz;
};

static abb_nodo_t* nodo_crear(char* clave, void* dato){
    abb_nodo_t* nuevo=malloc(sizeof(abb_nodo_t));
    if(nuevo==NULL) return NULL;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    nuevo->clave=malloc(sizeof(char)*(strlen(clave)+1));
    if(nuevo->clave==NULL){
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
    nodo=NULL;
    return aux;
}



abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* nuevo=malloc(sizeof(abb_t));
    if(nuevo==NULL) return NULL;    

    nuevo->raiz=NULL;
    nuevo->cmp = cmp;
    nuevo->destruir_dato = destruir_dato;
    return nuevo;
}

static bool abb_guardar_(abb_nodo_t** raiz, const char *clave, void *dato, abb_t* arbol){
    if(*raiz==NULL){
        *raiz = nodo_crear((char*)clave, dato);
        if((*raiz)==NULL) return false;
        return true;
    }

    if(arbol->cmp(clave, (*raiz)->clave) == 0){
        if(arbol->destruir_dato!= NULL)
            arbol->destruir_dato((*raiz)->dato);
        (*raiz)->dato=dato;
    }
    
    //fprintf(stderr,"seguro la palma aca\n");
    abb_nodo_t** aux = &(*raiz);
    if(arbol->cmp(clave, (*raiz)->clave)<0){
        return abb_guardar_(&(*aux)->izq, clave, dato, arbol);
    }else{
        return abb_guardar_(&(*aux)->der, clave, dato, arbol);
    }
    
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    abb_nodo_t** aux = &(arbol)->raiz;
    return abb_guardar_(aux, clave, dato, arbol);
}

static void *abb_obtener_(const abb_nodo_t *raiz, const char *clave, const abb_t* arbol){
    if(raiz==NULL)
        return NULL;
    if(arbol->cmp(clave, raiz->clave) == 0)
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

static bool abb_pertenece_(const abb_nodo_t *raiz, const char *clave, const abb_t* arbol){
    if(raiz==NULL)
        return false;
    if(arbol->cmp(clave, raiz->clave) == 0)
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
    if(arbol->raiz == NULL){
        return 0;
    }
    //fprintf(stderr,"aca seguro\n");
    return abb_cantidad_(arbol->raiz);
}

static void abb_destruir_(abb_nodo_t* raiz, abb_t* arbol){
    if(raiz==NULL)
        return;
    abb_destruir_(raiz->izq, arbol);
    abb_destruir_(raiz->der, arbol);
    void* dato = nodo_destruir(raiz);
    if(arbol->destruir_dato!=NULL)
        arbol->destruir_dato(dato);
    raiz=NULL;
}

void abb_destruir(abb_t *arbol){
    abb_destruir_(arbol->raiz, arbol);
    free(arbol);
}

static abb_nodo_t* nodo_todo_der(abb_nodo_t** raiz, abb_nodo_t** padre){
    if((*raiz)->der==NULL){       
        abb_nodo_t** aux = &(*raiz);
        if((*raiz)->izq!=NULL)
            (*padre)->der = (*raiz)->izq;
        
        if((*padre)->der!=NULL){
            return *aux;
        }

        else (*padre)->der = NULL;
        return *aux;
    }
    *padre = *raiz;
    return nodo_todo_der(&(*raiz)->der, &(*padre));
}

static void* abb_borrar_(abb_nodo_t** raiz, const char *clave, abb_t* arbol, abb_nodo_t** padre){
    if(*raiz==NULL)
        return NULL;

    fprintf(stderr,"ESTO ES RAIZ IZQ %p\n\n ESTO ES RAIZ DER %p\n\n",(*raiz)->izq, (*raiz)->der);
     
     if((*raiz)->izq!=NULL && (*raiz)->der!=NULL){
         fprintf(stderr,"ESTO ES RAIZ IZQ %s\n\n ESTO ES RAIZ DER %s\n\n",(char*) (*raiz)->izq->dato,(char*) (*raiz)->der->dato);
     }
    if(arbol->cmp(clave, (*raiz)->clave) == 0){
        //fprintf(stderr, "aca\n");
        if((*raiz)->izq==NULL && (*raiz)->der==NULL){
            fprintf(stderr, "AMBOS == NULL\n\n");
            void* dato = nodo_destruir(*raiz); 
            *raiz = NULL;
            return dato;
        }
        if((*raiz)->izq==NULL){
            fprintf(stderr, "IZQUIERDA == NULL\n\n");
            abb_nodo_t* reemplazo = (*raiz)->der;
            void* dato = nodo_destruir(*raiz);
            *raiz = reemplazo;
            return dato;
        }
        if((*raiz)->der==NULL){
            fprintf(stderr, "DERECHA == NULL\n\n");
            abb_nodo_t* reemplazo = (*raiz)->izq;
            void* dato = nodo_destruir(*raiz);
            *raiz = reemplazo;
            return dato;
        }
        if((*raiz)->izq!=NULL && (*raiz)->der!=NULL){
            fprintf(stderr, "LA FARLOPA\n\n");
            abb_nodo_t* reemplazo_de_borrado = nodo_todo_der(&(*raiz)->izq, &(*raiz));           
            abb_nodo_t* izq = (*raiz)->izq;
            abb_nodo_t* der = (*raiz)->der;
            
            fprintf(stderr, "ANTES DEL DESTRUIR\n\n");
            fprintf(stderr,"RDB: %p\n",reemplazo_de_borrado);
            fprintf(stderr,"RDB DATO: %s\n",(char*)reemplazo_de_borrado->dato);
            fprintf(stderr,"IZQ: %p\n",izq);
            fprintf(stderr,"IZQ DATO: %s\n",(char*)izq->dato);
            fprintf(stderr,"DER: %p\n",der);
            fprintf(stderr,"DER DATO: %s\n",(char*)der->dato);

            void * dato = nodo_destruir(*raiz);

            fprintf(stderr, "\nDESP DEL DESTRUIR\n\n");

            fprintf(stderr,"RDB: %p\n",reemplazo_de_borrado);
            fprintf(stderr,"RDB DATO: %s\n",(char*)reemplazo_de_borrado->dato);
            fprintf(stderr,"IZQ: %p\n",izq);
            fprintf(stderr,"IZQ DATO: %s\n",(char*)izq->dato);
            fprintf(stderr,"DER: %p\n",der);
            fprintf(stderr,"DER DATO: %s\n",(char*)der->dato);

            if((reemplazo_de_borrado) != (izq))
            (reemplazo_de_borrado)->izq = (izq);
            if((reemplazo_de_borrado) != (der))
            (reemplazo_de_borrado)->der = (der);

            fprintf(stderr,"PADRE: %p\n",padre);
            fprintf(stderr,"PADRE DATO: %s\n",(char*)(*padre)->dato);

            abb_nodo_t ** reaux = (abb_nodo_t **) &reemplazo_de_borrado;

            if((*padre)->dato > reemplazo_de_borrado->dato){
                (*padre)->izq = *reaux;
            } 
            else (*padre)->der = *reaux;

            fprintf(stderr,"PADRE: %p\n",padre);
            fprintf(stderr,"PADRE DATO: %s\n",(char*)(*padre)->dato);
            
            fprintf(stderr,"PADRE IZQ DATO: %s\n",(char*)(*padre)->izq->dato);
            
            fprintf(stderr,"PADRE IZQ DER DATO: %s\n",(char*)(*padre)->izq->der->dato);
            
            fprintf(stderr,"PADRE DATO: %p\n",(char*)(*padre)->izq->izq);
            return dato;
        }
    }
    fprintf(stderr, "deberia seguir\n\n");

    abb_nodo_t** aux = &(*raiz);
    if(arbol->cmp(clave, (*raiz)->clave)<0){
        return abb_borrar_(&(*aux)->izq, clave, arbol,aux);
    }else{
        return abb_borrar_(&(*aux)->der, clave, arbol,aux);
    }
}

void* abb_borrar(abb_t *arbol, const char *clave){
    abb_nodo_t** aux = &(arbol)->raiz;
    abb_nodo_t** aux2 = &(arbol)->raiz;
    return abb_borrar_(aux, clave, arbol,aux2);
}

//- - - - - - - - - - - - - - - - - - - - - - - ITERADORES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
static void abb_in_order_(abb_nodo_t *raiz, bool visitar(const char *, void *, void *), void *extra){
    if(raiz==NULL)
        return;

    abb_in_order_(raiz->izq, visitar, extra);
    if(!visitar(raiz->clave, raiz->dato, extra)) return;
    abb_in_order_(raiz->der, visitar, extra);
}
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    return abb_in_order_(arbol->raiz, visitar, extra);
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

    while(raiz!=NULL){
        pila_apilar(iter->pila, raiz);
        raiz = raiz->izq;
    }
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
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;
    abb_nodo_t* aux = pila_desapilar(iter->pila);
    if(aux->der!=NULL){
        aux = aux->der;
        while(aux!=NULL){
            pila_apilar(iter->pila, aux);
            aux = aux->izq;
        }
    }
    return true;
}