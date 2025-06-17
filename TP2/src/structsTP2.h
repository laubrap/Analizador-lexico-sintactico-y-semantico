#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    char *nombreIdentificador;
    int contador;
    nodo *sgte = NULL;
} nodo;