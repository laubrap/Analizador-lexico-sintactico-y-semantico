#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

typedef enum {
    clase_almacenamiento,
    especificador_tipo,
    clasificador_tipo,
    struct_union,
    enumeracion,
    etiqueta,
    seleccion,
    iteracion,
    salto,
    unario
} CategoriaReservada;

typedef struct {
    char *nombreIdentificador;
    char *tipoIdentificador;
    int contador;
} infoNodoIdentificadores;

typedef struct {
    char *nombrePuntuaciones;
    int contador;
} infoNodoPuntuaciones;

typedef struct {
    char *nombreLiteralCadena;
    int longitud;
} infoNodoLiteralCadena;

typedef struct {
    char* hexadecimal;
    int decimal;
} infoNodoHexadecimal;

typedef struct {
    char* octal;
    int decimal;
} infoNodoOctal;

typedef struct {
    char* palabra;
    int linea;
    int columna;
    CategoriaReservada categoria;
} infoNodoPalabrasReservada;

typedef struct {
    char* valor;
    float parteEntera;
    float mantisa;
} infoNodoReal;

typedef struct {
    char* caracter;
} infoNodoCaracter;

typedef struct {
    char* palabra;
    int linea;
    int columna;
} infoNodoCadenasNoReconocidas;

typedef struct {
    char* nombre;
    char* tipo;
    char* simbolo;
    int linea; 
    int columna;
} infoVarDeclarada;

typedef struct {
    char* nombre;
    char* retorna;
    infoVarDeclarada* parametros;
    int es_definicion;
    int linea;
    int columna;
} infoFuncion;

typedef struct {
    char* tipo;
    int linea;
    int columna;
} infoSentencia;

typedef struct {
    char* texto;
    int linea;
} infoEstructuraNoReconocida;


typedef struct nodoDecimal nodoDecimal;
typedef struct nodoHexadecimal nodoHexadecimal;
typedef struct nodoOctal nodoOctal;
typedef struct nodoReal nodoReal;
typedef struct nodoCaracter nodoCaracter;
typedef struct nodoIdentificadores nodoIdentificadores;
typedef struct nodoLiteralCadena nodoLiteralCadena;
typedef struct nodoReservada nodoReservada;
typedef struct nodoPuntuaciones nodoPuntuaciones;
typedef struct nodoCadenasNoReconocidas nodoCadenasNoReconocidas;
typedef struct nodoVarDeclarada nodoVarDeclarada;
typedef struct nodoFuncion nodoFuncion;
typedef struct nodoSentencia nodoSentencia;
typedef struct nodoEstructuraNoReconocida nodoEstructuraNoReconocida;

typedef struct {
    int valor;
    nodoDecimal *sgte;
}nodoDecimal;

typedef struct nodoHexadecimal {
    infoNodoHexadecimal info;
    nodoHexadecimal *sgte;
};

typedef struct nodoOctal {
    infoNodoOctal info;
    nodoOctal *sgte;
};

typedef struct nodoReal {
    infoNodoReal info;
    nodoReal *sgte;
};

typedef struct nodoCaracter {
    infoNodoCaracter info;
    nodoCaracter *sgte;
};

typedef struct nodoIdentificadores {
    infoNodoIdentificadores info;
    nodoIdentificadores *sgte;
};

typedef struct nodoLiteralCadena {
    infoNodoLiteralCadena info;
    nodoLiteralCadena *sgte;
};

typedef struct nodoReservada {
    infoNodoPalabrasReservada info;
    nodoReservada* sgte;
};

typedef struct nodoPuntuaciones {
    infoNodoPuntuaciones info;
    nodoPuntuaciones * sgte;
};

typedef struct nodoCadenasNoReconocidas {
    infoNodoCadenasNoReconocidas info;
    nodoCadenasNoReconocidas * sgte;
};

typedef struct nodoVarDeclarada {
    infoVarDeclarada info;
    nodoVarDeclarada* sgte;
};

typedef struct nodoFuncion {
    infoFuncion info;
    nodoFuncion* sgte;
};

typedef struct nodoSentencia {
    infoSentencia info;
    nodoSentencia* sgte;
};

typedef struct nodoEstructuraNoReconocida {
    infoEstructuraNoReconocida info;
    nodoEstructuraNoReconocida* sgte;
};

typedef struct{
    nodoVarDeclarada *nodoVariable;
    infoFuncion *nodoFuncion;
}tablaDeSimbolos;

typedef struct {
    CodigoError idError;             
    char* identificador;   
    int linea1;       
    int columna1;
    int tipoDeDatoAnterior;
    int linea2;  
    int columna2;      
    char* tipoDato;     
} errorSemanticoIdentificadores;

typedef enum {
    ERROR_SIN_DECLARAR = 1,              
    ERROR_REDECLARACION_TIPO_DIF_SIMBOLO, 
    ERROR_CONFLICTO_TIPOS_MISMO_SIMBOLO,  
    ERROR_REDECLARACION_VARIABLE_IGUAL_TIPO,
    ERROR_REDEFINICION_FUNCION_IGUAL_TIPO,
    OPERANDOS_INVALIDOS,
    FUNCION_SIN_DECLARAR,
    FUNCION_NO_SE_QUE_PONER,
    INSUFICIENTES_PARAMETROS,
    DEMASIADOS_PARAMETROS,
    INCOMPATIBILIDAD_TIPOS,
    RETORNO_VOID,
    INCOMPATIBILIDAD_TIPOS_AL_INICIAR,
    ASIGNAR_EN_UNA_CONSTANTE,
    NO_EXISTE_L_VALOR_MODIFICABLE,
    NO_RETURN_EN_FUNCION_NO_VOID,
    TIPO_DE_DATO_INCOMPATIBLE_RETURN
} CodigoError;

typedef struct{
    errorSemanticoIdentificadores info;
    nodoError* sgte;
} nodoError;



#endif /* TIPOS_H */