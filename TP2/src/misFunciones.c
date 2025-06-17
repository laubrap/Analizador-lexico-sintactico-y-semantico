#include "misFunciones.h"


int estaEnLista(nodo* raiz, char* elemento){
    while(raiz->sgte != NULL){
        if(strcmp(raiz->nombreIdentificador, elemento) == 0) {
            raiz = raiz->sgte;
            return 1;
        }
        return 0;
    }
}

 nodo * agregarALista(nodo* raiz, char* elementoParaAgregar){

   nodo *aux = raiz;
   
   if(estaEnLista(raiz,elementoParaAgregar)){
    raiz->contador += 1;
   }
   
   else{
        if(aux->sgte==NULL){
            aux->nombreIdentificador = (char*)malloc(strlen(elementoParaAgregar));
            strcpy(aux->nombreIdentificador, elementoParaAgregar);
            aux->sgte = NULL;
            aux->contador = 1;
        }
    
        raiz->nombreIdentificador = (char*)malloc(strlen(elementoParaAgregar));
        raiz->sgte = aux;
        raiz->contador = 1;

    }
return raiz;
}

int cantidadDeVecesQueAparece(nodo* lista, char* paraContar){

    lista = agregarALista(lista, paraContar);

    return lista->contador;

}

// Enteros

int obtenerValorDeOctal(int octal) {
    int decimal = 0, base = 1;
    while (octal > 0) {
        int digito = octal % 10;
        decimal += digito * base;
        base *= 8;
        octal /= 10;
    }
    return decimal;
}

int obtenerValorDeHexadecimal(char* hex) {
    int decimal = 0;
    int valor;
    hex[1] = '0';
    for (int i = 0 ; hex[i] != '\0'; i++) {
        if (hex[i] >= '0' && hex[i] <= '9')
            valor = hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            valor = hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            valor = hex[i] - 'a' + 10;
        decimal = decimal * 16 + valor;
    }
    return decimal;
}