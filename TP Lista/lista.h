#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

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

// Si la lista tiene elementos, se quita el primero de la lista y
// se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos.
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
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

//itera toda la lista aplicandole la funcion visitar elemento a elemento mientras
//mientras que esta devuelva true. corta la iteracion cuando visitar devuelve false o 
//cuando ya se itero toda la lista.
//pre: la lista fue creada.
//post: se le aplico visitar a todos los elementos iterados
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

//crea un iterador para una lista. este empieza en el primer elemento de la lista.
//pre: la lista fue creada.
//post: devuelve el iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

//avanza al siguiente elemento de la lista. si ya no puede avanzar devuelve false.
//pre: el iterador y la lista fueron creados.
//post: el iterador avanzo al siguiente elemento o quedo en  el final.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del  elemento actual de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista y el iterador fueron creados.
// Post: se devolvió el elemento actual de la lista, cuando no está vacía.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//devuelve true si esta al final de la lista, sino devuelve false.
//pre: la lista y el iterador fueron creados.
//post: la lista y el iterador sigue igual.
bool lista_iter_al_final(const lista_iter_t *iter);

//destruye el iterador.
//pre: la lista y el iterador fueron creados.
//post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

//inserta un nuevo elemento en la posicion actual de la lista y devuelve true. si no se pudo
//devuelve false.
//pre: la lista y el iterador fueron creados.
//post: se agrego el elemento nuevo y el iterador sigue en la misma posicion.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//borra el elemento en la posicion actual de la lista y lo devuelve.
//pre: la lista y el iterador fueron creados.
//post: se borro el elemento de la lista y se devolvio.
void *lista_iter_borrar(lista_iter_t *iter);

#endif