#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

static void prueba_crear_abb_vacio(){
    printf("\n\nINICIO PRUEBAS ABB VACIO\n\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio(){
    printf("\n\nINICIO PRUEBAS ABB VACIO ITERAR\n\n");
    abb_t* abb = abb_crear(strcmp,free);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar(){
    printf("\n\nINICIO PRUEBAS ABB INSERTAR\n\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "a", *valor4 = "a";
    char *clave5 = "b", *valor5 = "b";
    char *clave6 = "c", *valor6 = "c";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1));
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));

    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb pertenece clave6, es true", abb_pertenece(abb, clave6));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar(){
    printf("\n\nINICIO PRUEBAS REEMPLAZO\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir(){
    printf("\n\nINICIO PRUEBAS REEMPLAZO CON DESTRUIR\n\n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

void prueba_abb_borrar(){
    printf("\n\nINICIO PRUEBAS ABB BORRAR\n\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "4", *valor1 = "4";
    char *clave2 = "2", *valor2 = "2";
    char *clave3 = "6", *valor3 = "6";
    char *clave4 = "1", *valor4 = "1";
    char *clave5 = "5", *valor5 = "5";
    char *clave6 = "3", *valor6 = "3";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);

    // borro el nro 1, q sus hijos son NULL
    print_test("Prueba abb borrar hoja", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("vuelvo a insertar la hoja", abb_guardar(abb, clave4, valor4) && abb_cantidad(abb)==6 && abb_obtener(abb, clave4)==valor4);
    
    //borro el nro 6, q su hijo izquierdo es 5
    print_test("Prueba abb borrar nodo con un solo hijo", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Verifico si el hijo izquierdo sigue estando", abb_pertenece(abb, clave5));

    //borro el nro 2, q sus hijos son 1 y 3. mueve el nodo 1 para reemplazarlo
    print_test("Prueba borrar nodo con dos hijos", abb_borrar(abb, clave2)==valor2);
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Verifico que el elemento borrado no esta", abb_obtener(abb, clave2)==NULL);
    print_test("Verifico que los hijos del borrado esten", abb_obtener(abb, clave6)==valor6 && abb_obtener(abb, clave4));

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia(){
    printf("\n\nINICIO PRUEBAS ABB CLAVE VACIA\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null(){
    printf("\n\nINICIO PRUEBAS ABB VALOR NULL\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo, bool debug){
    printf("\n\nINICIO PRUEBAS ABB VOLUMEN\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 100;
    char** claves = malloc(sizeof(char*) * largo);

    bool ok = true;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t j = 0;
    size_t largo_string = strlen(string);
    for (int i = 0; i < largo; i++) {
        claves[i] = malloc(sizeof(char) * largo_clave);
        if(j == largo_string - 1) j = 0;
        strcpy(claves[i], string + j);
        j++;
        ok = abb_guardar(abb, (void*) claves[i], claves[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);


    for(size_t i = 0; i < largo; i++){
        void* aux = abb_borrar(abb, (const char*) claves[i]);
        if(aux == NULL)
            ok = false;
        free(aux);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == 0);
    
    free(claves);
    abb_destruir(abb);
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo){
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar(){
    printf("\n\nINICIO PRUEBAS ABB ITERAR\n\n");
    abb_t* abb2 = abb_crear(strcmp,NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};


    print_test("Prueba abb insertar clave1", abb_guardar(abb2, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb2, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb2, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb2);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));


    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb2);
} 

void prueba_abb_insertar_borrar(){

    printf("\n\nINICIO PRUEBAS ABB INSERTAR Y BORRAR\n\n");

    abb_t* abb = abb_crear(strcmp,NULL);

     char *clave4 = "4", *valor4 = "4";
    char *clave2 = "2", *valor2 = "2";
    char *clave1 = "1", *valor1 = "1";
    char *clave3 = "3", *valor3 = "3";
    char *clave5 = "5", *valor5 = "5";
    char *clave6 = "6", *valor6 = "6";

    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb pertenece clave6, es true", abb_pertenece(abb, clave6));

    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

    //borrar
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    
    print_test("Prueba abb borrar clave6, es valor6", abb_borrar(abb, clave6) == valor6);
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);

    print_test("Prueba borrar algo q no esta", abb_borrar(abb, "7")==NULL && abb_borrar(abb, "0")==NULL);
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    
    print_test("Prueba abb borrar clave4, es valor4", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);


    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb borrar clave5, es valor5", abb_borrar(abb, clave5) == valor5);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

void pruebas_abb_estudiante(){
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(500, true);
    prueba_abb_iterar(); 
    prueba_abb_insertar_borrar();
    printf("\n\n- - - - FIN DE TODAS LAS PRUEBAS - - - -\n\n");
}


int main(void){
    pruebas_abb_estudiante();
    return 0;
} 