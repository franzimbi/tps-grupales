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
    size_t prioridad;
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


//--------------------------------------------------------------------------------------------

static bool print_clave(const char* clave, void* _, void* __){
    printf("%s\n", clave);
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int publicacion_cmp(post_con_prioridad_t* a, post_con_prioridad_t* b){
    a->prioridad - b->prioridad;
}

global_t* global_crear(FILE* f){
    global_t* nuevo = malloc(sizeof(global_t));
    if(nuevo == NULL) return NULL;

    nuevo->vector_usr = vector_crear(CANTIDAD_INICIAL);
    if(nuevo->vector_usr == NULL){
        free(nuevo);
        return NULL;
    }
    int largo_linea = 0;
    size_t largo_nombre = 50;
    char* nombre = malloc(sizeof(char) * largo_nombre);
    while( ( largo_linea = getline(&nombre, &largo_nombre, f) ) != -1 ){
        nombre[largo_linea-1] = '\0'; // para no guardar el \n
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
    free(nombre);
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

static bool usuario_login_(global_t* global, char* usuario){
    if(global->login != NULL){
        fprintf(stderr,"Error: Ya habia un usuario loggeado.");
        return false;
    }
    
    usuario_t* usr_logeado = hash_obtener(global->hash_usr, usuario);
    if(usr_logeado == NULL){
        fprintf(stderr,"Error: Ya habia un usuario loggeado.");
        return false;
    }
    global->login = usr_logeado;
    printf("hola %s\n", usuario_ver_nombre(usr_logeado));
    return true;
}

bool usuario_login(void* global, void* usuario){
    return usuario_login_((global_t*) global, (char*) usuario);
}

static bool usuario_logout_(global_t* global, char* _){
    if(global->login == NULL){
        fprintf(stderr, "Error: no habia usuario loggeado.\n");
        return false;
    }    
    global->login = NULL;
    return true;
}

bool usuario_logout(void* global, void* _){
    return usuario_logout_((global_t*)global, (char*)_);
}

static bool post_publicar_(global_t* global, char* texto){
    if(global->login == NULL){
        fprintf(stderr, "Error: no habia usuario loggeado.\n");
        return false;
    }
    publicacion_t* nuevo_post = publicacion_nueva(global->id_post_global, texto, usuario_ver_id(global->login));
    if(nuevo_post == NULL) return false;

    if(!vector_agregar(global->vector_posts, (void*) nuevo_post)){
        destructor_publicacion(nuevo_post);
        return false;
    }
    abb_t* likes_post = abb_crear(strcmp, NULL);
    if(!vector_agregar(global->vector_likes, (void*) likes_post)){
        publicacion_destruir(nuevo_post);
        abb_destruir(likes_post);
        return false;
    }
    for(size_t i=0; i<vector_tamano(global->vector_usr); i++){
        if( !usuario_guardar_publicacion(vector_obtener(global->vector_usr, i), (void*) nuevo_post) ){
            publicacion_destruir(nuevo_post);
            abb_destruir(likes_post);
            return false;
        }
    }
    global->id_post_global ++;
    return true;
}

bool post_publicar(void* global, void* texto){
    return post_publicar_((global_t*)global, (char*)texto);
}

static bool ver_siguiente_feed_(global_t* global){
    if(feed_esta_al_final(global->login) || global->login == NULL){ 
        fprintf(stderr, "Usuario no loggeado o no hay mas posts para ver.\n");        
        return false;
    }
    void* publicacion = usuario_ver_siguiente_publicacion(global->login);
    set_id_ultima_publicacion(global->login, publicacion_ver_id((publicacion_t*) publicacion));
    printf("Post ID:%ld\n", publicacion_ver_id((publicacion_t*) publicacion));
    printf("%s dijo: %s\n", (char*) vector_obtener(global->vector_usr, publicacion_ver_id_creador(publicacion)), publicacion_ver_mensaje(publicacion));
    return true;
}

bool ver_siguiente_feed(void* global, void* _){
    ver_siguiente_feed_((global_t*)global);
}

static bool likear_post_(global_t* global){
    if(ver_id_ultima_publicacion(global->login) == -1 || global->login == NULL){
        fprintf(stderr, "Error: Usuario no loggeado o Post inexistente.\n");
        return false;
    }

    abb_guardar((abb_t *) vector_obtener(global->vector_likes,ver_id_ultima_publicacion(global->login)), usuario_ver_nombre(global->login),NULL);
    printf("Post likeado\n");
    return true;
}

bool likear_post(void* global, void* _){
    likear_post_((global_t*) global);
}

static bool mostrar_likes_(global_t* global, size_t id_publicacion){
    if(id_publicacion<0 || id_publicacion >= vector_tamano(global->vector_likes)){
        fprintf(stderr, "Error: Post inexistente o sin likes.\n");
        return false;
    }

    abb_in_order(vector_obtener(global->vector_likes, id_publicacion), print_clave,NULL);
    return true;
}

bool mostrar_likes(void* global, void* id_publiacion){
    return mostrar_likes_((global_t*) global, (size_t) id_publiacion);
}

int main(void){
    FILE* archivo = fopen("04_usuarios", "r");
    global_t* global = global_crear(archivo);

    usuario_login(global, "barbara");
    post_publicar(global, "booooeenasss");
    set_id_ultima_publicacion(global->login, 0);
    likear_post(global, 0);
    mostrar_likes(global, 0);
    fclose(archivo);
    global_destruir(global);
    return 0;
}
