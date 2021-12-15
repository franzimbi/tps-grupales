#ifndef GLOBAL_H
#define GLOBAL_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct global global_t;
typedef enum {TODO_OK, USUARIO_YA_LOGEADO, USUARIO_INEXISTENTE, USUARIO_NO_LOGEADO, FEED_VACIO, NO_LOGEADO_O_POST_INEXISTENTE, SIN_LIKES_O_POST_INEXISTENTE, POST_SIN_LIKES_O_INEXISTENTE} status_t;

typedef struct{
    char *mensaje;
}mensajes_error;

const mensajes_error tabla_error[] = {  [TODO_OK]={"todo ok"}, 
                                        [USUARIO_YA_LOGEADO]={"Error: Ya habia un usuario loggeado\n"}, 
                                        [USUARIO_INEXISTENTE]={"Error: usuario no existente\n"},
                                        [USUARIO_NO_LOGEADO]={"Error: no habia usuario loggeado\n"},
                                        [FEED_VACIO]={"Usuario no loggeado o no hay mas posts para ver\n"}, 
                                        [NO_LOGEADO_O_POST_INEXISTENTE]={"Error: Usuario no loggeado o Post inexistente\n"}, 
                                        [POST_SIN_LIKES_O_INEXISTENTE]={"Error: Post inexistente o sin likes\n"}
                                     };

//crea una estructura global a partir de un archivo abierto con todos los nombres de usuario.
//post: devuelve un puntero a la estructura o NULL si fallo/
global_t* global_crear(FILE* f);

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

// - - -- - - - - - - - - - - -
char* leer_linea(FILE* f);

#endif