#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void prueba_lista_vacia(){
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    print_test("ver si lista esta vacia", lista_esta_vacia(lista)==true);
    print_test("ver si lista tiene algo en el primer lugar", lista_ver_primero(lista)==NULL);
    print_test("ver si lista tiene algo en el ultimo lugar", lista_ver_ultimo(lista)==NULL);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_insertar_borrar(){
    printf("\nINICIO DE PRUEBAS DE INSERTAR Y BORRAR\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    //creo elementos para insertar y los uso
    int* dato1=malloc(sizeof(int));
    if(dato1==NULL){
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato1 =  45;

    float* dato2=malloc(sizeof(float));
    if(dato2==NULL){
        free(dato1);
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato2 = 234.576f;

    char* dato3=malloc(sizeof(char));
    if(dato2==NULL){
        free(dato1);
        free(dato2);
        printf("\nFALLO DE MEMORIA\n");
        return;
    }
    *dato3='A';

    print_test("ver si lista esta vacia", lista_esta_vacia(lista));
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    
    print_test("insertar primero en la lista", lista_insertar_primero(lista, dato1));
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato1);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato1);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==1);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato1);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    print_test("ver si lista esta vacia", lista_esta_vacia(lista));
    
    print_test("volver a insertar elemento ultimo en la lista", lista_insertar_ultimo(lista, dato1));
    print_test("insertar 2do elemento ultimo en la lista", lista_insertar_ultimo(lista, dato2));
    print_test("insertar 3er elemento ultimo en la lista", lista_insertar_ultimo(lista, dato3));
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato1);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato3);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==3);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato1);
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato2);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==2);
    print_test("ver si lista esta vacia", !lista_esta_vacia(lista));
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato2);
    print_test("ver primer elemento de la lista", lista_ver_primero(lista)==dato3);
    print_test("ver ultimo elemento de la lista", lista_ver_ultimo(lista)==dato3);
    print_test("borrar primero de la lista", lista_borrar_primero(lista)==dato3);
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==0);
    print_test("ver si lista esta vacia", lista_esta_vacia(lista));

    print_test("volver a insertar elementos a la lista", lista_insertar_ultimo(lista, dato1) 
    && lista_insertar_ultimo(lista, dato2) && lista_insertar_ultimo(lista, dato3));
    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, free);
}

static void prueba_lista_destruir_null(){
    printf("\nINICIO DE PRUEBAS DESTRUIR LISTA CON NULL\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    int dato1 = 45;
    float dato2 = 234.576f;
    char dato3 = 'A';

    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato1));
    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato2));
    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato3));

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

#define CANTIDAD_DATOS 10000

bool sumar_lista(int* elemento, int* extra) {
    int aux = *extra + *elemento;
    *extra = aux;
    return true;  // seguir iterando
}

bool encontrar_ultimo_cero(int* elemento, int* extra){
    if(*elemento == 0){
        (*extra)++;
        return true;
    }
    return false;
}

