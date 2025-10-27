 /* Calculadora de notación polaca inversa */

/* Inicio de la seccion de prólogo (declaraciones y definiciones de C y directivas del preprocesador) */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "general.h"

	/* Declaración de la funcion yylex del analizador léxico, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla cada vez que solicite un nuevo token */
extern int yylex(void);
	/* Archivo de entrada para el analizador léxico */
extern FILE* yyin;
	/* Declaracion de la función yyerror para reportar errores, necesaria para que la función yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char*);

/* Estado auxiliar para armar strings en acciones */
char buffer_auxiliar[256];

%}
/* Fin de la sección de prólogo (declaraciones y definiciones de C y directivas del preprocesador) */

/* Inicio de la sección de declaraciones de Bison */

	/* Para requerir una versión mínima de Bison para procesar la gramática */
/* %require "2.4.1" */

	/* Para requirle a Bison que describa más detalladamente los mensajes de error al invocar a yyerror */
%error-verbose
	/* Nota: esta directiva (escrita de esta manera) quedó obsoleta a partir de Bison v3.0, siendo reemplazada por la directiva: %define parse.error verbose */

	/* Para activar el seguimiento de las ubicaciones de los tokens (número de linea, número de columna) */
%locations

	/* Para especificar la colección completa de posibles tipos de datos para los valores semánticos */
%union {
        long unsigned_long_type;
        int numeros;
        double constantes; 
        char *string;
        char *caracter;
        
}

        /* */
        
%token <string> IDENTIFICADOR 
%token <numeros> DECIMAL 
%token <numeros> OCTAL 
%token <numeros> HEXA 
%token <constantes> REAL
%token <caracter> CARACTER 
%token <string> LITERAL_CADENA

%token VOID CHAR SHORT INT LONG FLOAT DOUBLE UNSIGNED SIGNED CONST CONST FLOAT CONST INT CONST CHAR CONST DOUBLE CONST SHORT CONST LONG CONST UNSIGNED INT CONST SIGNED_INT 
%token CASE DEFAULT
%token IF ELSE SWITCH
%token DO WHILE FOR
%token CONTINUE BREAK RETURN

%token INCREMENTO DECREMENTO
%token MAS_IGUAL MENOS_IGUAL MULTIPLICAR_IGUAL DIVIDIR_IGUAL
%token IGUAL_IGUAL NEGADO_IGUAL
%token MAYOR_IGUAL MENOR_IGUAL AND OR

        /* */
%type <unsigned_long_type> exp expAsignacion expCondicional expOr expAnd expIgualdad expRelacional expAditiva listaArgumentos
%type <string> tipoDato tipoBasico parametro listaParametros parametros listaVarSimples unaVarSimple expMultiplicativa expUnaria expPostfijo expPrimaria


	/* Para especificar el no-terminal de inicio de la gramática (el axioma). Si esto se omitiera, se asumiría que es el no-terminal de la primera regla */
%start input

/* Fin de la sección de declaraciones de Bison */

/* Inicio de la sección de reglas gramaticales */
%%

/* Unidad de compilación mínima: secuencia de declaraciones/definiciones y/o nuevas líneas a tope */
input
        : /* vacío */
        | input unidad
        ;

unidad
        : declaracion
        | prototipoDeFuncion
        | definicionDeFuncion
        | ';'
        | error ';' { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, buffer_acumulador, @2.first_line); yyerrok; }
        | error ';' { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, buffer_acumulador, @2.first_line); yyerrok; }
        ;

exp
        : expAsignacion
        ;


expAsignacion
        : expCondicional
        | expUnaria '=' expAsignacion
        | expUnaria MAS_IGUAL expAsignacion 
        | expUnaria MENOS_IGUAL expAsignacion
        | expUnaria MULTIPLICAR_IGUAL expAsignacion
        | expUnaria DIVIDIR_IGUAL expAsignacion
        ;

expCondicional
        : expOr
        ;

expOr
        : expAnd
        | expOr OR expAnd {$$ = ($1 || $3);}
        ;

expAnd
        : expIgualdad
        | expAnd AND expIgualdad {$$ = $1 && $3;}
        ;

expIgualdad
        : expRelacional
        | expIgualdad IGUAL_IGUAL expRelacional {$$ = $1 == $3;}
        | expIgualdad NEGADO_IGUAL expRelacional {$$ = $1 != $3;}
        ;

expRelacional
        : expAditiva
        | expRelacional MAYOR_IGUAL expAditiva 
        | expRelacional '>' expAditiva  
        | expRelacional MENOR_IGUAL expAditiva 
        | expRelacional '<' expAditiva 
        ;

