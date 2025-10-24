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

tablaDeSimbolos *raizTS = NULL;
errorSemantico *raizErrores = NULL;


int linea_actual = 1;
int columna_actual = 1;

char buffer_acumulador[512];

void inicializarUbicacion(void)
{
    yylloc.first_line = yylloc.last_line = INICIO_CONTEO_LINEA;
    yylloc.first_column = yylloc.last_column = INICIO_CONTEO_COLUMNA;
}

tablaDeSimbolos *buscarSimbolo(tablaDeSimbolos *raiz, char *nombre) {
    tablaDeSimbolos *aux = raiz;
    while (aux) {
        if (strcmp(aux->nombre, nombre) == 0)
            return aux;
        aux = aux->sgte;
    }
    return NULL;
}

tablaDeSimbolos *insertarSimbolo(tablaDeSimbolos *raiz, char *nombre, char *tipoDato, char *tipoSimbolo, int linea, int columna) {
    tablaDeSimbolos *nuevo = malloc(sizeof(tablaDeSimbolos));
    nuevo->nombre = copia(nombre);
    nuevo->tipoDato = copia(tipoDato);
    nuevo->tipoSimbolo = copia(tipoSimbolo);
    nuevo->linea = linea;
    nuevo->columna = columna;
    nuevo->definida = 0;
    nuevo->sgte = NULL;

    if (raiz == NULL) 
    {
        return nuevo;
    }

    tablaDeSimbolos *aux = raiz;
    while (aux->sgte){
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}

void agregarError(CodigoError codigo,char *identificador, char *tipoPrevio, int lineaPrevio, int columnaPrevio,int lineaActual, int columnaActual) {
    errorSemantico *nuevo = malloc(sizeof(errorSemantico));
    if (nuevo == NULL) 
      return;

    nuevo->codigo = codigo;
    nuevo->identificador = identificador;
    nuevo->tipoPrevio = tipoPrevio;
    nuevo->lineaPrevio = lineaPrevio;
    nuevo->columnaPrevio = columnaPrevio;
    nuevo->lineaActual = lineaActual;
    nuevo->columnaActual = columnaActual;
    nuevo->sgte = NULL;

    if (raizErrores == NULL) {
        raizErrores = nuevo;
        return;
    }
    errorSemantico *aux = raizErrores;
    while (aux->sgte){
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
}

void imprimirErrores(void) {
    if (raizErrores == NULL) {
        printf("-\n"); 
        return;
    }

    errorSemantico *aux = raizErrores;
    while (aux) {
        
        printf("%d:%d: ", aux->lineaActual, aux->columnaActual);
        switch (aux->codigo) {
            case ERROR_SIN_DECLARAR:
                printf("'%s' sin declarar\n", aux->identificador);
                break;
            case ERROR_REDECLARACION_TIPO_DIF_SIMBOLO:
                printf("'%s' redeclarado como un tipo diferente de simbolo\n", aux->identificador);
                printf("Nota: la declaracion previa de '%s' es de tipo '%s': %d:%d\n",
                       aux->identificador, aux->tipoPrevio, aux->lineaPrevio, aux->columnaPrevio);
                break;
            case ERROR_CONFLICTO_TIPOS_MISMO_SIMBOLO:
                printf("conflicto de tipos para '%s'; la ultima es de tipo '%s'\n",
                       aux->identificador, aux->tipoPrevio);
                printf("Nota: la declaracion previa de '%s' es de tipo '%s': %d:%d\n",
                       aux->identificador, aux->tipoPrevio, aux->lineaPrevio, aux->columnaPrevio);
                break;
            case ERROR_REDECLARACION_VARIABLE_IGUAL_TIPO:
                printf("Redeclaracion de '%s'\n", aux->identificador);
                printf("Nota: la declaracion previa de '%s' es de tipo '%s': %d:%d\n",
                       aux->identificador, aux->tipoPrevio, aux->lineaPrevio, aux->columnaPrevio);
                break;
            case ERROR_REDEFINICION_FUNCION_IGUAL_TIPO:
                printf("Redefinicion de '%s'\n", aux->identificador);
                printf("Nota: la definicion previa de '%s' es de tipo '%s': %d:%d\n",
                       aux->identificador, aux->tipoPrevio, aux->lineaPrevio, aux->columnaPrevio);
                break;
            default:
                printf("Error desconocido code=%d\n", aux->codigo);
        }
        aux = aux->sgte;
    }
}




