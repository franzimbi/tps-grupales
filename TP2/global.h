#ifndef GLOBAL_H
#define GLOBAL_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct global global_t;

//crea una estructura global a partir de un archivo abierto con todos los nombres de usuario.
//post: devuelve un puntero a la estructura o NULL si fallo/
global_t* global_crear(FILE* f);

//destruye global y todos sus datos
void global_destruir(global_t* global);

//logea a un usuario si no hay ninguno logeado. caso contrario devuelve un error.
//pre: globar fue creada
bool usuario_login(global_t* global, char* usuario);

//hace logout a un usuario si hay alguno logeado. caso contrario devuelve un error.
//pre: globar fue creada
bool usuario_logout(global_t* global);

//realiza una publicacion disponible para todos en su feed. debe haber un usuario logeado
//pre: global fue creada
bool post_publicar(global_t* global, char* texto);


bool ver_siguiente_feed(global_t* global);
bool likear_post(global_t* global, long id_post);
bool mostrar_likes(global_t* global, long id_publicacion);

// - - -- - - - - - - - - - - -
char* leer_linea(FILE* f);

#endif