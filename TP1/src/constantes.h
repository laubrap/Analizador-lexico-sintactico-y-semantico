#include <stdio.h>
#include <stdlib.h>

#define CANT_ESTADOS 7
#define CANT_COLUMNAS 6
#define ESTADO_INICIAL Q0
#define CENTINELA ','

#define ESTADO_FINAL Q1
#define ESTADO_FINAL2 Q2

estado tabla_transiciones[CANT_ESTADOS][CANT_COLUMNAS] = {
      //   0       [1-7]      [8-9]      [a-fA-F]      xX      Otro
/*Q0*/ {   Q1,      Q2,        Q2,         Q6,         Q6,     Q6 },
/*Q1+*/{   Q5,      Q5,        Q6,         Q6,         Q3,     Q6 },
/*Q2+*/{   Q2,      Q2,        Q2,         Q6,         Q6,     Q6 },    
/*Q3*/ {   Q4,      Q4,        Q4,         Q4,         Q6,     Q6 },
/*Q4+*/{   Q4,      Q4,        Q4,         Q4,         Q6,     Q6 },
/*Q5+*/{   Q5,      Q5,        Q6,         Q6,         Q6,     Q6 },
/*Q6*/ {   Q6,      Q6,        Q6,         Q6,         Q6,     Q6 },
};