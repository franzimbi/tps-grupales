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

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve la cantidad de elementos en la lista.
// Pre: la cola fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


#endif