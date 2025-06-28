#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

//INFO DE LOS NODOS
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
}CategoriaReservada;

typedef struct{
    char *nombreIdentificador;
    int contador;
}infoNodoIdentificadores;

typedef struct{
    char *nombreLiteralCadena;
    int longitud; 
}infoNodoLiteralCadena;
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
    int parteEntera;
    float mantisa;
}infoNodoReal;

typedef struct {
    char* caracter;
    struct nodoCaracter *sgte;
}infoNodoCaracter;

typedef struct{
    int valor;
    struct nodoDecimal *sgte;
}nodoDecimal;

typedef struct {
    infoNodoHexadecimal info;
    struct nodoHexadecimal *sgte;
}nodoHexadecimal;

typedef struct {
    infoNodoOctal info;
    struct nodoOctal *sgte;
}nodoOctal;


typedef struct{
    infoNodoReal info;
    struct nodoReal *sgte;
}nodoReal;

typedef struct{
    infoNodoCaracter info;
    struct nodoCaracter *sgte;
}nodoCaracter;

typedef struct{
    infoNodoIdentificadores info;
    struct nodoIdentificadores *sgte;
}nodoIdentificadores;

typedef struct{
    infoNodoLiteralCadena info;
    struct nodoLiteralCadena *sgte;
}nodoLiteralCadena;
typedef struct nodoReservada {
    infoNodoPalabrasReservada info;
    struct nodoReservada* sgte;
} nodoReservada;




