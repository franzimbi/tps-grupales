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

// http://www.cse.yorku.ca/~oz/hash.html 
unsigned long djb2(unsigned char *str, size_t largo_hash){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % largo_hash;
}

//https://stackoverflow.com/questions/7666509/hash-function-for-string
uint32_t MurmurOAAT32 ( const char * key, size_t largo_hash){
    uint32_t h=3323198485ul;
    for (;*key;++key){
        h ^= *key;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % largo_hash;
}

static bool redimensionar_hash(hash_t* hash){
    hash_t* hash_nuevo=malloc(sizeof(hash_t));
    if(hash_nuevo==NULL) return false;

    hash_nuevo->tabla= malloc(sizeof(elemento_t) * hash->tamano_tabla *2);

    hash_nuevo->cantidad_elementos_reales=hash->cantidad_elementos_reales;
    hash_nuevo->cantidad_elementos_acumulados = 0;
    hash_nuevo->tamano_tabla = hash->tamano_tabla * 2;
    hash_nuevo->destructor = hash->destructor;

    for(size_t i=0; i<hash->tamano_tabla; i++){
        elemento_t aux = hash->tabla[i];
        if(aux.estado==OCUPADO){
            if(!hash_guardar(hash_nuevo, hash->tabla[i].clave, hash->tabla[i].dato)){
                    hash_destruir(hash_nuevo);
                    return false;
                }
        hash_nuevo->cantidad_elementos_acumulados++;
        }
    }
    hash_destruir(hash);
    hash=hash_nuevo;
    return true;
}

static bool copiar_a_hash(size_t posicion, hash_t* hash, const char* clave, void* dato){
    hash->tabla[posicion].clave = malloc(sizeof(char)* (strlen(clave)+1));
    if(hash->tabla[posicion].clave==NULL) return false;

    strcpy(hash->tabla[posicion].clave, clave);
    hash->tabla[posicion].estado=OCUPADO;
    hash->tabla[posicion].dato = dato;
    hash->cantidad_elementos_acumulados++;
        hash->cantidad_elementos_reales++;
    return true;
}

static size_t encontrar_posicion(size_t a, size_t b, size_t c, hash_t* hash, const char* clave){
    if(hash->tabla[a].estado==OCUPADO)
        if(strcmp(hash->tabla[a].clave, clave))
            return a;
    if(hash->tabla[b].estado==OCUPADO)
        if(strcmp(hash->tabla[b].clave, clave))
            return b;
    if(hash->tabla[c].estado==OCUPADO)
        if(strcmp(hash->tabla[c].clave, clave))
            return c;
    if(hash->tabla[a].estado==VACIO || hash->tabla[a].estado==BORRADO)
        return a;
    if(hash->tabla[b].estado==VACIO || hash->tabla[b].estado==BORRADO)
        return b;
    if(hash->tabla[c].estado==VACIO || hash->tabla[c].estado==BORRADO)
        return c;
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
    size_t hash1 = (size_t)jenkins_one_at_a_time_hash(clave, hash->tamano_tabla);
    size_t hash2 = (size_t)djb2(clave, hash->tamano_tabla);
    size_t hash3 = (size_t)MurmurOAAT32(clave, hash->tamano_tabla);

    if(((hash->cantidad_elementos_acumulados)/(float)(hash->tamano_tabla)) > 0.7)
        redimensionar_hash(hash);

    size_t posicion = encontrar_posicion(hash1, hash2, hash3, hash, clave);

    if(hash->tabla[posicion].estado==OCUPADO){
        hash->tabla[posicion].dato = dato;
    }else
        return copiar_a_hash(posicion, hash, clave, dato);
}

void *hash_borrar(hash_t *hash, const char *clave){

}




