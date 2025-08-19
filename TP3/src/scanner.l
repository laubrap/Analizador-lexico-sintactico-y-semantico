
/* Inicio de la sección de definiciones. Aquí: */
    /* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
        /* De esas formas podemos poner declaraciones y definiciones de C y directivas del preprocesador */
    /* 2. Los comentarios (sólo hay de múltiples líneas) sin sangría también se copian tal cual al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

%{

#include "general.h"

/* Es indispensable que incluyamos el archivo de cabecera con las definiciones de YACC (*.tab.h) que se genera a partir del archivo fuente de YACC (*.y) */
#include "parser.tab.h"

%}

    /* La siguiente línea define explícitamente a yytext como un puntero a un caracter ( char* yytext; ). Ésta es la opción por defecto si no se pone nada. */
%pointer
    /* Con la siguiente opción la función de análisis int yylex(void); se comporta como si en la sección de usuario existiera la función int yywrap(void) return 1; la cual devuelve verdadero (no-cero), haciendo que una vez que la función de análisis int yylex(void) reciba una indicación de EOF desde YY_INPUT, asuma que no hay nada más para analizar de yyin y finalice (haciendo un return 0;) */
%option noyywrap

    /* Condiciones de arranque inclusivas */
/* %s */
    /* Condiciones de arranque exclusivas */
%x tokenNoReconocido

    /* Declaraciones con cada nombre y su definición; se utilizan para simplificar las reglas */
