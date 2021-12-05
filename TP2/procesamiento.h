#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <stdbool.h>
#include "hash.h"
#include "global.h"

typedef bool (*comando_t)(global_t*);

char* leer_linea();
hash_t* iniciar_diccionario();
void cerrar_diccionario(hash_t* diccionario);
comando_t buscar_comando(hash_t* diccionario, char* clave);
//bool string_a_nro(char* str, long* nro);

#endif