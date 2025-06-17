
/* Inicio de la sección de definiciones. Aquí: */
    /* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
        /* De esas formas podemos poner declaraciones y definiciones de C y directivas del preprocesador */
    /* 2. Los comentarios (sólo hay de múltiples líneas) sin sangría también se copian tal cual al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

%{

#include "misFunciones.h"

int sumaDecimales = 0;

int acumuladorIdentificadores = 0

nodo*lista = NULL;
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
    printf(yyout,"\nEncontre una constante entera decimal: %s\n", yytext, sumaDecimales += atoi(yytext));

}


0{digitoOctal}*{sufijoEntero}? { 
    printf(yyout,"\nEncontre una constante entera octal: %s\n", yytext); 
    
}


0[xX]{digitoHexa}+{sufijoEntero}? { 
    printf(yyout,"\nEncontre una constante entera hexadecimal: %s\n", yytext); 
    
}


{noDigito}({noDigito}|{digito})* { 
    printf(yyout,"\nLa palabra %s aparece : %s veces\n", yytext, agregarALaLista(lista,yytext));
    
}


{digito}*((\.{digito}*{exponente}?)|{exponente}){sufijoReal}? { 
    printf(yyout,"\nEncontre una constante real: %s\n", yytext); 
    
}


'([^'\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)' { 
    printf(yyout,"\nEncontre un caracter: %s\n", yytext); 
    
    }


\"([^\"\\]|\\{escapeSimple}|\\{digitoOctal}+|\\[xX]{digitoHexa}+)*\" { printf(yyout,"\nEncontre una literal cadena: %s\n", yytext, yyleng - 2 ); } // es por las comillas que se le resta 2


/*
    char* variable = "Algo
                        que tiene
                         enters en el medio"
*/

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

int main(int argc, char *argv[]) {

    yyin = fopen ("entrada.txt","r" );
    yyout = fopen ("salida.txt", "w");
    yylex();

    

    fclose(yyin);
    fclose(yyout);

    return 0;
}


/* Fin de la sección de código de usuario */