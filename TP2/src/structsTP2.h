#include <stdio.h>
#include <stdlib.h>

typedef struct {
 char *nombreIdentificador;
 int contador;
}listaCadenas;

typedef struct {
    listaCadenas infoCadena;
    nodo *sgte = NULL;
}nodo;
