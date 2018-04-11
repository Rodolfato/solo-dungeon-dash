#include <stdio.h>
#include <stdlib.h>

int ** generarTablero(){

    /*  Función que genera un array con "12" filas y "9" columnas, asemejando una matriz que a su vez asemeja un tablero de juego.
        El inicio del tablero está dado por el "8" y el final por el "9".
        Números "2" simbolizan casilleros inválidos. */

    int ** tablero = (int **)malloc(12 * sizeof(int *));
    int fila;
    int columna;

    for(fila = 0; fila < 12; fila++){

        tablero[fila] = (int *)malloc(9 * sizeof(int)); 

    }

    for(fila = 0; fila < 12; fila++){

        for(columna = 0; columna < 9; columna++){

            if(fila == 0 && columna != 4)
                tablero[fila][columna] = 2;

            if(fila == 0 && columna == 4)
                tablero[fila][columna] = 9;

            if(fila > 0 && fila < 10)
                tablero[fila][columna] = 0;

            if(fila == 11 && columna != 4)
                tablero[fila][columna] = 2;

            if(fila == 11 & columna == 4)
                tablero[fila][columna] = 8;

        }
    }

    return tablero;

}

int liberar_tablero(int ** tablero){

    int fila;

    for(fila = 0; fila < 12; fila++){

        free(tablero[fila]);
    }

    free(tablero);
}

int ** ingresarJugada(int ** tableroModificado){
    
    int jugada;
    printf("Ingrese su jugada:\n>>");
    scanf("%d", &jugada);

    int j = 4;
    int i = 11;

    if(jugada == 1)
        tableroModificado[i - 1][j - 1] = 1;

    if(jugada == 2)
        tableroModificado[i - 1][j] = 1;

    if(jugada == 3)
        tableroModificado[i - 1][j + 1] = 1;

    if(jugada == 4)
        tableroModificado[i][j + 1] = 1;

    if(jugada == 5)
        tableroModificado[i + 1][j + 1] = 1;

    if(jugada == 6)
        tableroModificado[i + 1][j] = 1;

    if(jugada == 7)
        tableroModificado[i + 1][j - 1] = 1;

    if(jugada == 8)
        tableroModificado[i][j - 1] = 1;

    return tableroModificado;

} 

int imprimirTablero(int ** tablero){

    int fila;
    int columna;
    printf("\n");
    for ( fila = 0; fila < 12; fila++ ) {

        for ( columna = 0; columna < 9; columna++ ) {

            if(columna == 8){

            printf("%d\n", tablero[fila][columna]);
            }

            else
            printf("%d", tablero[fila][columna]);
        }
    }

    return 0;
}


int main(){

    int ** tablero;
    tablero = generarTablero();

    imprimirTablero(tablero);

    liberar_tablero(tablero);

    return 0;
}





