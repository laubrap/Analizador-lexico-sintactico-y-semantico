#include "misFunciones.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ---------- IDENTIFICADORES ----------

nodoIdentificadores *agregarALista(nodoIdentificadores *raiz, char *elementoParaAgregar) {
    nodoIdentificadores *aux = raiz;

    while (aux != NULL) {
        if (strcmp(aux->info.nombreIdentificador, elementoParaAgregar) == 0) {
            aux->info.contador += 1;
            return raiz;
        }
        aux = aux->sgte;
    }

    nodoIdentificadores *nuevo = (nodoIdentificadores *)malloc(sizeof(nodoIdentificadores));
    if (!nuevo) return raiz;

    nuevo->info.nombreIdentificador = strdup(elementoParaAgregar);
    if (!nuevo->info.nombreIdentificador) {
        free(nuevo);
        return raiz;
    }

    nuevo->info.contador = 1;
    nuevo->sgte = NULL;

    nodoIdentificadores *punteroAnterior = NULL;
    nodoIdentificadores *punteroActual = raiz;

    while (punteroActual != NULL && strcmp(punteroActual->info.nombreIdentificador, elementoParaAgregar) < 0) {
        punteroAnterior = punteroActual;
        punteroActual = punteroActual->sgte;
    }

    if (punteroAnterior != NULL) {
        punteroAnterior->sgte = nuevo;
    } else {
        raiz = nuevo;
    }

    nuevo->sgte = punteroActual;
    return raiz;
}

void imprimirIdentificadores(nodoIdentificadores* raiz, FILE* salida) {
    nodoIdentificadores* aux = raiz;
    fprintf(salida, "* Listado de identificadores encontrados: \n");
    while (aux != NULL) {
        fprintf(salida, "La palabra %s aparece: %d veces\n", aux->info.nombreIdentificador, aux->info.contador);
        aux = aux->sgte;
    }
}

// ---------- LITERALES CADENA ----------

nodoLiteralCadena* literalesCadena(nodoLiteralCadena *raizLiterales, char *elementoParaAgregar, int longitud) {
    nodoLiteralCadena *aux = raizLiterales;

    while (aux != NULL) {
        if (strcmp(aux->info.nombreLiteralCadena, elementoParaAgregar) == 0) {
            return raizLiterales; // ya existe
        }
        aux = aux->sgte;
    }

    nodoLiteralCadena *nuevo = (nodoLiteralCadena*)malloc(sizeof(nodoLiteralCadena));
    if (!nuevo) return raizLiterales;

    nuevo->info.nombreLiteralCadena = strdup(elementoParaAgregar);
    if (!nuevo->info.nombreLiteralCadena) {
        free(nuevo);
        return raizLiterales;
    }

    nuevo->info.longitud = longitud;
    nuevo->sgte = NULL;

    nodoLiteralCadena *punteroAnterior = NULL;
    nodoLiteralCadena *punteroActual = raizLiterales;

    while (punteroActual != NULL && punteroActual->info.longitud < nuevo->info.longitud) {
        punteroAnterior = punteroActual;
        punteroActual = punteroActual->sgte;
    }

    if (punteroAnterior != NULL) {
        punteroAnterior->sgte = nuevo;
    } else {
        raizLiterales = nuevo;
    }

    nuevo->sgte = punteroActual;
    return raizLiterales;
}

void imprimirLiteralesCadena(nodoLiteralCadena* raiz, FILE* salida) {
    nodoLiteralCadena* aux = raiz;
    fprintf (salida,"\n* Listado de literales cadena encontrados: \n ");
    while (aux != NULL) {
        fprintf(salida, "%s: longitud %d\n", aux->info.nombreLiteralCadena, aux->info.longitud);
        aux = aux->sgte;
    }
}

// ---------- DECIMALES ----------

nodoDecimal* agregarDecimales(nodoDecimal *raiz, int valor) {
    nodoDecimal *nuevo = (nodoDecimal *)malloc(sizeof(nodoDecimal));
    nuevo->valor = valor;
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoDecimal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}


void imprimirDecimales(nodoDecimal *raiz, FILE *salida){
    
    nodoDecimal *aux = raiz;
    int suma = 0;
    
    fprintf(salida, "\n* Listado de constantes enteras decimales: \n");
    while(aux != NULL){

        fprintf(salida, "%d: valor %d\n", aux->valor, aux->valor);
        suma += aux->valor;
        aux = aux->sgte;
    }
    fprintf(salida, "Total acumulado de sumar todas las constantes decimales: %d\n", suma);
}


// ---------- Hexadecimal -----------

nodoHexadecimal* agregarHexadecimal(nodoHexadecimal *raiz, char* valor){

    nodoHexadecimal *nuevo = (nodoHexadecimal *)malloc(sizeof(nodoHexadecimal));
    nuevo->info.hexadecimal = strdup(valor);
    nuevo->info.decimal = strtol(valor, NULL, 16);
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoHexadecimal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}

void imprimirHexadecimales(nodoHexadecimal *raiz, FILE *salida){
    
    nodoHexadecimal *aux = raiz;
    fprintf(salida, "\n* Listado de constantes enteras hexadecimales: \n");
    while(aux != NULL){
        fprintf(salida, "%s: valor %d\n", aux->info.hexadecimal, aux->info.decimal);
    aux = aux->sgte;
}
}

// ----------- Octales ---------

nodoOctal* agregarOctal(nodoOctal *raiz, char* valor){

    nodoOctal *nuevo = (nodoOctal *)malloc(sizeof(nodoOctal));
    nuevo->info.octal = strdup(valor);
    nuevo->info.decimal = (int)strtol(valor, NULL, 8);
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoOctal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}

void imprimirOctal(nodoOctal *raiz, FILE *salida){
    
    nodoOctal *aux = raiz;
    fprintf(salida, "\n* Listado de constantes enteras octales: \n");
    while(aux != NULL){
        fprintf(salida, "%s: valor %d\n", aux->info.octal, aux->info.decimal);
    aux = aux->sgte;
}
}

// ----------- Reales ---------

// ---------- LIBERACIÓN DE MEMORIA ----------

void liberarIdentificadores(nodoIdentificadores* raiz) {
    nodoIdentificadores* aux;
    while (raiz != NULL) {
        aux = raiz;
        raiz = raiz->sgte;
        free(aux->info.nombreIdentificador);
        free(aux);
    }
}

void liberarLiteralesCadena(nodoLiteralCadena* raiz) {
    nodoLiteralCadena* aux;
    while (raiz != NULL) {
        aux = raiz;
        raiz = raiz->sgte;
        free(aux->info.nombreLiteralCadena);
        free(aux);
    }
}
