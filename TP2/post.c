#include "abb.h"
#include "post.h"
#include <stdio.h>
#include <string.h>

struct publicacion{
    size_t id;
    char* post;
    abb_t* likes;
    usuario_t* creador;
};

publicacion_t* publicarcion_nueva(size_t id, char* texto, usuario_t* creador){
    publicacion_t* publicacion = malloc(sizeof(publicacion_t));
    if(publicacion == NULL) return NULL;

    publicacion->id = id;
    size_t tamano_texto = strlen(texto) + 1;
    publicacion->post = malloc(sizeof(char) * tamano_texto);
    if(publicacion->post == NULL){
        free(publicacion);
        return NULL;
    }
    publicacion->creador = creador;
    publicacion->likes = abb_crear(strcmp, NULL);
    if(publicacion->likes = NULL){
        free(publicacion->post);
        free(publicacion);
        return NULL;
    }
    return publicacion;
}

size_t publicacion_ver_id(publicacion_t* publicacion){
    return publicacion->id;
}

bool publicacion_likear(publicacion_t* publicacion, char* usuario){
    return abb_guardar(publicacion->likes, usuario, NULL);
}

void imprimir_publicacion(const publicacion_t* publicacion){
    printf("Post ID %zu\n", publicacion->id);
    printf("%s dijo: %s\n", usuario_ver_nombre(publicacion->creador), publicacion->post);
    printf("Likes: %zu\n", abb_cantidad(publicacion->likes));
}

bool imprimir_likes_publicacion(const publicacion_t* publicacion){
    abb_iter_t* iter = abb_iter_in_crear(publicacion->likes);
    if(iter == NULL) return false;

    while(!abb_iter_in_al_final(iter)){
        printf("%s\n", abb_iter_in_ver_actual(iter));
        abb_iter_in_avanzar(iter);
    }
    abb_iter_in_destruir(iter);
    return true;
}

void publicacion_destruir(publicacion_t* publicacion){
    abb_destruir(publicacion->likes);
    free(publicacion->post);
    free(publicacion);
}


int publicacion_cmp(publicacion_t* a, publicacion_t* b, usuario_t* lector){
    long dif_a = usuario_ver_id(lector) - usuario_ver_id(a->creador);
    if(dif_a < 0)
        dif_a *= -1;
    long dif_b = usuario_ver_id(lector) - usuario_ver_id(b->creador);
    if(dif_b < 0)
        dif_b *= -1;
    
    if(dif_a != dif_b);
        return dif_a - dif_b;
    
    return a->id - b->id

}