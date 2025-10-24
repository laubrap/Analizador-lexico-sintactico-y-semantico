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
    int linea; 
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
    char* mensaje;
    char* nota; 
    int linea;
    int columna;
} infoErrorSemantico;

typedef struct{
    infoErrorSemantico info;
    nodoErrorSemantico* sgte;
} nodoErrorSemantico;





#endif /* TIPOS_H */