#include "file_reader.h"
#define TAMANO_INICIAL 200

char* leer_linea(FILE* f){
    char* texto = malloc(sizeof(char) * TAMANO_INICIAL);
    if(texto == NULL) return NULL;
    size_t counter = 0;
    size_t n = TAMANO_INICIAL;
    char caracter;
    while((caracter = (char) fgetc(f)) != '\n' && caracter != EOF ){
        if(counter == n - 1){
            n *= 2;
            char* aux = realloc(texto, sizeof(char) * n);
            if(aux == NULL) return NULL;
            texto = aux;
        }
        texto[counter] = caracter;
        counter++;
    }
    if(caracter == EOF){
        free(texto);
        return NULL;
    }
    texto[counter] = '\0';
    return texto;        
}