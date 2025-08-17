/* En los archivos (*.c) se pueden poner tanto DECLARACIONES como DEFINICIONES de C, así como directivas de preprocesador */
/* Recordar solamente indicar archivos *.h en las directivas de preprocesador #include, nunca archivos *.c */

#include <stdio.h>

#include "general.h"

extern YYLTYPE yylloc;

void pausa(void)
{
    printf("Presione ENTER para continuar...\n");
    getchar();
}

void inicializarUbicacion(void)
{
    yylloc.first_line = yylloc.last_line = INICIO_CONTEO_LINEA;
    yylloc.first_column = yylloc.last_column = INICIO_CONTEO_COLUMNA;
}

void reinicializarUbicacion(void)
{
    yylloc.first_line = yylloc.last_line;
    yylloc.first_column = yylloc.last_column;
}

char* devolverAParser(char *aDevolver){

    char *tipo = NULL;

    if (strcmp(aDevolver, "if") == 0 ) return "IF";
    if (strcmp(aDevolver, "if/else") == 0 ) return "IF/ELSE";
    if (strcmp(aDevolver, "switch") == 0) return "SWITCH";
    if (strcmp(aDevolver, "while") == 0) return "WHILE";
    if (strcmp(aDevolver, "do/while") == 0) return "DO/WHILE"; 
    if (strcmp(aDevolver, "for") == 0) return "FOR"; 
    if (strcmp(aDevolver, "case") == 0) return "CASE";
    if (strcmp(aDevolver, "default") == 0) return "DEFAULT";
    if (strcmp(aDevolver, "continue") == 0) return "CONTINUE";
    if (strcmp(aDevolver, "break") == 0) return "BREAK";
    if (strcmp(aDevolver, "return") == 0) return "RETURN";
}