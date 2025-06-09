#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "constantes.h"

typedef enum columna{
    COL_0,
    COL_1_7,
    COL_8_9,
    COL_AF_af,
    COL_xX,
    COL_otro_caracter
} columna;  

typedef enum estado{
    Q0,
    Q1,
    Q2,
    Q3,
    Q4,
    Q5,
    Q6  
}estado;

columna caracter_a_columna(int caracter);
void fin_de_cadena (estado estado, FILE * salida );
void scanner (FILE* entrada, FILE *salida);