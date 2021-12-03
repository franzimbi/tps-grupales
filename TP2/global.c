#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "hash.h"
#include "usuarios.h"
#include "post.h"
#include "abb.h"

#define CANTIDAD_INICIAL 30

struct vector{
    void** datos;
    size_t tamano;
    size_t capacidad;
};

struct global{
    vector_t* vector_usr;
    hash_t* hash_usr;
    vector_t* vector_likes; //guarda abb con los likes de cada post segun su id
    vector_t* vector_posts;
    size_t id_post_global;
    usuario_t* login;
};

struct post_con_prioridad{
    size_t id_publicacion;
    long prioridad;
};

//- - - - - - - - - - - - -  - - - - VECTOR DINAMICO - - - - - - - - - - - - - - - - - - - - 
static vector_t* vector_crear(size_t tam){
    vector_t* nuevo = malloc(sizeof(vector_t));
    if(nuevo == NULL) return NULL;
    nuevo->datos = malloc(sizeof(void*) * tam);
    if(nuevo->datos == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->tamano = 0;
    nuevo->capacidad = tam;
    return nuevo;
}

void vector_destruir(vector_t* vector, void (*destruir_dato)(void *)){
    for(size_t i=0; i<vector->tamano; i++){
        if(destruir_dato == NULL)
            break;
        destruir_dato(vector->datos[i]);
    }
    free(vector->datos);
    free(vector);
}

static bool vector_redimensionar(vector_t* vector, size_t nuevo_tamano){
    void** aux = realloc(vector->datos, sizeof(void*) * nuevo_tamano);
    if(aux == NULL){
        return false;
    }
    vector->datos = aux;
    vector->capacidad = nuevo_tamano;
    return true;
}

static bool vector_agregar(vector_t* vector, void* dato){
    if(vector->tamano == vector->capacidad)
        if(!vector_redimensionar(vector, (vector->tamano)*2)) return false;
    vector->datos[vector->tamano] = dato;
    vector->tamano ++;
    return true;
}

static size_t vector_tamano(vector_t* vector){
    return vector->tamano;
}

static void* vector_obtener(vector_t* vector, size_t pos){
    return vector->datos[pos];
}

static post_con_prioridad_t* post_con_prioridad_crear(size_t id_post, size_t id_creador, size_t id_lector){
    post_con_prioridad_t* p_prioridad = malloc(sizeof (post_con_prioridad_t));
    if(p_prioridad == NULL) return NULL;
    
    long dif_id = id_creador - id_lector;
    if(dif_id > 0)
        dif_id *= -1;
    
    p_prioridad->id_publicacion = id_post;
    p_prioridad->prioridad = /*(size_t)*/ dif_id;
    return p_prioridad;
}

//--------------------------------------------------------------------------------------------

static bool print_clave(const char* clave, void* _, void* __){
    printf("\t%s\n", clave);
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int publicacion_cmp(post_con_prioridad_t* a, post_con_prioridad_t* b){
    int dif = (int) b->prioridad - (int) a->prioridad; 
    if(dif >= -1)
        dif *= -1;
    if(dif != 0) return dif;
    else
        return (int) b->id_publicacion - (int) a->id_publicacion;
}

global_t* global_crear(FILE* f){
    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->vector_usr = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_usr == NULL){
        free(nuevo);
        return NULL;
    }
    char nombre [50];
    while(  (fgets(nombre, 50, f)) != NULL ){
        nombre[strlen(nombre)-1] = '\0'; //borrar el \n
        usuario_t* nuevo_usuario = usuario_crear(nombre, vector_tamano(nuevo->vector_usr), (int (*)(const void*, const void*)) publicacion_cmp);
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
    }
    nuevo->hash_usr = hash_crear(NULL);
    for (size_t i = 0; i < vector_tamano(nuevo->vector_usr); i++){
        hash_guardar(nuevo->hash_usr,usuario_ver_nombre(vector_obtener(nuevo->vector_usr, i)), vector_obtener(nuevo->vector_usr, i));
    }
    nuevo->vector_posts = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_posts == NULL){
        vector_destruir(nuevo->vector_usr, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usr, NULL);
        free(nuevo);
        return NULL;
    }
    nuevo->vector_likes = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_posts == NULL){
        vector_destruir(nuevo->vector_usr, (void (*) (void*)) usuario_destruir);
        hash_borrar(nuevo->hash_usr, NULL);
        vector_destruir(nuevo->vector_likes, NULL);
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
    vector_destruir(global->vector_likes, (void (*) (void*)) abb_destruir);
    hash_destruir(global->hash_usr);
    free(global);
}

