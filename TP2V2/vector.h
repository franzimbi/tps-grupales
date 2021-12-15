#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct vector vector_t;

vector_t* vector_crear();
void vector_destruir(vector_t* vector, void (*destruir_dato)(void *));
bool vector_agregar(vector_t* vector, void* dato);
size_t vector_tamano(vector_t* vector);
void* vector_obtener(vector_t* vector, size_t pos);

#endif
