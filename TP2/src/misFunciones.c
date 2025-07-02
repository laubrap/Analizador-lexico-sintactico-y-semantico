#include "misFunciones.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ---------- IDENTIFICADORES ----------


nodoIdentificadores * agregarIdentificadores(nodoIdentificadores*raiz , char*elementoParaAgregar) {
    nodoIdentificadores *aux = raiz;

    while (aux != NULL) {
        if (strcmp(aux->info.nombreIdentificador, elementoParaAgregar) == 0) {
            aux->info.contador += 1;
            return raiz;
        }
        aux = aux->sgte;
    }

    nodoIdentificadores *nuevo = (nodoIdentificadores *)malloc(sizeof(nodoIdentificadores));
    if (!nuevo) return raiz;

    nuevo->info.nombreIdentificador = strdup(elementoParaAgregar);
    if (!nuevo->info.nombreIdentificador) {
        free(nuevo);
        return raiz;
    }

    nuevo->info.contador = 1;
    nuevo->sgte = NULL;

    nodoIdentificadores *punteroAnterior = NULL;
    nodoIdentificadores *punteroActual = raiz;

    while (punteroActual != NULL && strcmp(punteroActual->info.nombreIdentificador, elementoParaAgregar) < 0) {
        punteroAnterior = punteroActual;
        punteroActual = punteroActual->sgte;
    }

    if (punteroAnterior != NULL) {
        punteroAnterior->sgte = nuevo;
    } else {
        raiz = nuevo;
    }

    nuevo->sgte = punteroActual;
    return raiz;
}

void imprimirIdentificadores(nodoIdentificadores* raiz, FILE* salida) {
    nodoIdentificadores* aux = raiz;
    int encontradas = 0;
    fprintf(salida, "* Listado de identificadores encontrados: \n");

    while (aux != NULL) {
        fprintf(salida, "La palabra %s aparece: %d veces\n", aux->info.nombreIdentificador, aux->info.contador);
        encontradas = 1; 
        aux = aux->sgte;
    }

    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}

// ---------- LITERALES CADENA ----------

nodoLiteralCadena* agregarLiteralesCadena(nodoLiteralCadena *raizLiterales, char *elementoParaAgregar, int longitud) {
    nodoLiteralCadena *aux = raizLiterales;

    while (aux != NULL) {
        if (strcmp(aux->info.nombreLiteralCadena, elementoParaAgregar) == 0) {
            return raizLiterales; // ya existe
        }
        aux = aux->sgte;
    }

    nodoLiteralCadena *nuevo = (nodoLiteralCadena*)malloc(sizeof(nodoLiteralCadena));
    if (!nuevo) return raizLiterales;

    nuevo->info.nombreLiteralCadena = strdup(elementoParaAgregar);
    if (!nuevo->info.nombreLiteralCadena) {
        free(nuevo);
        return raizLiterales;
    }

    nuevo->info.longitud = longitud;
    nuevo->sgte = NULL;

    nodoLiteralCadena *punteroAnterior = NULL;
    nodoLiteralCadena *punteroActual = raizLiterales;

    while (punteroActual != NULL && punteroActual->info.longitud < nuevo->info.longitud) {
        punteroAnterior = punteroActual;
        punteroActual = punteroActual->sgte;
    }

    if (punteroAnterior != NULL) {
        punteroAnterior->sgte = nuevo;
    } else {
        raizLiterales = nuevo;
    }

    nuevo->sgte = punteroActual;
    return raizLiterales;
}

void imprimirLiteralesCadena(nodoLiteralCadena* raiz, FILE* salida) {
    nodoLiteralCadena* aux = raiz;
    int encontradas = 0;
    fprintf (salida,"\n* Listado de literales cadena encontrados: \n ");
   
    while (aux != NULL) {
        fprintf(salida, "%s: longitud %d\n", aux->info.nombreLiteralCadena, aux->info.longitud);
        encontradas = 1;
        aux = aux->sgte;
    }

    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}

// ----------Palabras Reservadas-------