expAditiva
        : expMultiplicativa
        | expAditiva '+' expMultiplicativa 
        | expAditiva '-' expMultiplicativa 
        ;

expMultiplicativa
    : expUnaria { $$ = $1; }
    | expMultiplicativa '*' expUnaria {
        if (!tiposCompatiblesMultiplicacion($1, $3)) {
            agregarError(&raizErrores, OPERANDOS_INVALIDOS, "*", $1, $3, @2.first_line, @2.first_column, @2.first_line, @2.first_column);
            $$ = strdup("error");
        } else {
            $$ = tipoDominante($1, $3);
        }
    }
    | expMultiplicativa '/' expUnaria {
        if (!tiposCompatiblesMultiplicacion($1, $3)) {
            agregarError(&raizErrores, OPERANDOS_INVALIDOS, "/", $1, $3, @2.first_line, @2.first_column, @2.first_line, @2.first_column);
            $$ = strdup("error");
        } else {
            $$ = tipoDominante($1, $3);
        }
    }
;

expUnaria
        : expPostfijo
        | INCREMENTO expUnaria 
        | DECREMENTO expUnaria
        | expUnaria INCREMENTO 
        | expUnaria DECREMENTO    
        | '&'expUnaria 
        | '*'expUnaria 
        | '-'expUnaria 
        | '!'expUnaria 
        ;       

expPostfijo
        : expPrimaria
        | expPostfijo '[' exp ']'
        | expPostfijo '('listaArgumentos')'
        | IDENTIFICADOR '(' ')' {
                tablaDeSimbolos *simbolo = buscarSimbolo(raizTS, $1);
                if (!simbolo) {
                        agregarError(&raizErrores, FUNCION_SIN_DECLARAR, $1, NULL,NULL, -1, -1, @1.first_line, @1.first_column);
                        raizTS = insertarSimbolo(raizTS, $1, "int", "funcion", @1.first_line, @1.first_column, raizErrores);
                } else if (strcmp(simbolo->tipoSimbolo, "funcion") != 0) {
                        agregarError(&raizErrores, FUNCION_NO_SE_QUE_PONER, $1, NULL, NULL, simbolo->linea, simbolo->columna, @1.first_line, @1.first_column);
                }
        }
        | IDENTIFICADOR '(' listaArgumentos ')' {
                tablaDeSimbolos *simbolo = buscarSimbolo(raizTS, $1);
                if (!simbolo) {
                        agregarError(&raizErrores, FUNCION_SIN_DECLARAR, $1, NULL, NULL, -1, -1, @1.first_line, @1.first_column);
                        raizTS = insertarSimbolo(raizTS, $1, "int", "funcion", @1.first_line, @1.first_column, raizErrores);
                } else if (strcmp(simbolo->tipoSimbolo, "funcion") != 0) {
                        agregarError(&raizErrores, FUNCION_NO_SE_QUE_PONER, $1, NULL,NULL, simbolo->linea, simbolo->columna, @1.first_line, @1.first_column);
                }
        }
        ;

listaArgumentos
        : expAsignacion
        | listaArgumentos ',' expAsignacion
        ;
        
expPrimaria
    : IDENTIFICADOR {
        tablaDeSimbolos *simbolo = buscarSimbolo(raizTS, $1);
        if (!simbolo) {
            agregarError(&raizErrores, ERROR_SIN_DECLARAR, $1, NULL, NULL, -1, -1, @1.first_line, @1.first_column);
            $$ = strdup("error");
        } else {
            $$ = strdup(simbolo->tipoDato); 
        }
    }
    | DECIMAL            { $$ = strdup("int"); }
    | OCTAL              { $$ = strdup("int"); }
    | HEXA               { $$ = strdup("int"); }
    | REAL               { $$ = strdup("double"); }
    | LITERAL_CADENA     { $$ = strdup("string"); }
    | CARACTER           { $$ = strdup("char"); }
    | '(' exp ')'        { $$ = $2; }
;

// BNF de sentencias

sentencia
        : sentCompuesta 
        | sentExpresion 
        | sentSeleccion 
        | sentIteracion 
        | sentSalto
        | sentEtiquetada
        | error ';' { yyerrok; }
        ;

sentCompuesta
        : '{' listaDeclaraciones listaSentencias '}'
        | '{' listaSentencias '}'
        | '{' listaDeclaraciones '}'
        | '{' '}'
        ;

