/* En los archivos (*.c) se pueden poner tanto DECLARACIONES como DEFINICIONES de C, así como directivas de preprocesador */
/* Recordar solamente indicar archivos *.h en las directivas de preprocesador #include, nunca archivos *.c */

#include <stdio.h>
#include "general.h"

extern YYLTYPE yylloc;

int sumaDecimales = 0;
int acumuladorIdentificadores = 0;
int num_linea = 1;
char* buffer = NULL;

nodoIdentificadores *raizIdentificador = NULL;
nodoLiteralCadena *raizLiterales = NULL;
nodoDecimal *raizDecimal = NULL;
nodoHexadecimal *raizHexadecimal = NULL;
nodoOctal *raizOctal = NULL;
nodoReservada *raizPalabraReservada = NULL;
nodoReal *raizReal = NULL;
nodoCaracter *raizCaracter = NULL;
nodoPuntuaciones *raizPuntuaciones = NULL;
nodoCadenasNoReconocidas* raizNoReconocida = NULL;

nodoVarDeclarada* raizVariables = NULL;
nodoFuncion* raizFunciones = NULL;
nodoSentencia* raizSentencias = NULL;
nodoEstructuraNoReconocida* raizEstructurasNoReconocidas = NULL;

nodoErrorSemantico* raizErroresSemanticos = NULL;

int linea_actual = 1;
int columna_actual = 1;

char buffer_acumulador[512];

void inicializarUbicacion(void)
{
    yylloc.first_line = yylloc.last_line = INICIO_CONTEO_LINEA;
    yylloc.first_column = yylloc.last_column = INICIO_CONTEO_COLUMNA;
}

int agregarIdentificadorATS(const char* nombre, const char* tipo, int linea) {
    nodoVarDeclarada* aux = TS.nodoVariable;
    nodoVarDeclarada* ultimo = NULL;

    while (aux != NULL) {
        if (aux->info.nombre && strcmp(aux->info.nombre, nombre) == 0){
            return -1;
        }
        ultimo = aux;
        aux = aux->sgte;
    }

    nodoVarDeclarada* nuevo = (nodoVarDeclarada*)malloc(sizeof(nodoVarDeclarada));

    nuevo->info.nombre = strdup(nombre);
    if (tipo != NULL) {
        nuevo->info.tipo = strdup(tipo);
    } else {
        nuevo->info.tipo = NULL;
    }
    nuevo->info.linea = linea;
    nuevo->sgte = NULL;

    if (TS.nodoVariable == NULL) {
        TS.nodoVariable = nuevo;
    } else {
        ultimo->sgte = nuevo;
    }

    return 0;
}

void acumularError(char *identificador, int codigo, int linea, int columna);

char* obtenerTipoIdentificador(char* nombre) {
    nodoVarDeclarada* aux = TS.nodoVariable;
    while (aux != NULL) {

        if (aux->info.nombre && strcmp(aux->info.nombre, nombre) == 0) {
            return aux->info.tipo;
        }
        aux = aux->sgte;
    }
    return NULL;
}

tablaDeSimbolos TS = { NULL, NULL };

void iniciar_tabla(void) {
    TS.nodoVariable  = NULL;
    TS.nodoFuncion  = NULL;
}
