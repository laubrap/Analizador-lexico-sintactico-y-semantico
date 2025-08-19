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

    if (strcmp(aDevolver, "auto") == 0) return "AUTO";
    if (strcmp(aDevolver, "register") == 0) return "REGISTER";
    if (strcmp(aDevolver, "static") == 0) return "STATIC";
    if (strcmp(aDevolver, "extern") == 0) return "EXTERN";
    if (strcmp(aDevolver, "typedef") == 0) return "TYPEDEF";
    if (strcmp(aDevolver, "void") == 0) return "VOID";
    if (strcmp(aDevolver, "char") == 0) return "CHAR";
    if (strcmp(aDevolver, "short") == 0) return "SHORT";
    if (strcmp(aDevolver, "int") == 0) return "INT";
    if (strcmp(aDevolver, "long") == 0) return "LONG";
    if (strcmp(aDevolver, "float") == 0) return "FLOAT";
    if (strcmp(aDevolver, "double") == 0) return "DOUBLE";
    if (strcmp(aDevolver, "signed") == 0) return "SIGNED";
    if (strcmp(aDevolver, "unsigned") == 0) return "UNSIGNED";
    if (strcmp(aDevolver, "const") == 0) return "CONST";
    if (strcmp(aDevolver, "volatile") == 0) return "VOLATILE";
    if (strcmp(aDevolver, "struct") == 0) return "STRUCT";
    if (strcmp(aDevolver, "union") == 0) return "UNION";
    if (strcmp(aDevolver, "enum") == 0) return "ENUM";
    if (strcmp(aDevolver, "case") == 0) return "CASE";
    if (strcmp(aDevolver, "default") == 0) return "DEFAULT";
    if (strcmp(aDevolver, "if") == 0) return "IF";
    if (strcmp(aDevolver, "else") == 0) return "ELSE";
    if (strcmp(aDevolver, "switch") == 0) return "SWITCH";
    if (strcmp(aDevolver, "do") == 0) return "DO";
    if (strcmp(aDevolver, "while") == 0) return "WHILE";
    if (strcmp(aDevolver, "for") == 0) return "FOR";
    if (strcmp(aDevolver, "goto") == 0) return "GOTO";
    if (strcmp(aDevolver, "continue") == 0) return "CONTINUE";
    if (strcmp(aDevolver, "break") == 0) return "BREAK";
    if (strcmp(aDevolver, "return") == 0) return "RETURN";
    if (strcmp(aDevolver, "sizeof") == 0) return "SIZEOF";

    /* Literales de dos caracteres */
    if (strcmp(aDevolver, "++") == 0) return "INCREMENTO";
    if (strcmp(aDevolver, "--") == 0) return "DECREMENTO";
    if (strcmp(aDevolver, "+=") == 0) return "MAS_IGUAL";
    if (strcmp(aDevolver, "-=") == 0) return "MENOS_IGUAL";
    if (strcmp(aDevolver, "*=") == 0) return "MULTIPLICAR_IGUAL";
    if (strcmp(aDevolver, "/=") == 0) return "DIVIDIR_IGUAL";
    if (strcmp(aDevolver, "==") == 0) return "IGUAL_IGUAL";
    if (strcmp(aDevolver, "!=") == 0) return "NEGADO_IGUAL";
    if (strcmp(aDevolver, ">=") == 0) return "MAYOR_IGUAL";
    if (strcmp(aDevolver, "<=") == 0) return "MENOR_IGUAL";
    if (strcmp(aDevolver, "&&") == 0) return "AND";
    if (strcmp(aDevolver, "||") == 0) return "OR";

    /* Literales de un solo caracter */
    if (strcmp(aDevolver, "+") == 0) return '+';
    if (strcmp(aDevolver, "-") == 0) return '-';
    if (strcmp(aDevolver, "*") == 0) return '*';
    if (strcmp(aDevolver, "/") == 0) return '/';
    if (strcmp(aDevolver, "=") == 0) return '=';
    if (strcmp(aDevolver, ">") == 0) return '>';
    if (strcmp(aDevolver, "<") == 0) return '<';
    if (strcmp(aDevolver, "!") == 0) return '!';
    if (strcmp(aDevolver, "&") == 0) return '&';
    if (strcmp(aDevolver, ":") == 0) return ':';
    if (strcmp(aDevolver, ";") == 0) return ';';
    if (strcmp(aDevolver, ",") == 0) return ',';
    if (strcmp(aDevolver, ".") == 0) return '.';
    if (strcmp(aDevolver, "[") == 0) return '[';
    if (strcmp(aDevolver, "]") == 0) return ']';
    if (strcmp(aDevolver, "(") == 0) return '(';
    if (strcmp(aDevolver, ")") == 0) return ')';
    if (strcmp(aDevolver, "{") == 0) return '{';
    if (strcmp(aDevolver, "}") == 0) return '}';
}