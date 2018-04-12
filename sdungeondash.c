#include <stdio.h>
#include <stdlib.h>

int ** generarTablero(){

    /*  Función que genera un array de dos dimensiones con "12" "filas" y "9" "columnas", asemejando una matriz que a su vez asemeja un tablero de juego.
        El inicio del tablero está dado por el "1" y el final por el "9". 
        Espacios vacíos son representados con un "0" y el jugador con un "1".
        Espacios ya ocupados anteriormente por el jugador están representados por un "3".
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

            if(fila == 11 && columna == 4)
                tablero[fila][columna] = 1;

        }
    }

    return tablero;
}

int liberarTablero(int ** tablero){

    int fila;

    for(fila = 0; fila < 12; fila++){

        free(tablero[fila]);
    }

    free(tablero);
}

int ingresarJugada(){

    int jugada;
    printf("\nIngrese su jugada:\n>>");
    scanf("%d", &jugada);

    while(jugada > 8 || jugada <= 0){

        printf("Ingrese una jugada válida:\n>>");
        scanf("%d", &jugada);
    }

    return jugada;

}

int * encontrarJugador(int ** tablero){

    int fila;
    int columna;
    int filaEncontrada;
    int columnaEncontrada;

    static int ubicacion[2];

    for(fila = 0; fila < 12; fila++){
        for(columna = 0; columna < 9; columna++){

            if(tablero[fila][columna] == 1){
                filaEncontrada = fila;
                columnaEncontrada = columna;

            }
        }
    }

    ubicacion[0] = filaEncontrada;
    ubicacion[1] = columnaEncontrada;

    return ubicacion;

}

int validarJugada(int ** tablero, int jugada, int fila, int columna){

    //Validación del punto de partida.
    if(fila == 11 && columna == 4){
        //Jugadas válidas son 1, 2 ó 3.
        while(jugada >= 3){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la fila 10.
    if(fila == 10 && columna != 8 && columna != 0){
        //Jugadas válidas son 1, 2, 3, 4 ú 8.
        while(jugada > 4 && jugada != 8){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la esquina inferior izquierda.
    if(fila == 10 && columna == 0){
        //Jugadas válidas son 2,3 ó 4.
        while(jugada > 4 || jugada == 1){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la esquina inferior derecha.
    if(fila == 10 && columna == 8){
        //Jugadas válidas son 1, 2 ó 8.
        while(jugada != 2 && jugada != 1 && jugada != 8){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }   

    //Validación de la fila 1.
    if(fila == 1 && columna != 0 && columna != 8  && columna != 3 && columna != 4 && columna != 5){
        //Jugadas válidas son 4, 5, 6, 7 ó 8.
        while(jugada != 4 && jugada != 5 && jugada != 6 && jugada != 7 && jugada != 8){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la esquina superior izquierda.
    if(fila == 1 && columna == 0){
        //Jugadas válidas son 4, 5 ó 6.
        while(jugada != 4 && jugada != 5 && jugada != 6){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la esquina superior derecha.
    if(fila == 1 && columna == 8){
        //Jugadas válidas son 6, 7 ó 8.
        while(jugada != 8 && jugada != 7 && jugada != 6){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la columna 0.
    if(columna == 0 && fila != 1 && fila != 10){

        while(jugada == 7 || jugada == 8 || jugada == 1){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la columna 8.
    if(columna == 8 && fila != 1 && fila != 10){

        while(jugada == 3 || jugada == 4 || jugada == 5){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }


    //Validación de la esquina inferior izquierda del cuadro final del juego.
    if(fila == 1 && columna == 3){
        //Jugadas válidas son 3, 4, 5, 6, 7 ú 8.
        while(jugada == 1 || jugada == 2){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }

    }

    //Validación del cuadro anterior al cuadro final del juego.
    if(fila == 1 && columna == 4){

        while(jugada == 1 || jugada == 3){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación del cuadro inferior derecho al cuadro final del juego.
    if(fila == 1 && columna == 5){

        while(jugada == 2 || jugada == 3){

            printf("Jugada inválida\n");
            jugada = ingresarJugada();
        }
    }


    return jugada;
}

int ** modificarTablero(int ** tablero, int jugada){

    int * ubicacion;
    int fila;
    int columna;
    ubicacion = encontrarJugador(tablero);
    fila = ubicacion[0];
    columna = ubicacion[1];

    if(jugada == 1)
        tablero[fila - 1][columna - 1] = 1;

    if(jugada == 2)
        tablero[fila - 1][columna] = 1;

    if(jugada == 3)
        tablero[fila - 1][columna + 1] = 1;

    if(jugada == 4)
        tablero[fila][columna + 1] = 1;

    if(jugada == 5)
        tablero[fila + 1][columna + 1] = 1;

    if(jugada == 6)
        tablero[fila + 1][columna] = 1;

    if(jugada == 7)
        tablero[fila + 1][columna - 1] = 1;

    if(jugada == 8)
        tablero[fila][columna - 1] = 1;

    tablero[fila][columna] = 3;

    return tablero;

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

    int jugada;
    int * ubicacion;
    int ** tablero;
    int condicion;

    condicion = 0;
    tablero = generarTablero();

    imprimirTablero(tablero);

    while(condicion == 0){

        jugada = ingresarJugada();
        ubicacion = encontrarJugador(tablero);
        printf("%d", ubicacion[0]);
        printf("%d", ubicacion[1]);
        jugada = validarJugada(tablero, jugada, ubicacion[0], ubicacion[1]);
        tablero = modificarTablero(tablero, jugada);


        imprimirTablero(tablero);
    }

    liberarTablero(tablero);

    return 0;
}