sentSeleccion 
        : sentIf
        | sentIfElse
        | sentSwitch
        ;

listaDeclaraciones
        : /* vacío */
        | listaDeclaraciones declaVarSimples
        ;

listaSentencias
        : /* vacío */
        | listaSentencias sentencia
        ;

sentExpresion
        : exp ';'
        | ';'
        ;

sentIf
    : IF '(' exp ')' sentencia{ raizSentencias = agregarSentencia(raizSentencias, "if", @1.first_line, @1.first_column); }
    | IF error { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, "if ...", @1.first_line); yyerrok; }
    ;

sentIfElse
    : IF '(' exp ')' sentencia ELSE sentencia{ raizSentencias = agregarSentencia(raizSentencias, "if/else", @1.first_line, @1.first_column); }
    ;

sentSwitch
    : SWITCH '(' exp ')' sentencia{ raizSentencias = agregarSentencia(raizSentencias, "switch", @1.first_line, @1.first_column); }
    ;

optExp
        : exp
        | /* vacío */
        ;

sentIteracion
        : WHILE { raizSentencias = agregarSentencia(raizSentencias, "while", @1.first_line, @1.first_column); } '(' exp ')' sentencia
        | DO { raizSentencias = agregarSentencia(raizSentencias, "do/while", @1.first_line, @1.first_column); } sentencia WHILE '(' exp ')' ';'
        | FOR { raizSentencias = agregarSentencia(raizSentencias, "for", @1.first_line, @1.first_column); } '(' optExp ';' optExp ';' optExp ')' sentencia
        | WHILE error { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, "while ...", @1.first_line); yyerrok; }
        | FOR error { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, "for ...", @1.first_line); yyerrok; }
        | DO error { raizEstructurasNoReconocidas = agregarEstructuraNoReconocida(raizEstructurasNoReconocidas, "do ...", @1.first_line); yyerrok; }
   ;


sentSalto
        : RETURN '(' exp ')' ';' { raizSentencias = agregarSentencia(raizSentencias, "return", @1.first_line, @1.first_column); }
        | RETURN exp ';' { raizSentencias = agregarSentencia(raizSentencias, "return", @1.first_line, @1.first_column); }
        | RETURN ';' { raizSentencias = agregarSentencia(raizSentencias, "return", @1.first_line, @1.first_column); }
        | CONTINUE ';' { raizSentencias = agregarSentencia(raizSentencias, "continue", @1.first_line, @1.first_column); }
        | BREAK ';' { raizSentencias = agregarSentencia(raizSentencias, "break", @1.first_line, @1.first_column); }
        ;

sentEtiquetada
        : CASE exp ':' { raizSentencias = agregarSentencia(raizSentencias, "case", @1.first_line, @1.first_column); }
        | DEFAULT ':' { raizSentencias = agregarSentencia(raizSentencias, "default", @1.first_line, @1.first_column); }
        ;

// BNF de las Declaraciones


tipoDato
        : tipoBasico
        ;

-- tipoBasico
--         : UNSIGNED INT    { $$ = strdup("unsigned int"); }
--         | CONST FLOAT     { $$ = strdup("const float"); }
--         | CONST DOUBLE     { $$ = strdup("const double"); }
--         | CONST CHAR      { $$ = strdup("const char"); }
--         | CONST INT       { $$ = strdup("const int"); }
--         | CONST SHORT     { $$ = strdup("const short"); }
--         | CONST LONG      { $$ = strdup("const long"); }
--         | CONST VOID      { $$ = strdup("const void"); }
--         | SIGNED INT      { $$ = strdup("signed int"); }
--         | UNSIGNED LONG   { $$ = strdup("unsigned long"); }
--         | LONG UNSIGNED   { $$ = strdup("unsigned long"); }
--         | VOID            { $$ = strdup("void"); }
--         | CHAR      { $$ = strdup("char"); }
--         | INT       { $$ = strdup("int"); }
--         | DOUBLE    { $$ = strdup("double"); }
--         | FLOAT     { $$ = strdup("float"); }
--         | SHORT     { $$ = strdup("short"); }
--         | LONG      { $$ = strdup("long"); }
--         | SIGNED    { $$ = strdup("signed"); }
--         | UNSIGNED  { $$ = strdup("unsigned"); }
--         ;
tipoBasico
        : VOID      { $$ = strdup("void"); }
        | CHAR      { $$ = strdup("char"); }
        | INT       { $$ = strdup("int"); }
        | DOUBLE    { $$ = strdup("double"); }
        | FLOAT     { $$ = strdup("float"); }
        | SHORT     { $$ = strdup("short"); }
        | LONG      { $$ = strdup("long"); }
        | SIGNED    { $$ = strdup("signed"); }
        | UNSIGNED  { $$ = strdup("unsigned"); }
        | tipoConstante { $$ = $1; }
        ;

