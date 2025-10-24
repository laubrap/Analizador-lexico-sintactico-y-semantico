#include "structsTP4.h"

nodoIdentificadores * agregarIdentificadores(nodoIdentificadores*raiz , char*elementoParaAgregar);
void imprimirIdentificadores(nodoIdentificadores* raiz);

int obtenerValorDeOctal(int octal);
int obtenerValorDeHexadecimal(char* hex);

nodoLiteralCadena* agregarLiteralesCadena(nodoLiteralCadena *raizLiterales, char *elementoParaAgregar, int longitud);
void imprimirLiteralesCadena(nodoLiteralCadena* raiz);

nodoReservada * agregarReservada(nodoReservada * raizReservada, char *valor, int columna, int linea);
void imprimirAlmacenamiento(nodoReservada *raiz);
void imprimirEspecificadoresTipo(nodoReservada *raiz);
void imprimirCalificadoresTipo(nodoReservada *raiz);
void imprimirCalificadoresUnion(nodoReservada *raiz);
void imprimirEnumeraciones(nodoReservada *raiz);
void imprimirEtiquetas(nodoReservada *raiz);
void imprimirSeleccion(nodoReservada *raiz);
void imprimirIteracion(nodoReservada *raiz);
void imprimirSalto(nodoReservada *raiz);
void imprimirUnario(nodoReservada *raiz);
void imprimirPalabrasReservadas (nodoReservada *raiz);

nodoDecimal* agregarDecimales(nodoDecimal *raiz, int valor);
void imprimirDecimales(nodoDecimal* raiz);

nodoHexadecimal* agregarHexadecimal(nodoHexadecimal *raiz, char* valor);
void imprimirHexadecimales(nodoHexadecimal *raiz);

nodoOctal* agregarOctal(nodoOctal *raiz, char* valor);
void imprimirOctal(nodoOctal *raiz);

nodoReal * agregarReal(nodoReal *raizReal, char *valor);
void imprimirReales(nodoReal *raiz);

nodoCaracter * agregarCaracter(nodoCaracter *raizCaracter, char *valor);
void imprimirCaracteres(nodoCaracter *raiz);

nodoPuntuaciones* agregarPuntuacion (nodoPuntuaciones *raiz, char *caracter);
void imprimirPuntuaciones(nodoPuntuaciones* raiz);

nodoCadenasNoReconocidas* agregarCadenaNoReconocida(nodoCadenasNoReconocidas* raiz, char *valor ,int columna, int linea);
void imprimirCadenaNoReconocida(nodoCadenasNoReconocidas *raiz);

extern nodoVarDeclarada* raizVariables;
extern nodoFuncion* raizFunciones;
extern nodoSentencia* raizSentencias;
extern nodoEstructuraNoReconocida* raizEstructurasNoReconocidas;
extern tablaDeSimbolos *raizTS;
extern errorSemantico *raizErrores;

nodoVarDeclarada* agregarVariable(errorSemantico*listaErrores, nodoVarDeclarada* raiz,char* nombre,char* tipo,char* simbolo,int linea,int columna);
nodoFuncion* agregarFuncion(nodoFuncion* raiz, const char* nombre, const char* retorna, const char* parametros, int es_definicion, int linea);
nodoSentencia* agregarSentencia(nodoSentencia* raiz, const char* tipo, int linea, int columna);
nodoEstructuraNoReconocida* agregarEstructuraNoReconocida(nodoEstructuraNoReconocida* raiz, const char* texto, int linea);

void imprimirVariablesDeclaradas(nodoVarDeclarada* raiz);
void imprimirFunciones(nodoFuncion* raiz);
void imprimirSentencias(nodoSentencia* raiz);
void imprimirEstructurasNoReconocidas(nodoEstructuraNoReconocida* raiz);

tablaDeSimbolos *buscarSimbolo(tablaDeSimbolos *raiz, char *nombre);
tablaDeSimbolos *insertarSimbolo(tablaDeSimbolos *raiz, char *nombre, char *tipoDato, char *tipoSimbolo, int linea, int columna, errorSemantico **raizErrores);

void agregarError(errorSemantico *raiz, CodigoError codigo,char *identificador, char *tipoPrevio, int lineaPrevio, int columnaPrevio,int lineaActual, int columnaActual);
void imprimirErrores(errorSemantico* raiz);
