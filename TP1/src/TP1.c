#include "TP1.h"

columna caracter_a_columna(int caracter){
    switch(caracter){

        case '0':
            return COL_0;
        case '1': case '2':  case '3': case '4': case '5': case '6': case '7':
            return COL_1_7;
        case '8': case '9':
            return COL_8_9;  
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            return COL_AF_af;
        case 'x': case 'X':
            return COL_xX;
        default:
            return COL_otro_caracter;

    } 
}

void fin_de_cadena (estado estado, FILE * salida ){
    
    if (estado == Q2){
        fprintf(salida, "\t\tDECIMAL\n");
    } 
    else if (estado == Q1 || estado == Q5){
        fprintf(salida, "\t\tOCTAL\n");
    } 
    else if (estado == Q4){
        fprintf(salida, "\t\tHEXADECIMAL\n");
    } 
     else {
         fprintf(salida, "\t\tNO RECONOCIDA\n");
     }
}


void scanner (FILE* entrada, FILE *salida){
    int caracter;
    estado estado_actual = ESTADO_INICIAL;
    while((caracter = fgetc(entrada)) != EOF){
        if(caracter != CENTINELA){
            fputc(caracter, salida);
            estado_actual = tabla_transiciones[estado_actual][caracter_a_columna(caracter)];
        }else{
            fin_de_cadena(estado_actual, salida);
            estado_actual=ESTADO_INICIAL;
        }
    }
    fin_de_cadena(estado_actual,salida);
}