nodoReservada * agregarReservada(nodoReservada * raizReservada, char *valor, int columna, int linea){

    nodoReservada * nuevo = (nodoReservada*)malloc(sizeof(nodoReservada));
    nuevo->info.columna = columna;
    nuevo->info.linea = linea;
    nuevo->info.palabra = strdup(valor);
    nuevo->sgte = NULL;
    
    nodoReservada * aux = raizReservada;

    if(raizReservada == NULL){
      raizReservada = nuevo;  
      return raizReservada;
    }
    else{
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
        return raizReservada;
    }
}

void imprimirAlmacenamiento(nodoReservada *raiz, FILE *salida) {

    nodoReservada *aux = raiz;
    int encontradas = 0;

    fprintf(salida,"\n*Listado de palabras reservadas (clase de almacenamiento):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "auto") == 0 || 
            strcmp(aux->info.palabra, "register") == 0 ||
            strcmp(aux->info.palabra, "static") == 0 || 
            strcmp(aux->info.palabra, "extern") == 0 ||
            strcmp(aux->info.palabra, "typedef") == 0) 
        {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra,aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }

    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}

void imprimirEspecificadoresTipo(nodoReservada *raiz, FILE *salida) {
    int encontradas = 0;
    nodoReservada *aux = raiz;
    fprintf(salida, "\n\n* Listado de palabras reservadas (especificadores de tipo):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "void") == 0 ||
            strcmp(aux->info.palabra, "char") == 0 ||
            strcmp(aux->info.palabra, "short") == 0 ||
            strcmp(aux->info.palabra, "int") == 0 ||
            strcmp(aux->info.palabra, "long") == 0 ||
            strcmp(aux->info.palabra, "float") == 0 ||
            strcmp(aux->info.palabra, "double") == 0 ||
            strcmp(aux->info.palabra, "signed") == 0 ||
            strcmp(aux->info.palabra, "unsigned") == 0) 
        {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }
    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}


void imprimirCalificadoresTipo(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (calificadores de tipo):\n");
    
    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "const") == 0 ||
            strcmp(aux->info.palabra, "volatile") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }
    if (encontradas == 0) {
      fprintf(salida, "-");
}
}

void imprimirCalificadoresUnion(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (struct / union):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "struct") == 0 ||
            strcmp(aux->info.palabra, "union") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }

    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}


void imprimirEnumeraciones(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (enumeraciones):\n");
 
    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "enum") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }

    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}


void imprimirEtiquetas(nodoReservada *raiz, FILE *salida){
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (etiquetas):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "case") == 0 ||
            strcmp(aux->info.palabra, "default") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }

    if (encontradas == 0) {
        fprintf(salida, "-");
    }    
}

void imprimirSeleccion(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (selección):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "if") == 0 ||
            strcmp(aux->info.palabra, "else") == 0 ||
            strcmp(aux->info.palabra, "switch") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }

    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}


void imprimirIteracion(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (iteración):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "for") == 0 ||
            strcmp(aux->info.palabra, "while") == 0 ||
            strcmp(aux->info.palabra, "do") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }
    if (encontradas == 0) {
      fprintf(salida, "-");
}
}


void imprimirSalto(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (salto):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "goto") == 0 ||
            strcmp(aux->info.palabra, "continue") == 0 ||
            strcmp(aux->info.palabra, "break") == 0 ||
            strcmp(aux->info.palabra, "return") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
        }
        encontradas = 1;
        aux = aux->sgte;
    }
    if (encontradas == 0) {
      fprintf(salida, "-");
    }
}

void imprimirUnario(nodoReservada *raiz, FILE *salida) {
    nodoReservada *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras reservadas (operadores unarios):\n");

    while (aux != NULL) {
        if (strcmp(aux->info.palabra, "sizeof") == 0) {
            fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
            encontradas = 1;
        }
        aux = aux->sgte;
    }
    
    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}


void imprimirPalabrasReservadas (nodoReservada *raiz, FILE *salida){
    
    imprimirAlmacenamiento(raiz, salida);
    imprimirEspecificadoresTipo(raiz, salida);
    imprimirCalificadoresTipo(raiz, salida);
    imprimirCalificadoresUnion(raiz, salida);
    imprimirEnumeraciones(raiz, salida);
    imprimirEtiquetas(raiz, salida);
    imprimirSeleccion(raiz, salida);
    imprimirIteracion(raiz, salida);
    imprimirSalto(raiz, salida);
    imprimirUnario(raiz, salida);
    
}

