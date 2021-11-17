#include "usuarios.h"
#include "hash.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>



// LOGIN Y LOGOUT

hash{
    char* usuario;
    void* usuario_t*;
}

typedef struct{
    usuario_t* login;
    size_t id_global;
    char** usuarios;
    size_t total_users;
    hash_t* hash_usuarios;
}global_login_t;

typedef struct{
    heap_t* publicaciones (de publicacion_t);
    char* nombre_usuario;
    size_t id_usuario;
}usuario_t;



publicar post:
o(ulog(p)) -> encolar en cada usuario;

ver sguiente post:
o(log(p)) -> desencolar en si mismo;

typedef struct{
    size_t id;
    char* post;
    abb_t* likes;
}publicacion_t;