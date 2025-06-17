#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

typedef struct{
    char *nombreIdentificador;
    int contador;
}infoNodo;

typedef struct nodo nodo;
typedef struct nodo{
    infoNodo info;
    nodo *sgte;
};