
/* Inicio de la sección de definiciones. Aquí: */
    /* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
        /* De esas formas podemos poner declaraciones y definiciones de C y directivas del preprocesador */
    /* 2. Los comentarios (sólo hay de múltiples líneas) sin sangría también se copian tal cual al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

%{

#include "misFunciones.h"

int sumaDecimales = 0;

int acumuladorIdentificadores = 0;

nodoIdentificadores *raizIdentificador = NULL;

nodoLiteralCadena *raizLiterales = NULL;

nodoDecimal * raizDecimal = NULL;

nodoHexadecimal * raizHexadecimal = NULL;

nodoOctal * raizOctal = NULL;

%}

    /* La siguiente línea define explícitamente a yytext como un puntero a un caracter ( char* yytext; ). Ésta es la opción por defecto si no se pone nada. */
%pointer
    /* Con la siguiente opción la función de análisis int yylex(void); se comporta como si en la sección de usuario existiera la función int yywrap(void) return 1; la cual devuelve verdadero (no-cero), haciendo que una vez que la función de análisis int yylex(void) reciba una indicación de EOF desde YY_INPUT, asuma que no hay nada más para analizar de yyin y finalice (haciendo un return 0;) */
%option noyywrap

    /* Condiciones de arranque inclusivas */
/* %s */
    /* Condiciones de arranque exclusivas */
/* %x */

    /* Declaraciones con cada nombre y su definición; se utilizan para simplificar las reglas */
/* digito [0-9] */
digito [0-9]
digitoNoCero [1-9]
digitoOctal [0-7]
digitoHexa [0-9a-fA-F]
noDigito [_a-zA-Z]
sufijoEntero ([uU][lL]?|[lL][uU]?)
sufijoReal ([fF][lL]?|[lL][fF]?)
escapeSimple [abfnrtv'\"\?\\]
exponente (e[+-]?{digito}*)


/* Fin de la sección de definiciones */

/* Inicio de la sección de reglas. Aquí: */
    /* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
        /* Esto podría utilizarse para declarar variables que son locales a la rutina de análisis léxico y (después de las declaraciones) al código que debe ejecutarse siempre que se entra a la rutina de análisis léxico */
    /* 2. NO pueden hacerse comentarios sin sangría, ya que estos no se copian literalmente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
%%

{digitoNoCero}{digito}*{sufijoEntero}? { 
    raizDecimal = agregarDecimales(raizDecimal,atoi(yytext));

}


0{digitoOctal}*{sufijoEntero}? { 
    raizOctal = agregarOctal(raizOctal, yytext);
    
}


0[xX]{digitoHexa}+{sufijoEntero}? { 
    raizHexadecimal = agregarHexadecimal(raizHexadecimal, yytext);
    
}


{noDigito}({noDigito}|{digito})* {
    raizIdentificador = agregarALista(raizIdentificador, yytext);
}



{digito}*((\.{digito}*{exponente}?)|{exponente}){sufijoReal}? { 
    fprintf(yyout,"\nEncontre una constante real: %s\n", yytext); 
    
}


'([^'\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)' { 
    fprintf(yyout,"\nEncontre un caracter: %s\n", atoi(yytext)); 
    
    }


\"([^\"\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)*\" { 
    raizLiterales = literalesCadena(raizLiterales, yytext, yyleng - 2);
}
%%
int main(int argc, char *argv[]) {

    yyin = fopen ("entrada.txt","r" );
    yyout = fopen ("salida.txt", "w");
    yylex();

    imprimirIdentificadores(raizIdentificador,yyout);
    imprimirLiteralesCadena(raizLiterales,yyout);
    imprimirDecimales(raizDecimal,yyout);
    imprimirHexadecimales(raizHexadecimal,yyout);
    imprimirOctal(raizOctal, yyout);

    fclose(yyin);
    fclose(yyout);

    return 0;
}


/* Fin de la sección de código de usuario */