tipoConstante
        : CONST tipoBasico {
            char *resultado = malloc(strlen("const ") + strlen($2) + 2);
            strcpy(resultado, "const ");
            strcat(resultado, $2);
            $$ = resultado;
          }
        ;
declaracion
        : declaVarSimples
        | prototipoDeFuncion
        ;

declaVarSimples
        : tipoDato { strncpy(buffer_auxiliar, $1, sizeof(buffer_auxiliar)-1); free($1); } listaVarSimples ';'
        ;

listaVarSimples
        : unaVarSimple
	| listaVarSimples ',' unaVarSimple
        ;

unaVarSimple        
    : IDENTIFICADOR {
        raizTS = insertarSimbolo(raizTS, $1, buffer_auxiliar, "variable", @1.first_line, @1.first_column, raizErrores);
      }
    | IDENTIFICADOR '=' exp {
        raizTS = insertarSimbolo(raizTS, $1, buffer_auxiliar, "variable", @1.first_line, @1.first_column, raizErrores);
      }
    | IDENTIFICADOR '=' error {
        raizTS = insertarSimbolo(raizTS, $1, buffer_auxiliar, "variable", @1.first_line, @1.first_column, raizErrores);
        yyerrok;
        ;
      }



inicializacion		
        : '=' '('exp')'
        ;

/* Lista de parámetros de funciones (simple): (tipo nombre) separados por coma, o void */
parametro
        : tipoBasico IDENTIFICADOR {
            char *resultado = malloc(strlen($1) + strlen(" ") + strlen($2) + 1);
            strcpy(resultado, $1);
            strcat(resultado, " ");
            strcat(resultado, $2);
            free($1);
            $$ = resultado;
        }
        | tipoBasico { $$ = $1; }
        ;

listaParametros
        : parametro { $$ = $1; }
        | listaParametros ',' parametro {
            char *resultado = malloc(strlen($1) + strlen(", ") + strlen($3) + 1);
            strcpy(resultado, $1);
            strcat(resultado, ", ");
            strcat(resultado, $3);
            free($1);
            free($3);
            $$ = resultado;
        }
        ;

parametros
        : VOID { $$ = strdup("void"); }
        | listaParametros { $$ = $1; }
        ;

prototipoDeFuncion
        : tipoBasico IDENTIFICADOR '(' parametros ')' ';' {
            raizFunciones = agregarFuncion(raizFunciones, $2, $1, $4 ? $4 : "void", 0, @1.first_line);
            raizTS = insertarSimbolo(raizTS, $2, $1, "funcion", @2.first_line, @2.first_column, raizErrores);
            if ($1) free($1);
            if ($4) free($4);
          }
        ;
definicionDeFuncion
        : tipoBasico IDENTIFICADOR '(' parametros ')' sentCompuesta {
            raizFunciones = agregarFuncion(raizFunciones, $2, $1, $4 ? $4 : "void", 1, @1.first_line);
            raizTS = insertarSimbolo(raizTS, $2, $1, "funcion", @2.first_line, @2.first_column, raizErrores);
            if ($1) free($1);
            if ($4) free($4);
          }
        ;

%%
/* Fin de la sección de reglas gramaticales */

/* Inicio de la sección de epílogo (código de usuario) */

int main(int argc, char *argv[]) {
        inicializarUbicacion();

        #if YYDEBUG
                yydebug = 1;
        #endif

        FILE *file = NULL;
        if (argc >= 2) {
                file = fopen(argv[1], "r");
                if (file == 0)  
                        return 1; 
                
                yyin = file;
        }

        yyparse();

        imprimirVariablesDeclaradas(raizTS);
        imprimirFunciones(raizFunciones);
        imprimirErrores(raizErrores);
        imprimirEstructurasNoReconocidas(raizEstructurasNoReconocidas);
        imprimirCadenaNoReconocida(raizNoReconocida);
        
        if (file) 
                fclose(file);
        
        return 0;
}
	/* Definición de la funcion yyerror para reportar errores, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char* literalCadena) {
        fprintf(stderr, "Bison: %d:%d: %s\n", yylloc.first_line, yylloc.first_column, literalCadena);
}

/* Fin de la sección de epílogo (código de usuario) */