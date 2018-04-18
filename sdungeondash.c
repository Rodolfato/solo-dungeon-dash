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

void saltarMucho(){

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int presionarEnter(){

    printf("\nPresione 'Enter' para continuar.\n");
    getc(stdin);
    return 0;
}


int lanzarDado(){

    int resultado;

    resultado = rand() % ((6 + 1 - 1) + 1);

    while(resultado == 0){
        resultado = rand() % ((6 + 1 - 1) + 1);
    }

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
    getchar();

    while(jugada > 8 || jugada <= 0){

        printf("Ingrese una jugada válida:\n>>");
        scanf("%d", &jugada);
        getchar();
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

int buscarSeis(int * dadosLanzados, int largo){

    int seisEnc = 0;
    int contador;

    for(contador = 0; contador < largo; contador++){

        if(dadosLanzados[contador] == 6)
            seisEnc += 1;

    }

    return seisEnc;
}

int * beberPocion(int * bolso){

    saltarMucho();
    int opcion;

    if(bolso[0] > 0 && bolso[4] < 17){
        
        printf("\nAntes de seguir tu camino a través de la mina, veo que has perdido %d punto(s) de vida y tienes en tu poder %d pocion(es).\n¿Deseas consumir alguna(s)?\n\nSeleccione una opción:\n\n1. Sí, por favor.\n2. No, gracias.\n>>", 17 - bolso[4], bolso[0]);
        scanf("%d", &opcion);
        getchar();

        while(opcion == 1 && bolso[0] > 0 && bolso[4] < 17){

            printf("\nConsumiste una poción.\n\nTus puntos de vida subieron a %d.", bolso[4] + 1);
            presionarEnter();
            bolso[0] -= 1;
            bolso[4] += 1;

            if(bolso[0] = 0 || bolso[4] == 17){
                if(bolso[0] == 0){
                    printf("\n¡Se te han acabdo las pociones!\n");
                    presionarEnter();
                }

                if(bolso[4] == 17){
                    printf("\nLlegaste al máximo de vidas disponibles.");
                    presionarEnter();
                }
                
                opcion = 0;
            }

            else{
                printf("\n¿Desea consumir otra poción?\nSeleccione una opción:\n1. Sí, más por favor.\n2. No más, gracias.\n>>");
                scanf("%d", &opcion);
                getchar();
            }
        }
    }

    return bolso;
}

int * comprar(int * bolso){

    saltarMucho();

    int opcion;
    int catalogo;

    printf("Una figura encapuchada se te acerca.\nTiene aspecto enfermizo.\nHabla un idioma desconocido...\n\n'Got some rare things on sale, stranger!'\n\nTe muestra un extraño catálogo.\nCreo que te quiere vender algo...\n");

    printf("\n\n\t\t\t\tItem\t\t\t\t\t\tPrecio\n\n");
    printf("_________________________________________________________________________________________\n");
    printf("\n1. Escudo de Madera: Agrega un dado de defensa.\t\t\t\t\t1 Tesoro\n");
    printf("\n2. Una poción.\t\t\t\t\t\t\t\t\t1 Tesoro\n");
    printf("\n3. Escudo de Hierro: Agrega dos dados de defensa.\t\t\t\t2 Tesoros\n");
    printf("\n4. Tres pociones.\t\t\t\t\t\t\t\t2 Tesoros\n");
    printf("\n5. Espada: Agrega un dado de ataque.\t\t\t\t\t\t3 Tesoros\n");
    printf("\n6. Seis pociones.\t\t\t\t\t\t\t\t3 Tesoros\n");
    printf("\n7. Hacha guerrera: Agrega dos dados de ataque.\t\t\t\t\t4 Tesoros\n");
    printf("\n8. Armadura con espinas: Agrega dos dados de ataque, y un dado de defensa.\t5 Tesoros\n");
    printf("\n9. Armadura mágica: Agrega cinco dados de defensa.\t\t\t\t6 Tesoros\n");
    printf("\n\n");
    printf("\nEl Escudo de Madera no se puede usar en conjunto con el Escudo de Hierro.\nLa Espada y la Hacha guerrera no se pueden usar en conjunto.\nLa Armadura con Espinas y la Armadura Mágica no se pueden usar en conjunto.\n\n");

    printf("\n¿Deseas comprar algún item?\nSeleccione una opción.\n1. Sí, me gustaría.\n2. No, por favor alejate.\n>>")
    scanf("%d", &opcion);
    getchar();

    while(opcion == 1){

        if(bolso[1] == 0){

            printf("\nNot enough cash, stranger!\nTe quedaste sin tesoros.\n");
            opcion = 0;
        }

        printf("\nWhat are you buying?\n¿Qué número del catálogo deseas comprar?\n");
        scanf("%d", &catalogo);
        getchar();

        
    }


    return bolso;
}

int * batallar(int * bolso, int dadosAtaqueEnemigo, int dadosDefensaEnemigo, int dadosAtaqueJugador, int dadosDefensaJugador, int monstruo){
// bolso = [pocion, tesoro, dadosAtaque, dadosDefensa, vida]

    saltarMucho();
    int instancia;
    int lanzamiento;
    int resultado;

    int dadoLanzadoAtaqueEnemigo[dadosAtaqueEnemigo];
    int dadoLanzadoAtaqueJugador[dadosAtaqueJugador];

    int dadoLanzadoDefensaEnemigo[dadosDefensaEnemigo];
    int dadoLanzadoDefensaJugador[dadosDefensaJugador];

    int ataqueEnemigo = 0;
    int defensaEnemigo = 0;

    int ataqueJugador = 0;
    int defensaJugador = 0;

    int finalCombate = 0;

    while(finalCombate == 0){

        for(instancia = 1; instancia <= dadosAtaqueEnemigo; instancia++){
            resultado = lanzarDado();
            
            dadoLanzadoAtaqueEnemigo[instancia - 1] = resultado;

            }

        for(lanzamiento = 0; lanzamiento < dadosAtaqueEnemigo; lanzamiento++){

            printf("El enemigo lanzó un %d.\n", dadoLanzadoAtaqueEnemigo[lanzamiento]);
        }

        //Se buscan si existen '6' en los lanzamientos del enemigo.
        ataqueEnemigo = buscarSeis(dadoLanzadoAtaqueEnemigo, dadosAtaqueEnemigo);

        //Si existe uno o más '6' en los lanzamientos del enemigo, se procede a la defensa del jugador.
        if(ataqueEnemigo >= 1){

            //Dependiendo de cuántos dados el jugador posea, se llama a la función lanzarDado().
            for(instancia = 1; instancia <= dadosDefensaJugador; instancia++){
                //Todos los resultados son guardados en un arreglo correspondiente.
                resultado = lanzarDado();
                dadoLanzadoDefensaJugador[instancia - 1] = resultado;
            }

            printf("\nEl enemigo prepara %d ataque(s).\n", ataqueEnemigo);
            printf("Preparas tu mejor defensa...\n");
            presionarEnter();
            saltarMucho();

            for(lanzamiento = 0; lanzamiento < dadosDefensaJugador; lanzamiento++){

                printf("Lanzaste un %d.\n", dadoLanzadoDefensaJugador[lanzamiento]);
            }

            defensaJugador = buscarSeis(dadoLanzadoDefensaJugador, dadosDefensaJugador);

            printf("\nBloqueaste %d ataque(s).\n", defensaJugador);

            if((defensaJugador - ataqueEnemigo) < 0){
                //Si la resta de la cantidad de '6' lanzados en la defensa del jugador con la cantidad de '6' en el ataque del enemigo es negativa, el jugador pierde una vida.
                printf("\nSientes un fuerte dolor en tu cuerpo.\nPerdiste %d vida(s).\n", -1*(defensaJugador - ataqueEnemigo));
                //Se le restan las vidas correspondiente al jugador.
                bolso[4] += (defensaJugador - ataqueEnemigo);
                printf("Te quedan %d vidas.\n", bolso[4]);
                presionarEnter();
                saltarMucho();
            }

            if((defensaJugador - ataqueEnemigo) >= 0){

                printf("\nCon un poco de habilidad y bastante suerte logras bloquear todos los ataques del enemigo.\n");
                presionarEnter();
                saltarMucho();
            }            
        }

        else if(ataqueEnemigo == 0){

            printf("\nEl enemigo resbala al atacarte y retrocede.\n");
        }

        printf("Sudando, levantas tu arma en un intento de ataque...\n");
        presionarEnter();
        saltarMucho();

        for(instancia = 1; instancia <= dadosAtaqueJugador; instancia++){

            resultado = lanzarDado();
            dadoLanzadoAtaqueJugador[instancia - 1] = resultado;
        }

        for(lanzamiento = 0; lanzamiento < dadosAtaqueJugador; lanzamiento++){

            printf("Lanzaste un %d.\n", dadoLanzadoAtaqueJugador[lanzamiento]);
        }

        ataqueJugador = buscarSeis(dadoLanzadoAtaqueJugador, dadosAtaqueJugador);

        if(ataqueJugador > 0){
            printf("\nPreparas %d ataque(s).\n", ataqueJugador);
        }

        if(ataqueJugador == 0){

            printf("\nAtacas con todas tus fuerzas.\nTus esfuerzos son en vano, tu enemigo sigue en pie.\n");
        }

        presionarEnter();
        saltarMucho();

        if(ataqueJugador >= 1 && dadosDefensaEnemigo == 0){

            printf("Atacas con toda tu furia.\n¡Heriste mortalmente a tu enemigo!\nLa victoria es tuya.");
            presionarEnter();
            finalCombate = 1;
        }

        if(dadosDefensaEnemigo > 0 && ataqueJugador >= 1){

            printf("\nEl enemigo prepara su defensa...\n");
            presionarEnter();
            saltarMucho();
            for(instancia = 1; instancia <= dadosDefensaEnemigo; instancia++){

                resultado = lanzarDado();
                dadoLanzadoDefensaEnemigo[instancia - 1 ] = resultado;
            }

            for(lanzamiento = 0; lanzamiento < dadosDefensaEnemigo; lanzamiento++){

                printf("El enemigo ha lanzado un %d. \n", dadoLanzadoDefensaEnemigo[lanzamiento]);
            }

            defensaEnemigo = buscarSeis(dadoLanzadoDefensaEnemigo, dadosDefensaEnemigo);
            printf("\nEl enemigo ha bloqueado %d ataque(s).\n", defensaEnemigo);

            if((defensaEnemigo - ataqueJugador) < 0){

                printf("\n\nEl enemigo ha caído en un profundo estupor.\nDespués de varias convulsiones queda inmóvil y no respira.\nLo has derrotado.\n\n");
                presionarEnter();
                finalCombate = 1;
            }

            if((defensaEnemigo - ataqueJugador) >= 0){
                printf("\nEl enemigo ha esquivado todos tus ataques.\nLa pelea sigue...\n");
                presionarEnter();
                saltarMucho();
            }
            
        }

    }

    bolso = beberPocion(bolso);

    if(bolso[1] > 0)
        bolso = comprar(bolso);

    saltarMucho();
    return bolso;
}

int * encontrarEntidad(int ** tablero, int * bolso){

    int * ubicacion;
    int dado;
    //bolso = [pocion, tesoro, dadosAtaque, dadosDefensa, vida]
    ubicacion = encontrarJugador(tablero);

    if(ubicacion[0] == 10){

        dado = lanzarDado();

        if(dado == 1){
            printf("\nEncontraste una poción.\n");
            bolso[0] += 1;
            presionarEnter();
        }

        if(dado > 1 && dado < 5){
            printf("\nUn OGRO bloquea tu camino.\n'Pelea insecto'\n");
            printf("¿Listo para pelear?\n");
            presionarEnter();

            batallar(bolso, 1, 0, 1, 1, 1);
        }

        if(dado == 5){
            printf("\nUna mosca vuela de pared en pared...\n");
            printf("Debes seguir avanzando.\n");
            presionarEnter();
        }

        if(dado == 6){
            printf("\nEncontraste una poción.\n");
            bolso[0] += 1;
            presionarEnter();
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
            printf("\nVes el cadáver de un guerrero caído...\nAvanzas con un poco de miedo...\n");

        }

        if(dado == 5){
            printf("\nEl olor a descomposición casi no te deja avanzar...\nTu sentido del orgullo te obliga a seguir...\n");
        }

        if(dado == 6){
            printf("\nUn cofre resplandeciente hace brillar tu alrededor.\nTu instinto avaricioso te obliga a guardar sus contenidos...\nHas adquirido un nuevo tesoro.\n");
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
            printf("\nUn ESQUELETO saca sus armas al verte pasar...\n");
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
            jugada = validarJugada(tablero, jugada, fila, columna);

        }
    }

    //Validación de la fila 10.
    if(fila == 10 && columna != 8 && columna != 0){
        //Jugadas válidas son 1, 2, 3, 4 ú 8.
        while(jugada > 4 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }

    //Validación de la esquina inferior izquierda.
    if(fila == 10 && columna == 0){
        //Jugadas válidas son 2, 3 ó 4.
        while(jugada > 4 || jugada == 1){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);

        }
    }

    //Validación de la esquina inferior derecha.
    if(fila == 10 && columna == 8){
        //Jugadas válidas son 1, 2 ó 8.
        while(jugada != 2 && jugada != 1 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }   

    //Validación de la fila 1.
    if(fila == 1 && columna != 0 && columna != 8  && columna != 3 && columna != 4 && columna != 5){
        //Jugadas válidas son 4, 5, 6, 7 ó 8.
        while(jugada != 4 && jugada != 5 && jugada != 6 && jugada != 7 && jugada != 8){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);

        }
    }

    //Validación de la esquina superior izquierda.
    if(fila == 1 && columna == 0){
        //Jugadas válidas son 4, 5 ó 6.
        while(jugada != 4 && jugada != 5 && jugada != 6){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }

    //Validación de la esquina superior derecha.
    if(fila == 1 && columna == 8){
        //Jugadas válidas son 6, 7 ó 8.
        while(jugada != 8 && jugada != 7 && jugada != 6){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }

    //Validación de la columna 0.
    if(columna == 0 && fila != 1 && fila != 10){
        //Jugadas válidas son 2, 3, 4, 5 ó 6.
        while(jugada == 7 || jugada == 8 || jugada == 1){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);

        }
    }

    //Validación de la columna 8.
    if(columna == 8 && fila != 1 && fila != 10){
        //Jugadas válidas son 1, 2, 6, 7 ú 8.       
        while(jugada == 3 || jugada == 4 || jugada == 5){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }


    //Validación de la esquina inferior izquierda del cuadro final del juego.
    if(fila == 1 && columna == 3){
        //Jugadas válidas son 3, 4, 5, 6, 7 ú 8.
        while(jugada == 1 || jugada == 2){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }

    }

    //Validación del cuadro anterior al cuadro final del juego.
    if(fila == 1 && columna == 4){
        //Jugadas válidas son 2, 4, 5, 6, 7 ú 8.
        while(jugada == 1 || jugada == 3){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
        }
    }

    //Validación del cuadro inferior derecho al cuadro final del juego.
    if(fila == 1 && columna == 5){
        //Jugadas válidas son 1, 4, 5, 6, 7 ú 8.
        while(jugada == 2 || jugada == 3){

            printf("\nJugada inválida\n");
            jugada = ingresarJugada();
            jugada = validarJugada(tablero, jugada, fila, columna);
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
    
    srand(time(NULL));
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
        saltarMucho();

        tablero = modificarTablero(tablero, jugada);

        mochila = encontrarEntidad(tablero, mochila);

        imprimirTablero(tablero);
        imprimirMochila(mochila);
    }

    liberarTablero(tablero);

    return 0;
}





