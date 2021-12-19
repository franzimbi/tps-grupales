#ifndef GLOBAL_H
#define GLOBAL_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct global global_t;
typedef enum {TODO_OK, 
                USUARIO_YA_LOGEADO,
                USUARIO_INEXISTENTE, 
                USUARIO_NO_LOGEADO,
                FEED_VACIO,
                NO_LOGEADO_O_POST_INEXISTENTE,
                POST_SIN_LIKES_O_INEXISTENTE,
                ERROR_MEMORIA} status_t;

typedef char* (users_function);

//crea una estructura global a partir de un archivo abierto con todos los nombres de usuario.
//post: devuelve un puntero a la estructura o NULL si fallo/
global_t* global_crear(users_function function);

//destruye global y todos sus datos
void global_destruir(global_t* global);

//logea a un usuario si no hay ninguno logeado. caso contrario devuelve un error.
//pre: globar fue creada
status_t usuario_login(global_t* global, char* usuario);

//hace logout a un usuario si hay alguno logeado. caso contrario devuelve un error.
//pre: globar fue creada
status_t usuario_logout(global_t* global);

//realiza una publicacion disponible para todos en su feed. debe haber un usuario logeado
//pre: global fue creada
status_t post_publicar(global_t* global, char* texto);

status_t ver_siguiente_feed(global_t* global);
status_t likear_post(global_t* global, long id_post);
status_t mostrar_likes(global_t* global, long id_publicacion);

#endif