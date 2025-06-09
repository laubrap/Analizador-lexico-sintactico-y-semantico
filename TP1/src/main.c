#include "TP1.h"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Uso: %s <ARCHIVO_ENTRADA> [...]\n", argv[0]);
        return EXIT_FAILURE;
    };
    FILE *entrada = fopen(argv[1], "r");
        if(entrada == NULL) {
            printf("%s: Error al intentar abrir el archivo: %s\n", argv[1], strerror(errno));
            return EXIT_FAILURE;
        }

    scanner(entrada, stdout);
    fclose (entrada);
    return EXIT_SUCCESS;
}