// ---------- DECIMALES ----------
nodoDecimal* agregarDecimales(nodoDecimal *raiz, int valor) {
    nodoDecimal *nuevo = (nodoDecimal *)malloc(sizeof(nodoDecimal));
    nuevo->valor = valor;
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoDecimal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}


void imprimirDecimales(nodoDecimal *raiz, FILE *salida){
    
    nodoDecimal *aux = raiz;
    int suma = 0;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de constantes enteras decimales: \n");
    
    while(aux != NULL){

        fprintf(salida, "%d: valor %d\n", aux->valor, aux->valor);
        suma += aux->valor;
        encontradas = 1;
        aux = aux->sgte;
    }
    fprintf(salida, "Total acumulado de sumar todas las constantes decimales: %d\n", suma);
    if (encontradas == 0) {
        fprintf(salida, "-");
    }
}



// ---------- Hexadecimal -----------
nodoHexadecimal* agregarHexadecimal(nodoHexadecimal *raiz, char* valor){

    nodoHexadecimal *nuevo = (nodoHexadecimal *)malloc(sizeof(nodoHexadecimal));
    nuevo->info.hexadecimal = strdup(valor);
    nuevo->info.decimal = strtol(valor, NULL, 16);
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoHexadecimal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}

void imprimirHexadecimales(nodoHexadecimal *raiz, FILE *salida){
    
    nodoHexadecimal *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de constantes enteras hexadecimales: \n");
    
    while(aux != NULL){
        fprintf(salida, "%s: valor %d\n", aux->info.hexadecimal, aux->info.decimal);
        encontradas = 1;
    aux = aux->sgte;
}
if (encontradas == 0) {
            fprintf(salida, "-");
    }
}


// ----------- Octales ---------
nodoOctal* agregarOctal(nodoOctal *raiz, char* valor){

    nodoOctal *nuevo = (nodoOctal *)malloc(sizeof(nodoOctal));
    nuevo->info.octal = strdup(valor);
    nuevo->info.decimal = (int)strtol(valor, NULL, 8);
    nuevo->sgte = NULL;
    if (raiz == NULL) {
        return nuevo;
    }
    nodoOctal *aux = raiz;
    while (aux->sgte != NULL) {
        aux = aux->sgte;
    }
    aux->sgte = nuevo;
    return raiz;
}

void imprimirOctal(nodoOctal *raiz, FILE *salida){
    
    nodoOctal *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de constantes enteras octales: \n");
    
    while(aux != NULL){
        fprintf(salida, "%s: valor %d\n", aux->info.octal, aux->info.decimal);
        encontradas = 1;
    aux = aux->sgte;
}
if (encontradas == 0) {
            fprintf(salida, "-");
    }
}


// ----------- Reales ---------
nodoReal * agregarReal(nodoReal *raizReal, char* valor){
    nodoReal * aux = raizReal;
    nodoReal * nuevo = (nodoReal*)malloc(sizeof(nodoReal));
    float valorDecimal = atof(valor);

    nuevo->info.valor = strdup(valor);
    nuevo->info.parteEntera = floor(valorDecimal);
    nuevo->info.mantisa = (float)(valorDecimal - floor(valorDecimal));
    nuevo->sgte = NULL;
    
    if(raizReal == NULL){
        raizReal = nuevo;
        return nuevo;
    }
    else{

        while(aux->sgte != NULL){
            aux=aux->sgte;
        }
    }
    aux->sgte = nuevo;
    return raizReal;
}

void imprimirReales(nodoReal * raizReal, FILE* salida){

    nodoReal * aux = raizReal;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de constantes enteras decimales: \n");
    
    while( aux !=NULL){
        fprintf(salida, "%s: parte entera: %d, mantisa: %f\n", aux->info.valor, aux->info.parteEntera, aux->info.mantisa );
        encontradas = 1;
        aux=aux->sgte;
    }
    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}

