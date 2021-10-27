#include "hash.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CANTIDAD_INICIAL 100

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
};

static bool redimensionar_hash(hash_t* hash){
    
}

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

    for(size_t i=0; i<CANTIDAD_INICIAL; i++){
        nuevo->tabla[i].estado=VACIO;
    }
    return nuevo;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){

    int hash= (int)jenkins_one_at_a_time_hash(clave, hash->tamano_tabla);

    if(((hash->cantidad_elementos_acumulados)/(float)(hash->tamano_tabla)) > 0.7)
        redimensionar_hash(hash);
}


