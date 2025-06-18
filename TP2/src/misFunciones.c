#include "misFunciones.h"


int estaEnLista(nodo* raiz, char* elemento){
    while(raiz != NULL){
        if(strcmp(raiz->info.nombreIdentificador, elemento) == 0) {
            return 1;
        }
        raiz = raiz->sgte;
    }
    return 0;
}

nodo *agregarALista(nodo *raiz, char *elementoParaAgregar) {
    nodo *aux = raiz;

    while (aux != NULL) {
        if (strcmp(aux->info.nombreIdentificador, elementoParaAgregar) == 0) {
            aux->info.contador += 1;
            return raiz;
        }
        aux = aux->sgte;
    }

    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->info.nombreIdentificador = strdup(elementoParaAgregar);
    nuevo->info.contador = 1;
    nuevo->sgte = raiz;

    return nuevo;
}


int cantidadDeVecesQueAparece(nodo* raiz, char* elemento){
nodo * aux = raiz;
while (aux != NULL){
    if(strcmp(aux->info.nombreIdentificador, elemento)==0){
        return aux->info.contador;
        }
    aux = aux ->sgte;
}
return 0;
}

void imprimirIdentificadores(nodo* raiz, FILE* salida) {
    nodo* aux = raiz;
    while (aux != NULL) {
        fprintf(salida, "La palabra %s aparece : %d veces\n", aux->info.nombreIdentificador, aux->info.contador);
        aux = aux->sgte;
    }
}
// Enteros

int obtenerValorDeOctal(int octal) {
    int decimal = 0, base = 1;
    while (octal > 0) {
        int digito = octal % 10;
        decimal += digito * base;
        base *= 8;
        octal /= 10;
    }
    return decimal;
}

int obtenerValorDeHexadecimal(char* hex) {
    int decimal = 0;
    int valor;
    hex[1] = '0';
    for (int i = 0 ; hex[i] != '\0'; i++) {
        if (hex[i] >= '0' && hex[i] <= '9')
            valor = hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            valor = hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            valor = hex[i] - 'a' + 10;
        decimal = decimal * 16 + valor;
    }
    return decimal;
}