static void prueba_lista_iterador_interno(){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR INTERNO\n");
    
    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    int datos[CANTIDAD_DATOS];
    int resultado_real = 0;
    int resultado_iterado=0;
    int posicion_ultimo_cero = 0;
    bool ok = true;
    for(int i=0; i<CANTIDAD_DATOS;i++){
        datos[i]=i;
        ok &=lista_insertar_ultimo(lista, &datos[i]);
        resultado_real+=datos[i];
    }
    print_test("insertar varios datos", ok);

    lista_iterar(lista,(bool (*)(void *, void *)) sumar_lista, &resultado_iterado);
    print_test("sumar datos con iterador interno", resultado_iterado==resultado_real);

    printf("\nINICIO PRUEBAS CON CORTE\n");
    print_test("cambiar los datos de la lista", true);
    for(int i=0; i<CANTIDAD_DATOS;i++){
        if(i<CANTIDAD_DATOS/2){
            datos[i]=0;
        }else{
            datos[i]=1;
        }
    }
    lista_iterar(lista, (bool (*)(void *, void *)) encontrar_ultimo_cero, &posicion_ultimo_cero);
    print_test("verificar si el iterador interno corta con false", posicion_ultimo_cero== (CANTIDAD_DATOS)/2 );

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_iterador_externo_loop(){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR EXTERNO\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    int datos[CANTIDAD_DATOS];
    for(int i=0; i<CANTIDAD_DATOS;i++){
        datos[i]=i;
        lista_insertar_ultimo(lista, &datos[i]);
    }
    print_test("insertar datos en lista", true);

    lista_iter_t* iterador=lista_iter_crear(lista);
    print_test("crear iterador de la lista", iterador!=NULL);

    bool ok = true;
    int i=0;
    while(!lista_iter_al_final(iterador)){
        ok &= lista_iter_ver_actual(iterador)==&datos[i];
        ok &= lista_iter_avanzar(iterador);
        i++;
    }
    print_test("loopeando iterador hasta el final", ok);
    printf("loop terminado\n");
    print_test("verificar que iterador esta al final", lista_iter_al_final(iterador)==true);
    print_test("verificar que no avanza mas", !lista_iter_avanzar(iterador));

    print_test("destruir iterador", lista!=NULL);
    lista_iter_destruir(iterador);
    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_iterador_externo_insertar_borrar(){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR EXTERNO\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);
    lista_iter_t* iterador=lista_iter_crear(lista);
    print_test("crear iterador de la lista", iterador!=NULL);

    print_test("verificar que iterador esta al final", lista_iter_al_final(iterador));

    lista_t* datos[CANTIDAD_DATOS];
    for(int i=0; i<CANTIDAD_DATOS;i++){
        datos[i] = lista_crear();
        if(datos[i]==NULL){
            for(; i>0;--i){
                lista_destruir(datos[i], (void (*)(void *)) lista_destruir);
            }
        printf("ERROR DE MEMORIA\n");
        }
    }
    print_test("crear listas para insertar", true);

    bool ok = true;
    for(int i=0; i<CANTIDAD_DATOS;i++){
        ok &= lista_iter_insertar(iterador, datos[i]);
        ok &= lista_iter_ver_actual(iterador)==datos[i];
    }
    print_test("insertar varios datos", ok);
    print_test("destruir iterador", lista!=NULL);
    lista_iter_destruir(iterador);
    iterador=lista_iter_crear(lista);
    print_test("crear nuevo iterador de la lista", iterador!=NULL);

    ok=true;
    for(int i=0; i<CANTIDAD_DATOS;i++){
        ok &= lista_iter_ver_actual(iterador)==lista_ver_primero(lista);
        lista_t* aux = lista_iter_ver_actual(iterador);
        ok &= lista_iter_borrar(iterador)==aux;
    }
    print_test("borrar datos", ok);
    print_test("verificar que iterador esta al final", lista_iter_al_final(iterador));

    print_test("volver a insertar datos", true);
    for(int i=0; i<CANTIDAD_DATOS;i++){
        lista_iter_insertar(iterador, datos[i]);
    }
    
    print_test("destruir iterador", lista!=NULL);
    lista_iter_destruir(iterador);

    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, (void (*)(void *))lista_destruir);
}

