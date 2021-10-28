#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CANTIDAD_INICIAL 10000
#define CONSTANTE_REDIMENSION 10

typedef enum {VACIO, OCUPADO, BORRADO} estado_t;

typedef struct{
    char* clave;
    void* dato;
    estado_t estado;
}elemento_t;

struct hash{
    elemento_t* tabla;
    size_t cantidad_elementos_acumulados;
    size_t cantidad_elementos_reales;
    size_t tamano_tabla;
    hash_destruir_dato_t destructor;
};

//https://en.wikipedia.org/wiki/Jenkins_hash_function lo encontramos en varias paginas y la recomendan bastante
uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t largo_hash){
    size_t i = 0;
    size_t length=strlen(key);
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash % largo_hash;
}

static size_t funcion_hashing(const char* clave, size_t largo_hash){
    return (size_t) jenkins_one_at_a_time_hash((const uint8_t*)clave, largo_hash);
}

static bool redimensionar_hash(hash_t* hash){
    hash_t* nuevo = malloc(sizeof(hash_t));
    if(nuevo==NULL) return false;

    nuevo->cantidad_elementos_acumulados=0;
    nuevo->cantidad_elementos_reales = 0;
    nuevo->tamano_tabla = hash->tamano_tabla * CONSTANTE_REDIMENSION;
    nuevo->destructor = hash->destructor;

    nuevo->tabla = malloc(sizeof(elemento_t) * nuevo->tamano_tabla);
    if(nuevo->tabla==false){
        free(nuevo);
        return false;
    }
    for(size_t i=0; i<nuevo->tamano_tabla; i++)
            nuevo->tabla[i].estado==VACIO;
    for(size_t i=0; i<hash->tamano_tabla; i++){
        if(hash->tabla[i].estado==OCUPADO){
            size_t nro_hasheo = funcion_hashing(hash->tabla[i].clave, hash->tamano_tabla);
            nro_hasheo = encontrar_posicion(nro_hasheo, nuevo, hash->tabla[i].clave);
            if(!copiar_a_posicion_hash(nro_hasheo, nuevo, hash->tabla[i].clave, hash->tabla[i].dato)){
                hash_destruir(nuevo);
                return false;
            }
        }
        if(nuevo->cantidad_elementos_reales==hash->cantidad_elementos_reales)
            break;
    }
    hash->destructor = NULL;
    hash_destruir(hash);
    hash = nuevo;
    return true;
}

//copia a posicion el nuevo dato o lo reemplaza
static bool copiar_a_posicion_hash(size_t posicion, hash_t* hash, char* clave, void* dato){
    if(hash->tabla[posicion].estado==OCUPADO){
        hash->destructor(hash->tabla[posicion].dato);
        hash->tabla[posicion].dato = dato;
        return true;
    }
    hash->tabla[posicion].clave = malloc(sizeof(char)* (strlen(clave)+1));
    if(hash->tabla[posicion].clave==NULL) return false;

    strcpy(hash->tabla[posicion].clave, clave);
    hash->tabla[posicion].estado=OCUPADO;
    hash->tabla[posicion].dato = dato;
    hash->cantidad_elementos_acumulados++;
    hash->cantidad_elementos_reales++;
    return true;
}

//a es el nro devulto por la funcion de hashing
static size_t encontrar_posicion(size_t a, hash_t* hash, const char* clave){
    while(hash->tabla[a].estado==OCUPADO){
        if(strcmp(hash->tabla[a].clave, clave))
            return a;
        a++;
        if(a==hash->tamano_tabla)
            a=0;
    }
    return a;
}


//------------------------------------------------------ FUNCIONES DEL TDA ----------------------------------------------------------------------

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* nuevo=malloc(sizeof(hash_t));
    if(nuevo==NULL) return NULL;

    nuevo->tabla=malloc(sizeof(elemento_t) * CANTIDAD_INICIAL);
    if(nuevo->tabla==NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->cantidad_elementos_reales = 0;
    nuevo->cantidad_elementos_acumulados = 0;
    nuevo->tamano_tabla = CANTIDAD_INICIAL;
    nuevo->destructor = destruir_dato;

    for(size_t i=0; i<CANTIDAD_INICIAL; i++){
        nuevo->tabla[i].estado=VACIO;
    }
    return nuevo;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    size_t nro_hasheo = funcion_hashing(clave, hash->tamano_tabla);
    if(((hash->cantidad_elementos_acumulados)/(float)(hash->tamano_tabla)) > 0.7)
        if(!redimensionar_hash(hash)) return false;

    nro_hasheo = encontrar_posicion(nro_hasheo, hash, clave);
    if(hash->tabla[nro_hasheo].estado==OCUPADO){
        hash->destructor(hash->tabla[nro_hasheo].dato);
        hash->tabla[nro_hasheo].dato = dato;
        return true;
    }
    if(!copiar_a_posicion_hash(nro_hasheo, hash, clave, dato)) return false;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t aux = encontrar_posicion(funcion_hashing(clave,hash->tamano_tabla),hash, clave);
    if(hash->tabla[aux].estado==OCUPADO){
        void* dato = hash->tabla[aux].dato;
        hash->tabla[aux].estado=BORRADO;
        return dato;
    }
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    size_t nro_hasheo = funcion_hashing(clave, hash->tamano_tabla);
    return hash->tabla[nro_hasheo].estado==OCUPADO ? hash->tabla[nro_hasheo].dato : NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    size_t nro_hasheo = funcion_hashing(clave, hash->tamano_tabla);
    return hash->tabla[nro_hasheo].estado==OCUPADO;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad_elementos_reales;
}

void hash_destruir(hash_t *hash){
    for(size_t i=0; i<hash->tamano_tabla; i++){
        if(hash->tabla[i].estado==OCUPADO){
            if(hash->destructor!=NULL)
                hash->destructor(hash->tabla[i].dato);
        }
    }
    free(hash->tabla);
    free(hash);
}