digito [0-9]
digitoNoCero [1-9]
digitoOctal [0-7]
digitoHexa [0-9a-fA-F]
noDigito [_a-zA-Z]
sufijoEntero ([uU][lL]?|[lL][uU]?)
sufijoReal ([fF][lL]?|[lL][fF]?)
escapeSimple [abfnrtv'\"\?\\]
exponente (e[+-]?{digito}*)
almacenamiento (auto|register|static|extern|typedef)
especificadoresDeTipo (void|char|short|int|long|float|double|signed|unsigned)
calificadoresDeTipo (const|volatile)
calificadoresDeUnion (struct|union)
calificadoresDeEnum (enum)
etiquetas (case|default)
seleccion (if|else|switch)
iteracion (do|while|for)
salto (goto|continue|break|return)
unario (sizeof)
puntuaciones ("["|"]"|"("|")"|"{"|"}"|"."|"->"|"++"|"--"|"&"|"*"|"+"|"-"|"̃ "|"!"|"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"|"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|"?"|":"|";"|"..."|","|"#"|"##")
noReconocida ([^ \t\n])

/* Fin de la sección de definiciones */

/* Inicio de la sección de reglas. Aquí: */
    /* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
        /* Esto podría utilizarse para declarar variables que son locales a la rutina de análisis léxico y (después de las declaraciones) al código que debe ejecutarse siempre que se entra a la rutina de análisis léxico */
    /* 2. NO pueden hacerse comentarios sin sangría, ya que estos no se copian literalmente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
%%

reinicializarUbicacion();

{almacenamiento}|{especificadoresDeTipo}|{calificadoresDeEnum}|{etiquetas}|{seleccion}|{iteracion}|{salto}|{unario}|{calificadoresDeTipo}|{calificadoresDeUnion} { 
    raizPalabraReservada = agregarReservada(raizPalabraReservada, yytext, columna_actual, linea_actual);
    columna_actual += yyleng;
    yylval.string = strdup(yytext);
    return devolverAParser(yytext);
}

    
{digitoNoCero}{digito}*{sufijoEntero}? { 
    raizDecimal = agregarDecimales(raizDecimal,atoi(yytext));
    columna_actual += (yyleng);
    yylval.numeros = atoi(yytext);
    return DECIMAL;
}


0{digitoOctal}*{sufijoEntero}? { 
    raizOctal = agregarOctal(raizOctal, yytext);
    columna_actual += yyleng;
    yylval.numeros = strtol(yytext, NULL, 8);
    return OCTAL;
}


0[xX]{digitoHexa}+{sufijoEntero}? { 
    raizHexadecimal = agregarHexadecimal(raizHexadecimal, yytext);
    columna_actual += yyleng;
    yylval.numeros = strtol(yytext, NULL, 16);
    return HEXA;
}


{noDigito}({noDigito}|{digito})* {
    raizIdentificador = agregarIdentificadores(raizIdentificador, yytext);
    columna_actual += yyleng;
    yylval.string = strdup(yytext);
    return IDENTIFICADOR;
}


{digito}*((\.{digito}*{exponente}?)|{exponente}){sufijoReal}? { 
    raizReal = agregarReal(raizReal, yytext);
    columna_actual += yyleng;
    return REAL;
}


'([^'\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)' { 
    raizCaracter = agregarCaracter(raizCaracter, yytext);
    columna_actual += yyleng;
    yylval.caracter = strdup(yytext);
    return CARACTER;
}


\"([^\"\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)*\" { 
    raizLiterales = agregarLiteralesCadena(raizLiterales, yytext, yyleng - 2);
    columna_actual += yyleng;
    yylval.string = strdup(yytext);
    return LITERAL_CADENA;
}

{puntuaciones} {
    raizPuntuaciones = agregarPuntuacion(raizPuntuaciones, yytext);
    columna_actual += yyleng;
    yylval.string = strdup(yytext);
    return devolverAParser(yytext);
}


/* "+" { yylloc.last_column += yyleng; return '+'; }

"-" { yylloc.last_column += yyleng; return '-'; }

"*" { yylloc.last_column += yyleng; return '*'; }

"/" { yylloc.last_column += yyleng; return '/'; }

"^" { yylloc.last_column += yyleng; return '^'; } */

[ \t]+ { yylloc.first_column = yylloc.last_column += yyleng; }

\n {
        yylloc.first_line = yylloc.last_line += yyleng;
        yylloc.first_column = yylloc.last_column = INICIO_CONTEO_COLUMNA;
        return '\n';
    }

[^ \t\n] { yylloc.last_column += yyleng; fprintf(stderr, "Flex: %d:%d: Error lexico: token no reconocido: %s", yylloc.first_line, yylloc.first_column, yytext); BEGIN(tokenNoReconocido); }
{noReconocida} { 
    buffer = strdup(yytext);
    columna_actual += yyleng;
    BEGIN(tokenNoReconocido); 
}

<tokenNoReconocido>{
    <<EOF>> {
        fprintf(stderr, "\n");
        BEGIN(INITIAL);
    }

    [ ] {
        columna_actual += 1;
        BEGIN(INITIAL);
    }
    [\t] {
        columna_actual += 4;
        BEGIN(INITIAL);
    }

    \n {
        linea_actual += 1;
        columna_actual = INICIO_CONTEO_COLUMNA;

        BEGIN(INITIAL);
    }

    [^ \t\n]+ {
        int columna_inicio = columna_actual - 1;
        if(buffer == NULL){
            buffer = calloc(yyleng + 1, sizeof(char));
            strncpy(buffer, yytext, yyleng);
        }
        else{
            size_t actual_len = strlen(buffer);
            buffer = realloc(buffer, actual_len + yyleng + 1);
            strncat(buffer, yytext, yyleng);
        }

        raizNoReconocida = agregarCadenaNoReconocida(raizNoReconocida, buffer, columna_inicio, linea_actual);
        columna_actual += yyleng;

        free(buffer);
        buffer = NULL;
        BEGIN(INITIAL);
    }
}


    /* Reglas por defecto de Flex: */
        /* <*>.|\n { ECHO; } */
            /* (ECHO; escribe yytext en la salida del escáner: FILE* yyout (variable global a la cual por defecto se le asigna stdout)) */
        /* <<EOF>> { yyterminate(); } */
            /* (yyterminate(); hace que la función yylex finalice retornando un 0, indicando un fin-de-entrada (EOF)) */

%%
/* Fin de la sección de reglas */ 

/* Inicio de la sección de código de usuario, la cual: */
	/* 1. Se utiliza para rutinas de complemento que llaman al analizador léxico o son llamadas por este; la presencia de esta sección es opcional */
    /* 2. Toda esta sección simplemente se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

/* Fin de la sección de código de usuario */