static void prueba_lista_iterador_externo_casos_medio(){
    printf("\nPRUEBAS ITERADOR EXTERNO CON ELEMENTOS DEL MEDIO\n");

    lista_t* lista=lista_crear();
    print_test("crear lista", lista!=NULL);

    int dato1 = 45;
    float dato2 = 234.576f;
    char dato3 = 'A';

    print_test("insertar primero en la lista", lista_insertar_primero(lista, &dato1));
    print_test("insertar primero en la lista", lista_insertar_ultimo(lista, &dato2));
    print_test("insertar primero en la lista", lista_insertar_ultimo(lista, &dato3));
    print_test("ver la cantidad de elementos de la lista", lista_largo(lista)==3);

    lista_iter_t* iterador=lista_iter_crear(lista);
    print_test("crear iterador de la lista", iterador!=NULL);

    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato1);
    print_test("avanzar iterador", lista_iter_avanzar(iterador));
    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato2);
    print_test("borrar actual", lista_iter_borrar(iterador)==&dato2);
    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato3);
    print_test("avanzar iterador", lista_iter_avanzar(iterador));
    print_test("avanzar iterador", !lista_iter_avanzar(iterador));

    print_test("destruir iterador", lista!=NULL);
    lista_iter_destruir(iterador);

    print_test("chequear cantidad de elementos", lista_largo(lista)==2);

    print_test("ver ultimo de la lista", lista_ver_ultimo(lista)==&dato3);
    print_test("ver primero de la lista", lista_ver_primero(lista)==&dato1);
    
    iterador=lista_iter_crear(lista);
    print_test("crear otro iterador de la lista", iterador!=NULL);

    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato1);
    print_test("avanzar iterador", lista_iter_avanzar(iterador));
    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato3);
    print_test("volver a insertar", lista_iter_insertar(iterador, &dato2));
    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato2);
    print_test("avanzar iterador", lista_iter_avanzar(iterador));
    print_test("chequear actual", lista_iter_ver_actual(iterador)==&dato3);


    print_test("destruir iterador", lista!=NULL);
    lista_iter_destruir(iterador);

    print_test("chequear cantidad de elementos", lista_largo(lista)==3);
    print_test("ver ultimo de la lista", lista_ver_ultimo(lista)==&dato3);
    print_test("ver primero de la lista", lista_ver_primero(lista)==&dato1);

    print_test("borrar primero", lista_borrar_primero(lista)==&dato1);
    print_test("borrar primero", lista_borrar_primero(lista)==&dato2);
    //print_test("borrar primero", lista_borrar_primero(lista)==&dato3);

    print_test("chequear cantidad de elementos", lista_largo(lista)==1);
    print_test("destruir lista", lista!=NULL);
    lista_destruir(lista, NULL);

}

static void pruebas_de_cantidad_lista_e_iterar(){
    printf("\nPRUEBAS DE CANTIDAD LISTA\n");

    char** array = malloc(sizeof(char*) * CANTIDAD_DATOS );
    if(array == NULL){
        return;
    }

    for(int i = 0; i < CANTIDAD_DATOS; i++){
        array[i]=malloc(sizeof(char) * 10);
        strcpy(array[i], "test");
    }

    lista_t* lista = lista_crear();
    print_test("crear lista", lista!=NULL);

    bool ok = true;
    for(size_t i = 0; i < CANTIDAD_DATOS ; i++){
        ok &=lista_insertar_primero(lista, array[i]);
    }
    print_test("insertar primero varias veces", ok); 

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("crear iterador de la lista", iter!=NULL);

    ok = true;
    int i=CANTIDAD_DATOS-1;
    printf("Iterando elementos:\n");
    while (!lista_iter_al_final(iter)){
        ok &= (char*) lista_iter_ver_actual(iter) == array[i--];
        ok &= lista_iter_avanzar(iter);
        
    }
    print_test("iter avanzar hasta el final, validando actual", ok);

    print_test("destuir iterador de la lista", true);
    lista_iter_destruir(iter);

    free(array);
    print_test("destruir la lista", true);
    lista_destruir(lista, free);
}



void pruebas_lista_estudiante(){
    prueba_lista_vacia();
    prueba_lista_insertar_borrar();
    prueba_lista_destruir_null();
    prueba_lista_iterador_interno();
    prueba_lista_iterador_externo_loop();
    prueba_lista_iterador_externo_insertar_borrar();
    prueba_lista_iterador_externo_casos_medio();
    pruebas_de_cantidad_lista_e_iterar();
}

#ifndef CORRECTOR  // Para que no d?? conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si fall?? alguna prueba.
}

#endif
