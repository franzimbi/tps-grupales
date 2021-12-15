#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <stdbool.h>
#include "hash.h"
#include "global.h"

typedef status_t (*comando_t)(global_t*);

char* leer_linea();
hash_t* iniciar_diccionario();
void cerrar_diccionario(hash_t* diccionario);
comando_t buscar_comando(hash_t* diccionario, char* clave);


#endif