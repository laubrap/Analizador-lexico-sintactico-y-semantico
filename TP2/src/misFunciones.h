#include "structsTP2.h"

nodoIdentificadores * agregarALista(nodoIdentificadores*raiz , char*elementoParaAgregar);
int obtenerValorDeOctal(int octal);
int obtenerValorDeHexadecimal(char* hex);

void imprimirIdentificadores(nodoIdentificadores* raiz, FILE* salida);

nodoLiteralCadena* literalesCadena(nodoLiteralCadena *raizLiterales, char *elementoParaAgregar, int longitud);
void imprimirLiteralesCadena(nodoLiteralCadena* raiz, FILE* salida);

nodoDecimal* agregarDecimales(nodoDecimal *raiz, int valor);
void imprimirDecimales(nodoDecimal* raiz, FILE *salida);

nodoHexadecimal* agregarHexadecimal(nodoHexadecimal *raiz, char* valor);
void imprimirHexadecimales(nodoHexadecimal *raiz, FILE *salida);

nodoOctal* agregarOctal(nodoOctal *raiz, char* valor);
void imprimirOctal(nodoOctal *raiz, FILE *salida);

