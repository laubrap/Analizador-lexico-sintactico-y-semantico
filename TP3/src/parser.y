/* Calculadora de notación polaca inversa */

/* Inicio de la seccion de prólogo (declaraciones y definiciones de C y directivas del preprocesador) */
%{
#include <stdio.h>
#include <math.h>

#include "general.h"

	/* Declaración de la funcion yylex del analizador léxico, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla cada vez que solicite un nuevo token */
extern int yylex(void);
	/* Declaracion de la función yyerror para reportar errores, necesaria para que la función yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char*);
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

%token AUTO REGISTER STATIC EXTERN TYPEDEF
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE UNSIGNED SIGNED
%token CONST VOLATILE
%token STRUCT UNION
%token ENUM
%token CASE DEFAULT
%token IF ELSE SWITCH
%token DO WHILE FOR
%token GOTO CONTINUE BREAK RETURN SIZEOF

%token INCREMENTO DECREMENTO
%token MAS_IGUAL MENOS_IGUAL MULTIPLICAR_IGUAL DIVIDIR_IGUAL
%token IGUAL_IGUAL NEGADO_IGUAL
%token MAYOR_IGUAL MENOR_IGUAL AND OR

        /* */
%type <unsigned_long_type> exp

	/* Para especificar el no-terminal de inicio de la gramática (el axioma). Si esto se omitiera, se asumiría que es el no-terminal de la primera regla */
%start input

/* Fin de la sección de declaraciones de Bison */

/* Inicio de la sección de reglas gramaticales */
%%

input
        : /* intencionalmente se deja el resto de esta línea vacía: es la producción nula */
        | input line
        ;

line
        : '\n'
        | exp '\n'  { printf ("El resultado de la expresion es: %lu\n", $1); YYACCEPT; } /* la macro 'YYACEPT;' produce que la función yyparse() retorne inmediatamente con valor 0 */
        ;

exp
        : expAsignacion
        ;

expAsignacion
        : expCondicional
        | expUnaria '=' expAsignacion {$$ = $1 = $3}
        | expUnaria '+=' expAsignacion {$$ = $1 += $3}
        | expUnaria '-=' expAsignacion {$$ = $1 -= $3}
        | expUnaria '*=' expAsignacion {$$ = $1 *= $3}
        | expUnaria '/=' expAsignacion {$$ = $1 /= $3}
        ;

expCondicional
        : expOr
        ;

expOr
        : expAnd
        | expOr '||' expAnd {$$ = $1 || $3}
        ;

expAnd
        : expIgualdad
        | expAnd '&&' expIgualdad {$$ = $1 && $3}
        ;

expIgualdad
        : expRelacional
        | expIgualdad '==' expRelacional {$$ = $1 == $3}
        | expIgualdad '!=' expRelacional {$$ = $1 != $3}
        ;

expRelacional
        : expAditiva
        | expRelacional '>=' expAditiva {$$ = $1 >= $3}
        | expRelacional '>' expAditiva  {$$ = $1 > $3}
        | expRelacional '<=' expAditiva {$$ = $1 <= $3}
        | expRelacional '<' expAditiva {$$ = $1 < $3}
        ;

expAditiva
        : expMultiplicativa
        | expAditiva '+' expMultiplicativa {$$ = $1 + $3}
        | expAditiva '-' expMultiplicativa {$$ = $1 - $3}
        ;

expMultiplicativa
        : expUnaria
        | expMultiplicativa '*' expUnaria {$$ = $1 * $3}
        | expMultiplicativa '/' expUnaria {$$ = $1 / $3}
        ;

expUnaria
        : expPostfijo
        | INCREMENTO expUnaria {$$ = INCREMENTO $2}
        | DECREMENTO expUnaria {$$ = DECREMENTO $2}
        | expUnaria INCREMENTO {$$ = $1 INCREMENTO}
        | expUnaria DECREMENTO {$$ = $1 DECREMENTO}     
        | '&'expUnaria {$$ = & $2}
        | '*'expUnaria {$$ = $1 * $2}
        | '-'expUnaria {$$ = $1 - $2}
        | '!'expUnaria {$$ =  !$2}
        ;

expPostfijo
        : expPrimaria
        | expPostfijo '['exp']'
        | expPostfijo '('listaArgumentos')'
        ;

listaArgumentos
        : expAsignacion
        | listaArgumentos ',' expAsignacion
        ;
        
expPrimaria
        : IDENTIFICADOR
        | DECIMAL
        | OCTAL
        | HEXA
        | REAL
        | '('exp')'
        ;

// BNF de sentencias

sentencia
        :sentCompuesta 
        | sentExpresion 
        | sentSeleccion 
        | sentIteracion 
        | sentSalto
        ;

sentCompuesta
        : listaDeclaraciones
        | listaSentencias
        ;

listaDeclaraciones
        :declaracion
        | listaDeclaraciones declaracion
        ;

listaSentencias
        : sentencia
        | listaSentencias sentencia
        ;

sentExpresion
        : '('exp')'
        ;

sentSeleccion
        : IF '('exp')' sentencia
        | IF '('exp')' sentencia ELSE sentencia
        | IF error
        ;
        
sentIteracion
        : WHILE '('exp')' sentencia
	| DO sentencia WHILE '('exp')'
        | FOR '(' '('exp')' ; '('exp')' ; '('exp')' ')' sentencia
        | FOR '(' '('')' ; '('exp')' ; '('exp')' ')' sentencia
        | FOR '(' '('exp')' ; '('')' ; '('exp')' ')' sentencia
        | FOR '(' '('exp')' ; '('exp')' ; '('')' ')' sentencia
        | FOR '(' '('exp')' ; '('')' ; '('')' ')' sentencia
        | FOR '(' '('')' ; '('')' ; '('')' ')' sentencia
        | WHILE error
        | FOR error
        | DO error
        ;

sentSalto
        : RETURN '('exp')'
        ;

// BNF de las Declaraciones

declaracion
        : declaVarSimples
        ;

declaVarSimples
        : tipoDato listaVarSimples 
        ;

tipoDato
        : INT DOUBLE CHAR
        ;

listaVarSimples
        :unaVarSimple
	| listaVarSimples unaVarSimple
        ;

unaVarSimple	
        :identificador inicializacion
        ;

inicializacion		
        : = '('exp')'
        ;


%%
/* Fin de la sección de reglas gramaticales */

/* Inicio de la sección de epílogo (código de usuario) */

int main(int argc, char *argv[]) {
        inicializarUbicacion();

        #if YYDEBUG
                yydebug = 1;
        #endif

        while(1) {
                printf("Ingrese una expresion aritmetica en notacion polaca inversa para resolver:\n");
                printf("(La funcion yyparse ha retornado con valor: %d)\n\n", yyparse());
                /* Valor | Significado */
                /*   0   | Análisis sintáctico exitoso (debido a un fin de entrada (EOF) indicado por el analizador léxico (yylex), ó bien a una invocación de la macro YYACCEPT) */
                /*   1   | Fallo en el análisis sintáctico (debido a un error en el análisis sintáctico del que no se pudo recuperar, ó bien a una invocación de la macro YYABORT) */
                /*   2   | Fallo en el análisis sintáctico (debido a un agotamiento de memoria) */
        }

        pausa();
        return 0;
}

	/* Definición de la funcion yyerror para reportar errores, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char* literalCadena) {
        fprintf(stderr, "Bison: %d:%d: %s\n", yylloc.first_line, yylloc.first_column, literalCadena);
}

/* Fin de la sección de epílogo (código de usuario) */