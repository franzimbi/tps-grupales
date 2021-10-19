#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct lista lista_t;

//crea una lista.
//post: devuelve una lista vacia.
lista_t *lista_crear(void);
//devuelve verdadero si la lista no tiene elementos. en caso contrario devuelve falso,
//pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);
//agrega un elemento al principio de la lista. devuelve falso en caso de error.
//pre: la lista fue creada.
//post: se agrego el nuevo dato a la lista, esta esta en el primer lugar.
bool lista_insertar_primero(lista_t *lista, void *dato);
//agrega un elemento al final de la lista. devuelve falso en caso de error.
//pre: la lista fue creada.
//post: se agrego el nuevo dato a la lista, esta esta en el ultimo lugar.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

void *lista_borrar_primero(lista_t *lista);
void *lista_ver_primero(const lista_t *lista);
void *lista_ver_ultimo(const lista_t* lista);
size_t lista_largo(const lista_t *lista);
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


#endif