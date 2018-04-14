#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int lanzarDado(){

    int resultado;
    time_t t;

    srand((unsigned) time(&t));
    resultado = rand() % ((6 + 1 - 1) + 1);

    while(resultado == 0){
        resultado = rand() % ((6 + 1 - 1) + 1);
    }

    printf("\nSu dado entregó un %d\n", resultado);


    return resultado;
}

int * convertirJugada(int jugada, int fila, int columna){

    int filaConvertida;
    int columnaConvertida;
    static int conversion[2];

    if(jugada == 1){
        filaConvertida = fila - 1;
        columnaConvertida = columna - 1;
    }

    if(jugada == 2){
        filaConvertida = fila - 1;
        columnaConvertida = columna;

    }

    if(jugada == 3){
        filaConvertida = fila - 1;
        columnaConvertida = columna + 1;

    }

    if(jugada == 4){
        filaConvertida = fila;
        columnaConvertida = columna + 1;

    }

    if(jugada == 5){
        filaConvertida = fila + 1;
        columnaConvertida = columna + 1;
    }

    if(jugada == 6){
        filaConvertida = fila + 1;
        columnaConvertida = columna;
        
    }

    if(jugada == 7){
        filaConvertida = fila + 1;
        columnaConvertida = columna - 1;
    }

    if(jugada == 8){
        filaConvertida = fila;
        columnaConvertida = columna - 1;
    }

    conversion[0] = filaConvertida;
    conversion[1] = columnaConvertida;

    return conversion;
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

int * generarMochila(){
    static int bolso[5];

    //Pociones
    bolso[0] = 0;
    //Tesoros
    bolso[1] = 0;
    //Dados de ataque
    bolso[2] = 1;
    //Dados de defensa
    bolso[3] = 1;
    //Vida
    bolso[4] = 17;

    return bolso;


}

void imprimirMochila(int * bolso){
    printf("\n__________________________________\n");
    printf("\nDados de Ataque: %d   Dados de Defensa: %d\n\nVida: %d\n\nPociones: %d            Tesoros: %d\n", bolso[2], bolso[3], bolso[4], bolso[0], bolso[1]);
    printf("\n__________________________________\n");
}

int batallar(int bolso, int dadosAtaqueEnemigo, int dadosDefensaEnemigo, int dadosAtaqueJugador, int dadosDefensaJugador){
// bolso = [pocion, tesoro, dadosAtaque, dadosDefensa, vida]


}

int * encontrarEntidad(int ** tablero){

    int * ubicacion;
    static int bolso[5];
    int dado;
// bolso = [pocion, tesoro, dadosAtaque, dadosDefensa, vida]
    ubicacion = encontrarJugador(tablero);

    if(ubicacion[0] == 10){

        dado = lanzarDado();

        if(dado == 1){
            printf("\nEncontraste una poción.\n");
            bolso[0] += 1;
        }

        if(dado > 1 && dado < 5){
            printf("\nUn OGRO bloquea tu camino.\n'Pelea insecto'\n");
        }

        if(dado == 5){
            printf("\nUna mosca vuela de pared en pared...\n");
        }

        if(dado == 6){
            printf("\nEncontraste una poción.");
            bolso[0] += 1;
        }

    }

    if(ubicacion[0] == 9){

        dado = lanzarDado();

        if(dado == 1){
            printf("\nUn OGRO bloquea tu pasar\n'De aquí no pasas'\n");

        }

        if(dado == 2){
            printf("\nVes un LOBO marcar su territorio.\nTu presencia no le es grata...\n");

        }

        if(dado == 3){
            printf("\nVes salir vapor de varias calderas en el suelo...\n");
        }

        if(dado == 4){
            printf("\nVes el cadáver de uno de tus enanos compatriotas...\nAvanzas con un poco de miedo...\n");

        }

        if(dado == 5){
            printf("\nEl olor a descomposición casi no te deja avanzar...\nTu sentido del orgullo te obliga a seguir...\n");
        }

        if(dado == 6){
            printf("\nUn cofre resplandeciente hace brillar tu alrededor.\nTu instinto avaricioso de enano te obliga a guardar sus contenidos...\nHas adquirido un nuevo tesoro.\n");
            bolso[1] += 1;

        }

    }

    if(ubicacion[0] == 8){

        dado = lanzarDado();

        if(dado == 1){
            printf("\nUn OGRO te mira al pasar.\nTu presencia no le agrada...\n");
        }

        if(dado == 2){
            printf("\nUn LOBO de apariencia robusta come un enano que yace muerto.\nCarne fresca...\n");

        }

        if(dado == 3){
            printf("\nUn ESQUELETO que asemeja un elfo del bosque saca sus armas al verte pasar...\n");
        }

        if(dado == 4){
            printf("\nUna bolsa reposa al lado de un cadáver irreconocible.\nSus contenidos son perlas brillantes.\nHas adquirido un tesoro.\n");
            bolso[1] += 1;
        }

        if(dado == 5){
            printf("\nUna botella que contiene un élixir parecido al de los elfos del Mirkwood yace frente a ti.\nDecides guardarla.\nHas adquirido una poción.\n");
            bolso[0] += 1;
        }

        if(dado == 6){
            printf("\nLa vibración de las moscas a tu alrededor te molesta de sobremanera...\n");
        }
    }

    if(ubicacion[0] == 7){

        dado = lanzarDado();

        if(dado == 1){
            printf("\nUn OGRO horriblemente deformado cruza sus cejas al verte pasar...\n");

        }

        if(dado == 2){
            printf("\nUn LOBO arrastra su cola mientras se acerca en tu dirección...·\n");
        }

        if(dado == 3){
            printf("\nUn robusto ESQUELETO hace círculos con una espada de plata al darse cuenta de tu presencia...\n");

        }

        if(dado == 4){
            printf("\nUn humanoide jorobado de apariencia robusta se dispone a pelear...\n'Mis habilidades de GUERRERO son insuperables'\n ");
        }

        if(dado == 5){
            printf("\nQué bello el resplandor de éstas monedas...\nLas guardas en tu morral.\nHas adquirido un tesoro.\n");
            bolso[1] += 1;
        }

        if(dado == 6){
            printf("\nLa penumbra apenas te deja ver tu camino.\nDecides avanzar con cautela...\n");

        }
    }   

    return bolso;
}

int validarJugada(int ** tablero, int jugada, int fila, int columna){
    //Validación de un cuadro en el cual el jugador ya estuvo.
    int * conversion;
    //Se convierte la jugada que el jugador quiere ingresar a "coordenadas" utilizables en el array que simboliza el tablero.
    conversion = convertirJugada(jugada, fila, columna);
    //Se usan estas "coordenadas" para revisar si existe un "3" en el casillero elegido.
    if(tablero[conversion[0]][conversion[1]] == 3){
        //Si existe un 3 en el casillero elegido, entonces se le muestra un mensaje de error y se le pide que ingrese nuevamente su jugada.
        printf("\nUsted ya estuvo en este casillero, por favor elegir otra opción.\n");
        jugada = ingresarJugada();
        jugada = validarJugada(tablero, jugada, fila, columna);
    }

    //Validación del punto de partida.
    if(fila == 11 && columna == 4){
        //Jugadas válidas son 1, 2 ó 3.
        while(jugada >= 3 || jugada == 6){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la fila 10.
    if(fila == 10 && columna != 8 && columna != 0){
        //Jugadas válidas son 1, 2, 3, 4 ú 8.
        while(jugada > 4 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la esquina inferior izquierda.
    if(fila == 10 && columna == 0){
        //Jugadas válidas son 2, 3 ó 4.
        while(jugada > 4 || jugada == 1){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la esquina inferior derecha.
    if(fila == 10 && columna == 8){
        //Jugadas válidas son 1, 2 ó 8.
        while(jugada != 2 && jugada != 1 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }   

    //Validación de la fila 1.
    if(fila == 1 && columna != 0 && columna != 8  && columna != 3 && columna != 4 && columna != 5){
        //Jugadas válidas son 4, 5, 6, 7 ó 8.
        while(jugada != 4 && jugada != 5 && jugada != 6 && jugada != 7 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la esquina superior izquierda.
    if(fila == 1 && columna == 0){
        //Jugadas válidas son 4, 5 ó 6.
        while(jugada != 4 && jugada != 5 && jugada != 6){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la esquina superior derecha.
    if(fila == 1 && columna == 8){
        //Jugadas válidas son 6, 7 ó 8.
        while(jugada != 8 && jugada != 7 && jugada != 6){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación de la columna 0.
    if(columna == 0 && fila != 1 && fila != 10){
        //Jugadas válidas son 2, 3, 4, 5 ó 6.
        while(jugada == 7 || jugada == 8 || jugada == 1){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();

        }
    }

    //Validación de la columna 8.
    if(columna == 8 && fila != 1 && fila != 10){
        //Jugadas válidas son 1, 2, 6, 7 ú 8.       
        while(jugada == 3 || jugada == 4 || jugada == 5){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }


    //Validación de la esquina inferior izquierda del cuadro final del juego.
    if(fila == 1 && columna == 3){
        //Jugadas válidas son 3, 4, 5, 6, 7 ú 8.
        while(jugada == 1 || jugada == 2){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }

    }

    //Validación del cuadro anterior al cuadro final del juego.
    if(fila == 1 && columna == 4){
        //Jugadas válidas son 2, 4, 5, 6, 7 ú 8.
        while(jugada == 1 || jugada == 3){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
        }
    }

    //Validación del cuadro inferior derecho al cuadro final del juego.
    if(fila == 1 && columna == 5){
        //Jugadas válidas son 1, 4, 5, 6, 7 ú 8.
        while(jugada == 2 || jugada == 3){

            printf("\nJugada inválida\n");
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
    int * mochila;
    int ** tablero;
    int condicion;

    condicion = 0;
    tablero = generarTablero();
    mochila = generarMochila();


    imprimirTablero(tablero);
    imprimirMochila(mochila);

    while(condicion == 0){

        jugada = ingresarJugada();
        ubicacion = encontrarJugador(tablero);
        jugada = validarJugada(tablero, jugada, ubicacion[0], ubicacion[1]);

        tablero = modificarTablero(tablero, jugada);

        imprimirTablero(tablero);

        mochila = encontrarEntidad(tablero);
        imprimirMochila(mochila);
    }

    liberarTablero(tablero);

    return 0;
}





