#include "hash.h"
#include <stdio.h>
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

// http://www.cse.yorku.ca/~oz/hash.html 
/*unsigned long djb2(unsigned char *str, size_t largo_hash){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

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
} */

static bool redimensionar_hash(hash_t* hash){
    elemento_t* tabla_nueva= malloc(sizeof(elemento_t) * hash->tamano_tabla * CONSTANTE_REDIMENSION);
    if(tabla_nueva==NULL) return false;
    hash->cantidad_elementos_acumulados = 0;
    size_t tamano_anterior = hash->tamano_tabla;
    hash->tamano_tabla = hash->tamano_tabla * CONSTANTE_REDIMENSION;

    for(size_t i=0; i<hash->tamano_tabla; i++){
        elemento_t* aux = &hash->tabla[i];
        if(aux->estado==OCUPADO){
            size_t nro_hasheo = (size_t) jenkins_one_at_a_time_hash(aux->clave, hash->tamano_tabla);
            hash_guardar(tabla_nueva, aux->clave, aux->dato);
            hash->cantidad_elementos_reales++;
        }
        hash->cantidad_elementos_acumulados++;
    }
    //hash_destruir(hash->tabla);
    elemento_t* aux = hash->tabla;
    tabla_destruir(aux, hash->destructor, tamano_anterior);
    hash->tabla=tabla_nueva;
    return true;
}

static bool copiar_a_posicion_hash(elemento_t* elemento, const char* clave, void* dato){
    elemento->clave = malloc(sizeof(char)* (strlen(clave)+1));
    if(elemento->clave==NULL) return false;

    strcpy(elemento->clave, clave);
    elemento->estado=OCUPADO;
    elemento->dato = dato;
    return true;
}

//a es el nro devulto por la funcion de hashing
static size_t encontrar_posicion(size_t a, hash_t* hash, const char* clave){
    if(hash->tabla[a].estado==VACIO || hash->tabla[a].estado==BORRADO)
        return a;
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
    size_t nro_hasheo = (size_t)jenkins_one_at_a_time_hash(clave, hash->tamano_tabla);

    if(((hash->cantidad_elementos_acumulados)/(float)(hash->tamano_tabla)) > 0.7)
        if(!redimensionar_hash(hash)) return false;

    nro_hasheo = encontrar_posicion(nro_hasheo, hash, clave);
    if(hash->tabla[nro_hasheo].estado==OCUPADO){
        hash->destructor(hash->tabla[nro_hasheo].dato);
        hash->tabla[nro_hasheo].dato = dato;
        return true;
    }
    if(!copiar_a_posicion_hash(&(hash->tabla[nro_hasheo]), clave, dato)) return false;
    hash->cantidad_elementos_acumulados++;
    hash->cantidad_elementos_reales++;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t aux = encontrar_posicion((size_t) jenkins_one_at_a_time_hash(clave,hash->tamano_tabla),hash, clave);
    void* dato = hash->tabla[aux].dato;
    hash->destructor(hash->tabla[aux].dato);
    hash->tabla[aux].estado = BORRADO;
    return dato;
}

bool tabla_destruir(elemento_t* elemento, hash_destruir_dato_t destruir, size_t largo){
    largo--;
    while(largo >= 0){
        if(elemento->estado==OCUPADO){
            if(destruir != NULL){
                destruir(elemento[largo].dato);
            }
        }
    }
    free(elemento);
}