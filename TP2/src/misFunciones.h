#include "structsTP2.h"

nodoIdentificadores * agregarIdentificadores(nodoIdentificadores*raiz , char*elementoParaAgregar);
void imprimirIdentificadores(nodoIdentificadores* raiz, FILE* salida);

int obtenerValorDeOctal(int octal);
int obtenerValorDeHexadecimal(char* hex);

nodoLiteralCadena* agregarLiteralesCadena(nodoLiteralCadena *raizLiterales, char *elementoParaAgregar, int longitud);
void imprimirLiteralesCadena(nodoLiteralCadena* raiz, FILE* salida);

nodoReservada * agregarReservada(nodoReservada * raizReservada, char *valor, int columna, int linea);
void imprimirAlmacenamiento(nodoReservada *raiz, FILE *salida);
void imprimirEspecificadoresTipo(nodoReservada *raiz, FILE *salida);
void imprimirCalificadoresTipo(nodoReservada *raiz, FILE *salida);
void imprimirCalificadoresUnion(nodoReservada *raiz, FILE *salida);
void imprimirEnumeraciones(nodoReservada *raiz, FILE *salida);
void imprimirEtiquetas(nodoReservada *raiz, FILE *salida);
void imprimirSeleccion(nodoReservada *raiz, FILE *salida);
void imprimirIteracion(nodoReservada *raiz, FILE *salida);
void imprimirSalto(nodoReservada *raiz, FILE *salida);
void imprimirUnario(nodoReservada *raiz, FILE *salida);
void imprimirPalabrasReservadas (nodoReservada *raiz, FILE *salida);

nodoDecimal* agregarDecimales(nodoDecimal *raiz, int valor);
void imprimirDecimales(nodoDecimal* raiz, FILE *salida);

nodoHexadecimal* agregarHexadecimal(nodoHexadecimal *raiz, char* valor);
void imprimirHexadecimales(nodoHexadecimal *raiz, FILE *salida);

nodoOctal* agregarOctal(nodoOctal *raiz, char* valor);
void imprimirOctal(nodoOctal *raiz, FILE *salida);

nodoReal * agregarReal(nodoReal *raizReal, char *valor);
void imprimirReales(nodoReal *raiz, FILE *salida);

nodoCaracter * agregarCaracter(nodoCaracter *raizCaracter, char *valor);
void imprimirCaracteres(nodoCaracter *raiz, FILE *salida);

nodoPuntuaciones* agregarPuntuacion (nodoPuntuaciones *raiz, char *caracter);
void imprimirPuntuaciones(nodoPuntuaciones* raiz, FILE* salida);

nodoCadenasNoReconocidas* agregarCadenaNoReconocida(nodoCadenasNoReconocidas* raiz, char *valor ,int columna, int linea, FILE* salida);
void imprimirCadenaNoReconocida(nodoCadenasNoReconocidas *raiz, FILE *salida);




