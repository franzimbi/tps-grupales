#include <stdlib.h>
#include "global.h"
#include "vector.h"
#include "hash.h"
#include "usuarios.h"
#include "post.h"
#include "abb.h"
#include "procesamiento.h"

#define CANTIDAD_INICIAL 30

struct global{
    vector_t* vector_usr;
    hash_t* hash_usr;
    //vector_t* vector_likes; //guarda abb con los likes de cada post segun su id
    vector_t* vector_posts;
    size_t id_post_global;
    usuario_t* login;
};

//--------------------------------------------------------------------------------------------

static bool print_clave(const char* clave, void* _, void* __){
    printf("\t%s\n", clave);
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

global_t* global_crear(users_function lectura_usuario, FILE* f){
    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->vector_usr = vector_crear();
    if(nuevo->vector_usr == NULL){
        free(nuevo);
        return NULL;
    }
    char* nombre;
    while(  (nombre = lectura_usuario(f)) != NULL ){
        usuario_t* nuevo_usuario = usuario_crear(nombre, vector_tamano(nuevo->vector_usr));
        if(nuevo_usuario == NULL){
            vector_destruir (nuevo->vector_usr, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
        if(!vector_agregar(nuevo->vector_usr, (void*) nuevo_usuario)){
            vector_destruir(nuevo->vector_usr, (void (*) (void *)) usuario_destruir);
            free(nuevo);
            return NULL;
        }
        free(nombre);
    }
    nuevo->hash_usr = hash_crear(NULL);
    for (size_t i = 0; i < vector_tamano(nuevo->vector_usr); i++){
        hash_guardar(nuevo->hash_usr,usuario_ver_nombre(vector_obtener(nuevo->vector_usr, i)), vector_obtener(nuevo->vector_usr, i));
    }
    nuevo->vector_posts = vector_crear();
    if(nuevo->vector_posts == NULL){
        vector_destruir(nuevo->vector_usr, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usr, NULL);
        free(nuevo);
        return NULL;
    }
    nuevo->id_post_global = 0;
    nuevo->login = NULL;
    return nuevo;
}

void global_destruir(global_t* global){
    vector_destruir(global->vector_usr, (void (*) (void*)) usuario_destruir);
    vector_destruir(global->vector_posts, (void (*) (void*)) publicacion_destruir);
    hash_destruir(global->hash_usr);
    free(global);
}

//true -> usuario logeado - false -> sin logear
static bool usuario_logeado(global_t* global){
    return global->login != NULL;
}

status_t usuario_login(global_t* global, char* usuario){
    if(usuario_logeado(global)){
        return USUARIO_YA_LOGEADO;
    }
    usuario_t* usr_logeado = hash_obtener(global->hash_usr, usuario);
    if(usr_logeado == NULL){
        return USUARIO_INEXISTENTE;
    }
    global->login = usr_logeado;
    printf("Hola %s\n", usuario_ver_nombre(usr_logeado));
    return TODO_OK;
}

status_t usuario_logout(global_t* global){
    if(!usuario_logeado(global)){
        return USUARIO_NO_LOGEADO;
    }    
    global->login = NULL;
    printf("Adios\n");
    return TODO_OK;
}

status_t post_publicar(global_t* global, char* texto){
    if(!usuario_logeado(global)){
        return USUARIO_NO_LOGEADO;
    }
    publicacion_t* nuevo_post = publicacion_nueva(global->id_post_global, texto, usuario_ver_id(global->login));
    if(nuevo_post == NULL) return ERROR_MEMORIA;

    if(!vector_agregar(global->vector_posts, (void*) nuevo_post)){
        publicacion_destruir(nuevo_post);
        return ERROR_MEMORIA;
    }

    for(size_t i=0; i<vector_tamano(global->vector_usr); i++){
        if(usuario_ver_id( (const usuario_t*) (global->login)) == usuario_ver_id( (const usuario_t*) vector_obtener(global->vector_usr, i)) )
            continue; 
        if( !usuario_guardar_publicacion(vector_obtener(global->vector_usr, i), nuevo_post, usuario_ver_id(global->login)) ){
            publicacion_destruir(nuevo_post);
            return ERROR_MEMORIA;
        }
    }
    global->id_post_global ++;
    printf("Post publicado\n");
    return TODO_OK;
}

status_t ver_siguiente_feed(global_t* global){
    if(feed_esta_al_final(global->login) || !usuario_logeado(global)){ 
        return FEED_VACIO;
    }
    size_t id_post = usuario_ver_siguiente_publicacion(global->login);
    printf("Post ID %zu\n", id_post);
    printf("%s dijo: %s\n", usuario_ver_nombre(vector_obtener(global->vector_usr, publicacion_ver_id_creador( vector_obtener(global->vector_posts, id_post) ) ) ),
                                    publicacion_ver_mensaje( vector_obtener(global->vector_posts, id_post) ) );
    printf("Likes: %zu\n", likes_publicacion(vector_obtener(global->vector_posts, id_post)));
    return TODO_OK;
}

status_t likear_post(global_t* global, long id_post){
    if(!usuario_logeado(global) || id_post <0 || id_post >= global->id_post_global){
        return NO_LOGEADO_O_POST_INEXISTENTE;
    }

    likear_publicacion(vector_obtener(global->vector_posts, id_post), usuario_ver_nombre(global->login));
    printf("Post likeado\n");
    return TODO_OK;
}

status_t mostrar_likes(global_t* global, long id_post){
    if( id_post<0 || id_post >= global->id_post_global ){
        return POST_SIN_LIKES_O_INEXISTENTE;
    }
    size_t cantidad_likes = likes_publicacion(vector_obtener(global->vector_posts, id_post));
    if(cantidad_likes == 0){
        return POST_SIN_LIKES_O_INEXISTENTE;
    }
    printf("El post tiene %zu likes:\n", cantidad_likes);
    printear_likes(vector_obtener(global->vector_posts, id_post), print_clave);
    return TODO_OK;
}
