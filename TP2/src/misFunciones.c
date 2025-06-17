#include "misFunciones.h"


int estaEnLista(nodo* raiz, char* aBuscar){
    while(raiz->sgte != NULL){
        if(strcmp(raiz->nombreIdentificador, aBuscar) == 0) {
            raiz = raiz->sgte;
            return 1;
        }
        return 0;
    }
}

 nodo * agregarALista(nodo* lista, char* paraAgregar){

   nodo *aux = lista;
   
   if(estaEnLista(lista,paraAgregar)){
     
    lista->contador += 1;

   }else{
        if(aux->sgte==NULL){
            aux->nombreIdentificador = (char*)malloc(strlen(paraAgregar));
            strcpy(aux->nombreIdentificador, paraAgregar);
            aux->sgte = NULL;
            aux->contador = 1;
        }
   
   lista->nombreIdentificador = paraAgregar;
   lista->sgte = aux;
   lista->contador = 1;

}
return lista;
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
    int longitud = strlen(hex);
    hex[1] = '0';
    for (int i = longitud - 1 ; hex[i] != '\0'; i--) {
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