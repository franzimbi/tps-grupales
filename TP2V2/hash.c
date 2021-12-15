#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define CANTIDAD_INICIAL 1000
#define CONSTANTE_AUMENTO_DE_TABLA 10 //aumenta cte veces
#define CONSTANTE_DISMINUCION_DE_TABLA 2 //se achica a 1/cte

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

struct hash_iter{
    long actual;
    const struct hash* hash;
};

//https://en.wikipedia.org/wiki/Jenkins_hash_function lo encontramos en varias paginas y la recomendan bastante
static uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length){
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

static size_t funcion_hashing(const char* clave, size_t largo_hash){
    return (size_t) jenkins_one_at_a_time_hash((const uint8_t*)clave, strlen(clave)) % largo_hash;
}


static bool copiar_a_posicion_hash(size_t posicion, hash_t* hash, const char* clave, void* dato){
    if(hash->tabla[posicion].estado==OCUPADO){
        if(hash->destructor!=NULL)
        hash->destructor(hash->tabla[posicion].dato);
        hash->tabla[posicion].dato = dato;
        return true;
    }
    hash->tabla[posicion].clave = malloc(sizeof(char)* (strlen(clave)+1));
    if(hash->tabla[posicion].clave==NULL) return false;

    if(hash->tabla[posicion].estado==VACIO)
        hash->cantidad_elementos_acumulados++;

    strcpy(hash->tabla[posicion].clave, clave);
    hash->tabla[posicion].estado=OCUPADO;
    hash->tabla[posicion].dato = dato;
    hash->cantidad_elementos_reales++;
    return true;
}

//a es el nro devulto por la funcion de hashing
static size_t encontrar_posicion(size_t posicion, elemento_t* tabla, size_t tamano_tabla, const char* clave){
    while(tabla[posicion].estado==OCUPADO || tabla[posicion].estado==BORRADO){
    if(tabla[posicion].estado==OCUPADO){
        if(strcmp(tabla[posicion].clave, clave)==0)
            return posicion;
    } 
    posicion++;
    if(posicion==tamano_tabla)
        posicion=0;
    }
    return posicion;
}


static bool redimensionar_hash(hash_t* hash, size_t tamano_nuevo){
    elemento_t* nueva_tabla = malloc(sizeof(elemento_t)* tamano_nuevo);
    if(nueva_tabla==NULL) return false;
    hash->cantidad_elementos_acumulados = 0;
    hash->cantidad_elementos_reales = 0;
    for(size_t i=0; i<(tamano_nuevo); i++){
        nueva_tabla[i].estado=VACIO;
    }
    for(size_t i=0; i<hash->tamano_tabla; i++){
        if(hash->tabla[i].estado==OCUPADO){
            size_t nro_hasheo =funcion_hashing(hash->tabla[i].clave, tamano_nuevo);
            nro_hasheo = encontrar_posicion(nro_hasheo, nueva_tabla, tamano_nuevo, hash->tabla[i].clave);
            nueva_tabla[nro_hasheo].estado=OCUPADO;
            nueva_tabla[nro_hasheo].clave = hash->tabla[i].clave;
            nueva_tabla[nro_hasheo].dato = hash->tabla[i].dato;
            hash->cantidad_elementos_acumulados++;
            hash->cantidad_elementos_reales ++;
        }
    }
    hash->tamano_tabla = tamano_nuevo;
    free(hash->tabla);
    hash->tabla = nueva_tabla;
    return true;
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
    if(((float)(hash->cantidad_elementos_acumulados)/(float)(hash->tamano_tabla)) > (float)0.7)
        if(!redimensionar_hash(hash, hash->tamano_tabla * CONSTANTE_AUMENTO_DE_TABLA)) return false;
    size_t nro_hasheo = encontrar_posicion(funcion_hashing(clave, hash->tamano_tabla), hash->tabla, hash->tamano_tabla, clave);
    if(!copiar_a_posicion_hash(nro_hasheo, hash, clave, dato)) return false;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t nro_hasheo = encontrar_posicion(funcion_hashing(clave, hash->tamano_tabla), hash->tabla, hash->tamano_tabla, clave);
    if(hash->tabla[nro_hasheo].estado==OCUPADO){
        void* dato = hash->tabla[nro_hasheo].dato;
        hash->tabla[nro_hasheo].estado=BORRADO;
        free(hash->tabla[nro_hasheo].clave);
        hash->cantidad_elementos_reales --;
        if((hash->cantidad_elementos_acumulados - hash->cantidad_elementos_reales)>(hash->tamano_tabla/3))
            redimensionar_hash(hash, hash->tamano_tabla / CONSTANTE_DISMINUCION_DE_TABLA);
        return dato;
    }
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    size_t nro_hasheo = encontrar_posicion(funcion_hashing(clave, hash->tamano_tabla),hash->tabla,hash->tamano_tabla,clave);
    return hash->tabla[nro_hasheo].estado==OCUPADO ? hash->tabla[nro_hasheo].dato : NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    size_t nro_hasheo = encontrar_posicion(funcion_hashing(clave, hash->tamano_tabla),hash->tabla,hash->tamano_tabla,clave);
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
            free(hash->tabla[i].clave);
        }
    }
    free(hash->tabla);
    free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* iterador=malloc(sizeof(hash_iter_t));
    if(iterador==NULL) return NULL;

    iterador->hash = hash;
    iterador->actual = -1;
    hash_iter_avanzar(iterador);
    return iterador;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if(hash_iter_al_final(iter)) return false;
    size_t i;
    for(i=iter->actual+1; i<iter->hash->tamano_tabla; i++)
        if(iter->hash->tabla[i].estado==OCUPADO) break;
    iter->actual = i;
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    return hash_iter_al_final(iter) ? NULL : (const char*) iter->hash->tabla[iter->actual].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->actual==iter->hash->tamano_tabla;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}