// ------ Caracteres --------
nodoCaracter * agregarCaracter (nodoCaracter *raizCaracter, char* valor){
    nodoCaracter * aux = raizCaracter;
    nodoCaracter *nuevo = (nodoCaracter*)malloc(sizeof(nodoCaracter));
    nuevo->info.caracter = strdup(valor);
    nuevo->sgte = NULL;

    if (raizCaracter == NULL) {
        raizCaracter = nuevo;
        return nuevo;     
    } else {
        while (aux->sgte != NULL) {
            aux = aux->sgte;
    }
    }
    aux->sgte = nuevo;
    return raizCaracter;
}

void imprimirCaracteres (nodoCaracter *raizCaracter, FILE* salida) {
    nodoCaracter *aux = raizCaracter;
    int contador = 0;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de constantes de caracter; \n");
   
    while( aux !=NULL){
    contador+=1;
    fprintf(salida, "%d) %s\n", contador,aux->info.caracter);
    encontradas = 1;
    aux=aux->sgte;
    }
    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}


// ------------- Puntuacion -------------
nodoPuntuaciones* agregarPuntuacion(nodoPuntuaciones *raiz, char *caracter) {
    nodoPuntuaciones *aux = raiz;

    while (aux != NULL) {
        if (strcmp(aux->info.nombrePuntuaciones, caracter) == 0) {
            aux->info.contador += 1;
            return raiz;
        }
        aux = aux->sgte;
    }

    nodoPuntuaciones *nuevo = (nodoPuntuaciones*)malloc(sizeof(nodoPuntuaciones));
    nuevo->info.nombrePuntuaciones = strdup(caracter);
    nuevo->info.contador = 1;
    nuevo->sgte = NULL;

    if (raiz == NULL) 
        return nuevo;
      else {
        aux = raiz;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
        return raiz;
    }
}

void imprimirPuntuaciones(nodoPuntuaciones* raiz, FILE* salida) {
    nodoPuntuaciones* aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n* Listado de caracteres de puntuación encontrados: \n");
   
    while (aux != NULL) {
        fprintf(salida, " %s :aparece %d veces\n", aux->info.nombrePuntuaciones, aux->info.contador);
        encontradas = 1;
        aux = aux->sgte;
        
    }
    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}


// ------------ Cadenas no reconocidas ------------

nodoCadenasNoReconocidas* agregarCadenaNoReconocida(nodoCadenasNoReconocidas* raiz, char *valor ,int columna, int linea, FILE* salida){

    nodoCadenasNoReconocidas * nuevo = (nodoCadenasNoReconocidas*)malloc(sizeof(nodoCadenasNoReconocidas));
    nuevo->info.columna = columna;
    nuevo->info.linea = linea;
    nuevo->info.palabra = strdup(valor);
    nuevo->sgte = NULL;
    
    nodoCadenasNoReconocidas * aux = raiz;

    if(raiz == NULL){
      raiz = nuevo;  
      return raiz;
    }
    else{
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
        return raiz;
    }
}

void imprimirCadenaNoReconocida(nodoCadenasNoReconocidas *raiz, FILE *salida) {
    nodoCadenasNoReconocidas *aux = raiz;
    int encontradas = 0;
    fprintf(salida, "\n\n* Listado de palabras no reconocidas: \n");
    
    while (aux != NULL) { 
        fprintf(salida, "%s: linea %d, columna %d\n", aux->info.palabra, aux->info.linea, aux->info.columna);
        encontradas = 1;
        aux = aux->sgte;
    }

    if (encontradas == 0) {
            fprintf(salida, "-");
    }
}



// ---------- LIBERACIÓN DE MEMORIA ----------
void liberarIdentificadores(nodoIdentificadores* raiz) {
    nodoIdentificadores* aux;
    while (raiz != NULL) {
        aux = raiz;
        raiz = raiz->sgte;
        free(aux->info.nombreIdentificador);
        free(aux);
    }
}

void liberarLiteralesCadena(nodoLiteralCadena* raiz) {
    nodoLiteralCadena* aux;
    while (raiz != NULL) {
        aux = raiz;
        raiz = raiz->sgte;
        free(aux->info.nombreLiteralCadena);
        free(aux);
    }
}