bool usuario_login(global_t* global, char* usuario){
    if(global->login != NULL){
        printf("Error: Ya habia un usuario loggeado\n");
        return false;
    }
    usuario_t* usr_logeado = hash_obtener(global->hash_usr, usuario);
    if(usr_logeado == NULL){
        printf("Error: usuario no existente\n");
        return false;
    }
    global->login = usr_logeado;
    printf("Hola %s\n", usuario_ver_nombre(usr_logeado));
    return true;
}

bool usuario_logout(global_t* global){
    if(global->login == NULL){
        printf("Error: no habia usuario loggeado\n");
        return false;
    }    
    global->login = NULL;
    printf("Adios\n");
    return true;
}

bool post_publicar(global_t* global, char* texto){
    if(global->login == NULL){
        printf("Error: no habia usuario loggeado\n");
        return false;
    }
    publicacion_t* nuevo_post = publicacion_nueva(global->id_post_global, texto, usuario_ver_id(global->login));
    if(nuevo_post == NULL) return false;

    if(!vector_agregar(global->vector_posts, (void*) nuevo_post)){
        publicacion_destruir(nuevo_post);
        return false;
    }
    abb_t* likes_post = abb_crear(strcmp, NULL);
    if(!vector_agregar(global->vector_likes, (void*) likes_post)){
        publicacion_destruir(nuevo_post);
        abb_destruir(likes_post);
        return false;
    }
    for(size_t i=0; i<vector_tamano(global->vector_usr); i++){
        if(usuario_ver_id( (const usuario_t*) (global->login)) == usuario_ver_id( (const usuario_t*) vector_obtener(global->vector_usr, i)) )
            continue;
        post_con_prioridad_t* p_prioridad = post_con_prioridad_crear(publicacion_ver_id(nuevo_post), usuario_ver_id(global->login),
                                            usuario_ver_id( (const usuario_t*) vector_obtener(global->vector_usr, i)));
        // VALIDAR 
        if( !usuario_guardar_publicacion(vector_obtener(global->vector_usr, i), (void*) p_prioridad) ){
            publicacion_destruir(nuevo_post);
            abb_destruir(likes_post);
            return false;
        }
    }
    global->id_post_global ++;
    printf("Post publicado\n");
    return true;
}

bool ver_siguiente_feed(global_t* global){
    if(feed_esta_al_final(global->login) || global->login == NULL){ 
        printf("Usuario no loggeado o no hay mas posts para ver.\n");        
        return false;
    }
    post_con_prioridad_t* p_prioridad = (post_con_prioridad_t*) usuario_ver_siguiente_publicacion(global->login);
    //printf("ESTO ES LA PRIORIDAD EN TEORIA %ld\n",p_prioridad->prioridad);
    printf("Post ID:%zu\n", p_prioridad->id_publicacion);
    printf("%s dijo: %s\n", usuario_ver_nombre(vector_obtener(global->vector_usr, publicacion_ver_id_creador( vector_obtener(global->vector_posts, p_prioridad->id_publicacion) ) ) ),
                                    publicacion_ver_mensaje( vector_obtener(global->vector_posts, p_prioridad->id_publicacion) ) );
    printf("Likes: %zu\n", abb_cantidad((abb_t*) vector_obtener(global->vector_likes, p_prioridad->id_publicacion)));
    free(p_prioridad);
    return true;
}

bool likear_post(global_t* global, long id_post){
    //printf("ESTO ES ID ULTIMA PUBLICACION %ld\n", ver_id_ultima_publicacion(global->login));
    if(global->login == NULL || id_post <0 || id_post > vector_tamano(global->vector_posts)){
        printf("Error: Usuario no loggeado o Post inexistente\n");
        return false;
    }

    abb_guardar((abb_t *) vector_obtener(global->vector_likes, (size_t) id_post), usuario_ver_nombre(global->login),NULL);
    printf("Post likeado\n");
    return true;
}

bool mostrar_likes(global_t* global, long id_publicacion){
    if( id_publicacion<0 || id_publicacion > vector_tamano(global->vector_likes) ){
        printf("Error: Post inexistente o sin likes\n");
        return false;
    }
    abb_t* post = (abb_t*) vector_obtener(global->vector_likes, id_publicacion);
    size_t cantidad_likes = abb_cantidad(post);
    if(cantidad_likes == 0){
        printf("Error: Post inexistente o sin likes\n");
        return true;
    }
    printf("El post tiene %zu likes:\n", cantidad_likes);
    abb_in_order(post, print_clave,NULL);
    return true;
}
