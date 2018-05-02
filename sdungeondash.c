#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  Rodolfo 
    RUT 

    Sección 
    Profesor 

    2 de Mayo del 2018

    Generalidades del código:

        El presente trabajo está compuesto de numerosas funciones, todas comentadas con sus respectivas Entradas, Salidas y el Objetivo de cada una.
        Además, si en alguna función existe una o más líneas de interés para su funcionamiento, éstas han sido comentadas de igual forma.

        El funcionamiento general del juego con todas las funciones trabajando en conjunto se puede ver explicado claramente en la función main(), en la parte final del archivo.

    Observaciones:

        1.  Todos los datos del jugador a lo largo de la duración del juego (Dados de ataque y defensa, armamento, vida, pociones y tesoros) son guardados en un arreglo que contiene 8 posiciones (0 al 7).
            
            Es decir; bolso = [Pociones, Tesoros, Dados de ataque, Dados de defensa, Vida, Arma, Escudo, Armadura].

        
        2.  La función aleatorizar frase se creó con la idea de que cada vez que el jugador entre en combate, éste pueda ver un nuevo dialogo en cada instancia de bloqueo, ataque, perder vida, etc.
            
            De esta forma, se torna un poco menos monótona la batalla dentro del juego.


        3.  Si se desea tener un pasar más fácil por el juego, es posible modificar la función generarMochila() y cambiar los valores iniciales del jugador.

            Por ejemplo, comenzar con 99 dados de ataque y defensa, o 99 de vida, o 99 de tesoros, etc.


        4.  El cuchillo de manteca, escudo viejo y la chaqueta de cuero hervido, son indumentarias básicas que proporcionan las condiciones iniciales de los dados, nada más.

            Se crearon para que el juego no mostrara "Nada equipado" al inicio.


    /* I N I C I O 
                    D E L
                            P R O G R A M A */



/*  Entrada: Nada.
    Salida: Un arreglo de dos dimensiones que simboliza una matriz, que a su vez, simboliza el tablero en el cual el juego se desarrolla.
    Objetivo: Generar un arreglo de dos dimensiones en memoria para poder ser utilizado como tablero.
*/
int ** generarTablero(){

    /*  Función que genera un array de dos dimensiones con "12" "filas" y "9" "columnas", asemejando una matriz que a su vez asemeja un tablero de juego.
        El inicio del tablero está dado por el "1". 
        Espacios vacíos son representados con un "0" y el jugador con un "1".
        Espacios ya ocupados anteriormente por el jugador están representados por un "3".
        Números "2" simbolizan casilleros inválidos.
        Más adelante se verá que las jugadas válidas posibles son representadas por números de dos dígitos (11 para la jugada número 1, 22 para la jugada 2, 33 para la 3, etc.) */

    int ** tablero = (int **)malloc(13 * sizeof(int *));
    int fila;
    int columna;


    for(fila = 0; fila < 13; fila++){

        tablero[fila] = (int *)malloc(9 * sizeof(int));
    }

    for(fila = 0; fila < 13; fila++){

        for(columna = 0; columna < 9; columna++){
            
            //Casillero final.
            if(fila == 0 && columna == 4)
                tablero[fila][columna] = 0;

            if(fila == 11 && columna != 4)
                tablero[fila][columna] = 2;

            if(fila == 11 && columna == 4)
                tablero[fila][columna] = 1;

            if(fila > 0 && fila < 11)
                tablero[fila][columna] = 0;

            if(fila == 11 && columna != 4)
                tablero[fila][columna] = 2;

            //Casilleros inaccesibles en el último nivel del juego.
            if(fila == 0 && columna != 4)
                tablero[fila][columna] = 2;
        }
    }

    return tablero;
}

/*  Entrada: Un arreglo de dos dimensiones que representa el tablero de juego.
    Salida: Nada.
    Objetivo: Liberar la memoria ocupada por el tablero.
*/
void liberarTablero(int ** tablero){
    
    int fila;
    int columna;

    for(fila = 0; fila < 13; fila++){            
            free(tablero[fila]);
    }

    free(tablero);
    return;
}

/*  Entrada: Nada.
    Salida: Nada.
    Objetivo: Son muchos saltos de lineas contenidos en un printf(), uno tras otro, para genera un súper salto de línea y así facilitar el orden y pulcritud del juego y código.
*/
void saltarMucho(){

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return;
}

/*  Entrada: Nada.
    Salida: Entero, 0.
    Objetivo: Para facilitar el orden y pulcritud del juego se decidió por escribir una función que pidiera al usuario presionar la tecla Enter para seguir avanzando en el juego.
*/
int presionarEnter(){

    printf("\nPresione 'Enter' para continuar.\n");
    getc(stdin);
    return 0;
}

/*  Entrada: Nada.
    Salida: Un resultado aleatorio que simula un dado real.
    Objetivo: Segun las especificaciones entregadas por coordinación se creó una función que representa un dado.
*/
int lanzarDado(){
    //Se crea una variable donde sea posible guardar el resultado del dado lanzado.
    int resultado;

    //Se utiliza la función random para generar un número aleatorio.
    resultado = rand() % ((6 + 1 - 1) + 1);

    //Si por alguna razón el resultado es 0, entonces se llama nuevamente a la función random para generar otro resultado, hasta que éste sea distinto de 0.
    while(resultado == 0){
        resultado = rand() % ((6 + 1 - 1) + 1);
    }

    //Se retorna el resultado obtenido por el lanzamiento del dado.
    return resultado;
}

/*  Entrada: Jugada realizada, la fila y columna de ésta.
    Salida: Un arreglo, llamado conversion, que contiene la fila y columna de la jugada que ingresó el usuario.
    Objetivo: Transformar una jugada ingresada en sus parámetros de fila y columna para poder ser editadas dentro del tablero.
*/
int * convertirJugada(int jugada, int fila, int columna){

    int filaConvertida;
    int columnaConvertida;
    //C presenta 'Warnings' cuando se desea retornar una variable local mediante punteros al compilar el programa, por esta razón se le especifica el 'static'. 
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

/*  Entrada: Nada.
    Salida: El número de la jugada realizada.
    Objetivo: Pedirle al usuario una jugada a realizar.
*/
int ingresarJugada(){

    int jugada;
    printf("\nIngrese su jugada:\n>>");
    scanf("%d", &jugada);
    getchar();
    //Valida la jugada ingresada, si ésta se sale de los parámetros indicados, se le pide nuevamente.
    while(jugada > 8 || jugada <= 0){

        printf("Ingrese una jugada válida:\n>>");
        scanf("%d", &jugada);
        getchar();
    }

    return jugada;

}

/*  Entrada: El tablero del juego.
    Salida: Un arreglo unidimensional que corresponde a la posición (fila y columna) del jugador en el tablero.
    Objetivo: Encontrar la ubicación (fila y columna) del jugador en el tablero.
*/
int * encontrarJugador(int ** tablero){

    int fila;
    int columna;
    int filaEncontrada;
    int columnaEncontrada;

    //C presenta 'Warnings' cuando se desea retornar una variable local mediante punteros al compilar el programa, por esta razón se le especifica el 'static'.
    static int ubicacion[2];

    //Por cada fila existente en el arreglo.
    for(fila = 0; fila < 12; fila++){
        //Por cada columna perteneciente a cada fila.
        for(columna = 0; columna < 9; columna++){
            //Si dentro del arreglo se encuentra un '1', quiere decir que el jugador fue encontrado.
            if(tablero[fila][columna] == 1){
                //Se procede a guardar la información de la ubicación del jugador en variables correspondientes.
                filaEncontrada = fila;
                columnaEncontrada = columna;

            }
        }
    }

    //En un arreglo creado con anterioridad se guardan las dos componentes encontradas que representan la ubicación actual del jugador.
    ubicacion[0] = filaEncontrada;
    ubicacion[1] = columnaEncontrada;

    //Se retorna el arreglo que contiene las variables de interés.
    return ubicacion;

}

/*  Entrada: Nada.
    Salida: Un arreglo unidimensional que contiene los valores iniciales del jugador. (Armamento, dados, vida, pociones y tesoros).
    Objetivo: Crear la mochila que guardará toda la información perteneciente al jugador a lo largo del juego.
*/
int * generarMochila(){
/*  Se genera una variable de tipo entero 'static' para evitar 'Warnings' al compilar el programa.
    El arreglo posee ocho lugares, uno por cada item perteneciente al juego */

    static int bolso[8];

    //Pociones.
    bolso[0] = 0;
    //Tesoros.
    bolso[1] = 0;
    //Dados de ataque.
    bolso[2] = 1;
    //Dados de defensa.
    bolso[3] = 1;
    //Vida.
    bolso[4] = 17;
    //Arma
    bolso[5] = 0;
    //Escudo.
    bolso[6] = 0;
    //Armadura.
    bolso[7] = 0;

    return bolso;
}

/*  Entrada: Un arreglo que representa la mochila del jugador.
    Salida: Nada.
    Objetivo: Mostrar por pantalla el estado actual de los items que el jugador posee.
*/
void imprimirMochila(int * bolso){
    printf("\n__________________________________\n");
    printf("\nDados de Ataque: %d\tDados de Defensa: %d\n\nVida: %d\n\nPociones: %d\t\tTesoros: %d", bolso[2], bolso[3], bolso[4], bolso[0], bolso[1]);
    
    if(bolso[5] == 1)
        printf("\n\nArma: Espada\n");

    if(bolso[5] == 2)
        printf("\n\nArma: Hacha Guerrera\n");

    if(bolso[5] == 0)
        printf("\n\nArma: Cuchillo de manteca\n");

    if(bolso[6] == 0)
        printf("\t\t\t\nEscudo: Escudo viejo\n");
    
    if(bolso[6] == 1)
        printf("\t\t\t\nEscudo: Escudo de Madera\n");

    if(bolso[6] == 2)
        printf("\t\t\t\nEscudo: Escudo de Hierro\n");

    if(bolso[7] == 0)
        printf("\t\t\t\nArmadura: Chaqueta de cuero hervido\n");

    if(bolso[7] == 1)
        printf("\t\t\t\nArmadura: Armadura de Espinas\n");

    if(bolso[7] == 2)
        printf("\t\t\t\nArmadura: Armadura Mágica\n");


    printf("\n__________________________________\n");
    return;
}

/*  Entrada: Un arreglo correspondiente a los resultados de uno o más dados lanzados por el jugador o enemigo.
    Salida: Una variable que contiene el número de 'seis' dentro de los lanzamientos efectuados.
    Objetivo: Contar la cantida de 'seis' en cada lanzamiento efectuado.
*/
int buscarSeis(int * dadosLanzados, int largo){
    //Se declaran las variables 'seisEnc' (cantidad de seis encontrados) y un contador para el ciclo for.
    int seisEnc = 0;
    int contador;

    for(contador = 0; contador < largo; contador++){
        //Se recorre el arreglo donde están guardados los lanzamientos y si se encuentra un 'seis' se le suma uno a la variable adecuada.
        if(dadosLanzados[contador] == 6)
            seisEnc += 1;
    }

    return seisEnc;
}

/*  Entrada: Una id correspondiente a la acción o dialogo según sea necesario.
    Salida: Nada.
    Objetivo: Dependiendo de la ID ingresada, se mostrará por pantalla un diálogo que corresponderá alguna acción o dialogo dentro del juego.
*/
void aleatorizarFrase(int id){

/*  Debido a que las batallas pueden ser muy largas y monótonas, se creó esta función que aleatoriza diferentes tipos de 'prints'
    para una misma acción o diálogo.
*/

    //Se declaran las variables frases y resultado para facilitar el aleatorizador.
    int frases;
    int resultado;

    //El jugador pierde vida.
    if(id == 1){

        frases = 6;
        //Dependiendo de la cantidad de frases, el aleatorizador se ejecuta del 1 al número de éstas.
        resultado = rand() % (frases);

        //Si por alguna razón el resultado es 0, se aleatoriza nuevamente hasta que el resultado sea adecuado.
        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nSientes un fuerte dolor en tu cuerpo.\n");

        if(resultado == 2)
            printf("\nMiras sangre salir de alguna parte de tu cuerpo.\n");

        if(resultado == 3)
            printf("\nUn dolor punzante afecta tu abdomen.\n");

        if(resultado == 4)
            printf("\nNo tienes idea de lo que pasó porque cerraste los ojos antes que te llegara un ataque.\nUn gran dolor está presente en alguna parte de tu cuerpo.\n");

        if(resultado == 5)
            printf("\nLa adrenalina no te deja sentir dolor, pero sabes que algo anda muy mal.\n");

        if(resultado == 6)
            printf("\nSientes como tus fuerzas se debilitan.\nTu onda vital disminuye debido a tus heridas.\n");

    }

    //El jugador bloquea todos los ataques del enemigo.
    if(id == 2){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nCon un poco de habilidad y bastante suerte logras bloquear todos los ataques del enemigo.\n");

        if(resultado == 2)
            printf("\nEl estruendo de tu escudo retumba en las paredes al bloquear todos los ataques del enemigo.\n");

        if(resultado == 3)
            printf("\nAstillas y chispas salen de tu escudo y espada al bloquear todos los ataques que el enemigo te lanzó.\n");

        if(resultado == 4)
            printf("\nTus manos tiemblan por la fuerza de los ataques recibidos, pero lograste bloquearlos todos.\n");

        if(resultado == 5)
            printf("\nHaciendo subir más y más la adrenalina, logras bloquear cada uno de los ataques recibidos.\n");

        if(resultado == 6)
            printf("\nA pesar de los esfuerzos del rival, con un solo dedo bloqueas todos los ataques del enemigo.\n");
    }

    //El enemigo falla sus ataques.
    if(id == 3){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nEl enemigo resbala al atacarte y retrocede.\n");

        if(resultado == 2)
            printf("\nVes como el enemigo estrella su cabeza contra el suelo en un intento fallido de ataque.\n");

        if(resultado == 3)
            printf("\nParece que el enemigo tenía pensado atacarte, pero se detuvo en el momento más crucial.\n");

        if(resultado == 4)
            printf("\nNo tienes idea de lo que pasó porque cerraste los ojos al momento del ataque, pero el enemigo yace en el suelo por alguna razón.\nSe vuelve a parar con verguenza en la cara.\n");

        if(resultado == 5)
            printf("\nTe gustaría saber como una bestia tan torpe llegó viva hasta este punto.\nTu enemigo tropieza al avanzar y retrocede.\n");

        if(resultado == 6)
            printf("\nEl rival pierde el equilibrio al atacarte y falla.\n");
    }

    //El jugador prepara ataque.
    if(id == 4){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nSudando, levantas tu arma en un intento de ataque...\n");

        if(resultado == 2)
            printf("\nCon las peores intenciones del mundo, soplas tu arma y vas al ataque...\n");

        if(resultado == 3)
            printf("\nPrefieres no pensar en el final, solamente en el presente.\nCorres en busca del golpe mortal...\n");

        if(resultado == 4)
            printf("\nEs hora de atacar.\nCorres hacia el enemigo con tus peores intenciones...\n");

        if(resultado == 5)
            printf("\nSabes que lo que tienes que hacer es peligroso.\nTe sacas ese pudor de encima y corres al ataque...\n");

        if(resultado == 6)
            printf("\nReúnes tus fuerzas y arremetes contra el rival...\n");
    }

    //El jugador falla ataques.
    if(id == 5){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nAtacas con todas tus fuerzas.\nTus esfuerzos son en vano, tu enemigo sigue en pie.\n");

        if(resultado == 2)
            printf("\nTus mejores esfuerzos han sido en vano.\nEl enemigo sigue vivo.\n");

        if(resultado == 3)
            printf("\nTe gustaría saber cómo no pudiste acabar la pelea con este ataque.\nEl enemigo sigue en pie y más furioso que antes.\n");

        if(resultado == 4)
            printf("\nUn balbuceo extraño sale del hocico de la bestia.\n¿Se estará burlando de ti?\nEl enemigo no ha sido afectado por tus ataques.\n");

        if(resultado == 5)
            printf("\nUn ronquido sale del estómago del enemigo.\nTus ataques fueron en vano, la bestia sigue en pie.\n");

        if(resultado == 6)
            printf("\nAtacas... pero la frase 'feto ingeniero' escrita con sangre en una pared te ha distraído y has fallado.\n¿Qué es 'feto'?\nEl enemigo sigue con vida.\n");
    }

    //El jugador gana el combate.
    if(id == 6){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nAtacas con toda tu furia.\n¡Heriste mortalmente a tu enemigo!\nLa victoria es tuya.");

        if(resultado == 2)
            printf("\nSangre por todos lados, en las paredes, en tus ropas...\nHeriste mortalmente a tu enemigo.\nHas ganado el combate.\n");

        if(resultado == 3)
            printf("\nTu arma derrocha grandes gotas de sangre.\nTu enemigo yace muerto frente a ti.\nLa batalla ha sido ganada.\n");

        if(resultado == 4)
            printf("\nGanaste el combate.\n¡Sigue avanzando y completa tu misión!\n");

        if(resultado == 5)
            printf("\nTripas, brazos, piernas, ojos... por todos lados...\nEn tu furia, descuartizaste a tu enemigo.\nGanaste el combate, pero... ¿valió la pena?\n");

        if(resultado == 6)
            printf("\nCon un lápiz y una libretita de color negro podría haber sido más sencillo.\nDe igual manera sales victorioso.\n");
    }

    //El enemigo esquiva todos los ataques.
    if(id == 7){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nEl enemigo ha esquivado todos tus ataques.\nLa pelea sigue...\n");

        if(resultado == 2)
            printf("\nTodos tus ataques han fallado.\nLa pelea DEBE continuar...\n");

        if(resultado == 3)
            printf("\nEl insecto ha esquivado todos tus ataques.\n¿Dónde está tu honor, basura?\nEl combate tiene que seguir...\n");

        if(resultado == 4)
            printf("\nTodos tus ataques fueron en vano.\nEl combate aún no termina...\n");

        if(resultado = 5)
            printf("\nCon un extraño baile el enemigo esquivó todos tus ataques.\nLa batalla aún no termina...\n");

        if(resultado == 6)
            printf("\nLa velocidad de tu enemigo ha sido muy superior y no has podido acertar.\nLa batalla persiste...\n");

    }

    // Ogro.
    if(id == 8){

        frases = 4;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nUn OGRO bloquea tu camino.\n'Pelea insecto'\n¿Listo para pelear?\n");

        if(resultado == 2)
            printf("\nUn OGRO bloquea tu pasar\n'De aquí no pasas'\n¿Qué se cree esta basura?\n¡MÁTALO!\n");

        if(resultado == 3)
            printf("\nUn OGRO te mira al pasar.\nTu presencia no le agrada...\nA ti tampoco te agrada.\nDecides matarlo.\n");

        if(resultado == 4)
            printf("\nUn OGRO horriblemente deformado cruza sus cejas al verte pasar...\nCriatura del inframundo, muere.\n");
    }

    //Lobo.
    if(id == 9){

        frases = 4;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nVes un LOBO marcar su territorio.\nTu presencia no le es grata...\n¡Cuidado con la orina!\n");

        if(resultado == 2)
            printf("\nUn LOBO de apariencia robusta come un enano que yace muerto.\nCarne fresca...\n¿Dejarás que te coma?\n");

        if(resultado == 3)
            printf("\nUn LOBO arrastra su cola mientras se acerca en tu dirección...·\nNo sientes miedo.\n");

        if(resultado == 4)
            printf("\nLos ojos de un peludo LOBO brillan en la penumbra.\nSientes la adrenalina subir y te preparas para eliminarlo.\n");
    }

    //Esqueleto.
    if(id == 10){

        frases = 4;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nUn ESQUELETO saca sus armas al verte pasar...\nHaces lo mismo y te preparas para la batalla.\n");

        if(resultado == 2)
            printf("\nUn robusto ESQUELETO hace círculos con una espada al darse cuenta de tu presencia...\nHaces ruido con tu espada y escudo.\nAcercate, basura.\n");

        if(resultado == 3)
            printf("\nClick, clack\nUn ESQUELETO no te quita la mirada de encima.\n\nTendrás que romperle el cráneo.\n");

        if(resultado == 4)
            printf("\nUna bestia horripilante aparece frente a ti.\nSu cuerpo no tiene piel ni carne.\nESQUELETO se prepara para atacarte.\n");

    }

    //Guerrero.
    if(id == 11){

        frases = 4;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nUn humanoide jorobado de apariencia robusta se dispone a pelear...\n'Mis habilidades de GUERRERO son insuperables'\nRepugnante bestia.\nDisfrutarás descuartizándolo.\n");

        if(resultado == 2)
            printf("\nEscuchas balbuseos irreproducibles\nEs un GUERRERO gordo y encorvado.\n\nBestia endemoniada...\n¡MÁTALO!\n");

        if(resultado == 3)
            printf("\nUn asqueroso GUERRERO horriblemente deformado se acerca a tu posición.\n¿Pelearás?\n");

        if(resultado == 4)
            printf("\nUn GUERRERO con el la cara llena de cicatrices corre hacia ti.\nDesenvainas tu espada, preparas tu escudo.\n");
    }

    //Murciélago.
    if(id == 12){

        frases = 3;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nEl sonido de alas rompiendo el aire retumba en tus oídos.\nUn MURCIÉLAGO gigante te ataca.\n");

        if(resultado == 2)
            printf("\nA lo lejos escuchas el batir de unas alas gigantescas.\nUna especie de MURCIÉLAGO vuela a gran velocidad hacia tu posición.\n¡PREPÁRATE PARA ASESINARLO!\n");

        if(resultado == 3)
            printf("\n¿Qué ruido es ese?\nUn MURCIÉLAGO de tamaño considerable vuela en tu dirección.\n¡PELEA!\n");
    }

    //Cíclope.
    if(id == 13){

        frases = 2;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\n¿Qué tipo de ogro es éste?\n¡TIENE UN OJO EN LA MITAD DE SU FRENTE!\nEl CÍCLOPE arremete contra ti.\nSacas tus armas y te preparas para el combate.\n");

        if(resultado == 2)
            printf("\nEste CÍCLOPE ha perdido todos sus ojos excepto el de su frente.\nQué bestia más fea.\nTe preparas para la batalla.\n");

    }

    //Elfo oscuro.
    if(id == 14){

        frases = 2;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nU-Un ELFO... pero su piel... es de color negro...\nHa sido corrompido por poderes oscuros.\nUn ELFO OSCURO arremente contra ti.\n");

        if(resultado == 2)
            printf("\n¿Un elfo?\n¿Qué le paso a su piel...?\nELFO OSCURO arremete contra ti.\n");
    }

    //Lord esqueleto.
    if(id == 15){

        frases = 2;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\n¿Por qué este esqueleto tiene una capa?\n¿Y un casco...?\nLORD ESQUELETO te mira feo y prepara sus armas.\n");

        if(resultado == 2)
            printf("\nEste esqueleto tiene un aspecto más forma que los que has encontrado antes.\nLORD ESQUELETO persigue tu pasar.\nHora del combate.\n");
    }

    //Mago.
    if(id == 16){

        frases = 2;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nUn humanoide con una extraña capa morada y ojos muertos mira en tu dirección\nMAGO te ataca.\nHora de enlistar tu armamento.\n");

        if(resultado == 2)
            printf("\nQué capa mas horrible.\nMAGO persigue tu dirección.\nMerece morir por ese vestuario.\n");

    }

    //Demonio.
    if(id == 666){

        frases = 2;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nDas un paso en falso.\nEl suelo se caliente y ablanda al mismo tiempo.\n¿Una trampa...?\nRetrocedes unos metros.\nSe arma un agujero en las rocas.\nVes cuernos salir de este espacio y un calor infernal que te ahoga\nUn terrible DEMONIO saca una espada y se prepara para asesinarte.\n¡MATAR O MORIR!\n");
        
        if(resultado == 2)
            printf("\n¿Qué significa este estruendo?\nSientes un gran calor proveniente del suelo abajo tuyo.\nLas piedras se ablandan y se convierten en lava.\nDas varios pasos atrás....\nUna bestia con patas de cabra y cuernos aparece frente a ti.\nDEMONIO te ataca, sin compasión.\nÉsta batalla no será como las anteriores...\n");
    }

    //Poción.
    if(id == 20){

        frases = 3;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nEncontraste una poción.\n");

        if(resultado == 2)
            printf("\nUna botella que contiene un élixir parecido al de los elfos del Mirkwood yace frente a ti.\nDecides guardarla.\nHas adquirido una poción.\n");

        if(resultado == 3)
            printf("\nUna especie de engrudo es contenido dentro de una botella de mediano espesor.\nLa guardas en tu morral.\nUna poción ha sido sumada a tu arsenal.\n");


    }

    //Tesoro.
    if(id == 21){

        frases = 6;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nUn cofre resplandeciente hace brillar tu alrededor.\nTu instinto avaricioso te obliga a guardar sus contenidos...\nHas adquirido un nuevo tesoro.\n");

        if(resultado == 2)
            printf("\nUna bolsa reposa al lado de un cadáver irreconocible.\nSus contenidos son perlas brillantes.\nHas adquirido un tesoro.\n");

        if(resultado == 3)
            printf("\nQué bello el resplandor de éstas monedas...\nLas guardas en tu morral.\nHas adquirido un tesoro.\n");

        if(resultado == 4)
            printf("\nPisas algo duro.\nAl levantar el pie ves un gran lingote de oro.\nAdquiriste un tesoro.\n");

        if(resultado == 5)
            printf("\nSientes un fuerte golpe en la parte superior de tu cabeza.\nCae al lado tuyo una barra metálica de color plateado.\nAdquiriste un nuevo tesoro.\n");

        if(resultado == 6)
            printf("\nMiras brillar algo incrustado en la pared.\nUtilizando el filo de tu espada logras arrancarlo.\nUna preciosa gema de color esmeralda cae en tu mano.\nAdquiriste un nuevo tesoro.");

    }

    //Vacío.
    if(id == 22){

        frases = 8;

        resultado = rand() % (frases);

        while(resultado == 0 || resultado > frases){

            resultado = rand() % (frases);        
        }

        if(resultado == 1)
            printf("\nVes las paredes transpirar un líquido extraño.\nDisgustado, avanzas...");

        if(resultado == 2)
            printf("\nVes salir vapor de varias calderas en el suelo.\nDecides seguir...\n");

        if(resultado == 3)
            printf("\nVes el cadáver de un guerrero caído...\nAvanzas con un poco de miedo...\n");

        if(resultado == 4)
            printf("\nEl olor a descomposición casi no te deja avanzar.\nTu sentido del orgullo te obliga a seguir...\n");

        if(resultado == 5)
            printf("\nLa vibración de las moscas a tu alrededor te molesta de sobremanera...\n");

        if(resultado == 6)
            printf("\nLa penumbra apenas te deja ver tu camino.\nDecides avanzar con cautela...\n");

        if(resultado == 7)
            printf("\n¿Qué es este olor tan extraño?\nCon un tremendo disgusto decides seguir adelante...\n");

        if(resultado == 8)
            printf("\nUn olor repugnante llena tus sentidos.\nTe tapas los orificios de tu nariz y decides avanzar...\n");

    }

    return;
}

/*  Entrada: La mochila perteneciente al jugador.
    Salida: La mochila perteneciente al jugador, modificada.
    Objetivo: El usuario, si así lo desesa, puede beber o no pociones encontradas o compradas con anterioridad.
*/
int * beberPocion(int * bolso){

    saltarMucho();
    //Se declara la variable opción, que representara la elección del usuario con respecto a la pregunta deseada.
    int opcion;

    //La función trabajará solamente cuando existan pociones en la mochila del jugador y la vida del jugador sea menor al maximo.
    //Esta validación es hecha con el arreglo que representa la mochila del jugador y sus indices correspondientes, a pociones y vida.
    if(bolso[0] > 0 && bolso[4] < 17){
        //Se le pregunta al usuario si desea consumir alguna poción.
        printf("\nAntes de seguir tu camino a través de la mina, veo que has perdido %d punto(s) de vida y tienes en tu poder %d poción(es).\n¿Deseas consumir alguna(s)?\n\nSeleccione una opción:\n\n1. Sí, por favor.\n2. No, gracias.\n>>", 17 - bolso[4], bolso[0]);
        scanf("%d", &opcion);
        getchar();

        //Se valida la opción ingresada.
        while(opcion > 2){
            printf("\nPor favor ingrese una de las opciones válidas.\n¿Deseas consumir alguna(s)?\n1. Sí, por favor.\n2. No, gracias.\n>>");
            scanf("%d", &opcion);
            getchar();
        }

        //Mientras la opción sea 1, se le seguirá preguntando al usuario si desea seguir consumiendo pociones.
        while(opcion == 1){
            //Se consumió una poción.
            printf("\nConsumiste una poción.\n\nTus puntos de vida subieron a %d.", bolso[4] + 1);
            
            //Se modifica la mochila.
            bolso[0] -= 1;
            bolso[4] += 1;

            //Se le avisa al jugador cuantas pociones le van quedando.
            printf("\nTe quedan %d poción(es).\n", bolso[0]);

            //Si se le acaban las pociones o la vida llega al máximo.
            if(bolso[0] == 0 || bolso[4] == 17){
                //Si se le acaban las pociones, se le avisa y el ciclo es roto.
                if(bolso[0] == 0){
                    printf("\n¡Se han acabado las pociones!\n");
                    presionarEnter();
                    opcion = 0;
                }
                //Si llega al máximo de vidas el ciclo se rompe.
                if(bolso[4] == 17){
                    printf("\nLlegaste al máximo de vidas disponibles.");
                    presionarEnter();
                    opcion = 0;
                } 
            }

            else{
                //Si todavia le quedan pociones y su vida todavia no llega al maximo, se le sigue preguntando si desea consumir mas.
                printf("\n¿Desea consumir otra poción?\nSeleccione una opción:\n1. Sí, más por favor.\n2. No más, gracias.\n>>");
                scanf("%d", &opcion);
                getchar();
            }            
        }
    }

    return bolso;
}

/*  Entrada: Nada.
    Salida: Nada.
    Objetivo: Mostrar de una manera legible el menú de compras.
*/
void mostrarCatalogo(){

    saltarMucho();

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
    printf("\n10. Mostrar el catálogo.\n");
    printf("\n11. Salir.\n");
    printf("\nEl Escudo de Madera no se puede usar en conjunto con el Escudo de Hierro.\nLa Espada y el Hacha guerrera no se pueden usar en conjunto.\nLa Armadura con Espinas y la Armadura Mágica no se pueden usar en conjunto.\n\n");
    return;
}

/*  Entrada: La mochila del jugador.
    Salida: La mochila del jugador modificada.
    Objetivo: Ofrecer al jugador la compra de items, segun la cantidad de tesoros que posea.
*/
int * comprar(int * bolso){

    saltarMucho();

    int opcion;
    int catalogo;

    //Se le avisa al jugador que el mercader está disponible.
    printf("Una figura encapuchada se te acerca.\nTiene aspecto enfermizo.\nHabla un idioma desconocido...\n\n'Got some rare things on sale, stranger!'\n\nTe muestra un extraño catálogo.\nCreo que te quiere vender algo...\n");
    presionarEnter();

    //Se le muestra al jugador la cantidad de tesoros disponibles para que pueda tomar una decisión informada.
    printf("\nPosees %d tesoros.\n", bolso[1]);

    //Se le pregunte si desea comprar algún item del catálogo.
    printf("\n¿Deseas ver el catálogo y comprar algún item?\nSeleccione una opción.\n1. Sí, me gustaría.\n2. No, por favor alejate.\n>>");
    scanf("%d", &opcion);
    getchar();
    saltarMucho();

    //Mientras la opción este fuera del rango adecuado, se le hace la pregunta nuevamente.
    while(opcion > 2 || opcion <= 0){

        printf("\nElegir una de las opciones válidas.\n1. Quiero comprar.\n2. Quiero seguir avanzando.\n>>");
        scanf("%d", &opcion);
        getchar();
        saltarMucho();
    }
    //Mientras la opción sea "Sí", se le seguirá realizando la pregunta.
    while(opcion == 1){
        //Se le muestra el catálogo de items disponibles al jugador y los tesoros disponibles.
        mostrarCatalogo();
        printf("\nPosees %d tesoros.\n", bolso[1]);
        //Si los tesoros guardados en el bolso se acaban, el periodo de compras termina.
        if(bolso[1] == 0){

            printf("\n\n\nTe quedaste sin tesoros.\n\n\n");
            presionarEnter();
            saltarMucho();
            opcion = 0;
            catalogo = 11;
        }
        //Caso contrario el periodo de compras continua.
        else{
            printf("\n\n'What are you buying?'\n¿Qué número del catálogo deseas comprar?\n\nSi quieres ver de nuevo el catálogo, la opción es 10.\nRecuerda que la opción para salir es 11.\n>>");
            scanf("%d", &catalogo);
            getchar();
        }
        //Mientras la opcion de compra contenida en el catalogo este fuera del rango, se le advierte el error y se le pregunta nuevamente.
        while(catalogo > 11){

            printf("\n\n'Stranger, stranger... I have nothing of the sort!'\nPor favor elige una de las opciones válidas\nSi quieres ver de nuevo el catálogo, la opción es 10.\nRecuerda que la opción para salir es 11.\n>>");
            scanf("%d", &catalogo);
            getchar();
        }
        //El primer item del catálogo: Escudo de Madera.
        if(catalogo == 1){
            //Si no posee algún escudo en su bolso, se le agrega sin complicaciones.
            if(bolso[1] >= 1 && bolso[6] == 0){
                printf("\n\n'Hehehehe, thank you'.\nHas adquirido el Escudo de Madera.\nSe ha sumado 1 dado a tu defensa.\n");
                bolso[3] += 1;
                bolso[6] = 1;
                bolso[1] -= 1;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();

            }
            //Si ya posee el Escudo de Madera, se le advierte que más no puede llevar.
            else if(bolso[1] >= 1 && bolso[6] == 1){
                printf("\n\n'Can't carry no more, stranger!'\nYa posees el Escudo de Madera.\n");
                presionarEnter();
            }
            //Si ya posee el Escudo de Hierro, se le advierte, no se le deja adquirir el Escudo de Madera y el menú sigue.
            else if(bolso[1] >= 1 && bolso[6] == 2){
                printf("\n\nYa posees el Escudo de Hierro.\n");
                presionarEnter();
            }
            //Si los tesoros son insuficientes para la compra del item, se le advierte y sigue.
            else{
                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 2){

            //Si tiene tesoros suficientes, la compra es exitosa y las pociones son añadidas al bolso del jugador.
            printf("\n\n'A wise choice, mate!'\nUna poción fue sumada a tu mochila.\n");
            bolso[0] += 1;
            bolso[1] -= 1;
            printf("\nTe quedan %d tesoros.\n", bolso[1]);
            presionarEnter();
        }

        if(catalogo == 3){
            if(bolso[1] >= 2 && bolso[6] == 0){
                printf("\n\nAdquiriste el Escudo de Hierro.\nSe han sumado 2 dados a tu defensa.\n");
                bolso[3] += 2;
                bolso[6] = 2;
                bolso[1] -= 2;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }
            //Si al comprar el Escudo de Hierro ya se posee el Escudo de Madera, éste último es reemplazado por el primero y se le advierte de las consecuencias de la compra.
            else if(bolso[1] >= 2 && bolso[6] == 1){
                printf("\n\n'Excellent choice, stranger'.\nReemplazaste tu Escudo de Madera por uno de Hierro.\nSe han sumado 2 dados a tu defensa, pero perdiste la bonificación del Escudo de Madera.\n");
                bolso[3] -= 1;
                bolso[3] += 2;
                bolso[6] = 2;
                bolso[1] -= 2;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 2 && bolso[6] == 2){

                printf("\n\n'Can't carry no more, stranger!'\nYa tienes el Escudo de Hierro.\n");
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 4){
            if(bolso[1] >= 2){
                printf("\n\n'Stranger, stranger!'.\nTres pociones han sido añadidas a tu mochila.\n");
                bolso[0] += 3;
                bolso[1] -= 2;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 5){

            if(bolso[1] >= 3 && bolso[5] == 0){

                printf("\n\nAdquiriste la Espada.\nSe ha sumado 1 dado de ataque.\n");
                bolso[2] += 1;
                bolso[1] -= 3;
                bolso[5] = 1;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 3 && bolso[5] == 1){

                printf("\n\n'Can't carry no more, stranger!'\nYa posees la Espada.\n");
                presionarEnter();
            }

            else if(bolso[1] >= 3 && bolso[5] == 2){

                printf("\n\nYa posees el Hacha Guerrera.\n");
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 6){

            if(bolso[1] >= 3){

                printf("\n\n'Wise choice, mate!'\nSeis pociones fueron sumadas a tu arsenal.\n");
                bolso[0] += 6;
                bolso[1] -= 3;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }
            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 7){

            if(bolso[1] >= 4 && bolso[5] == 0){

                printf("\n\n'Stranger, stranger! Now that's a weapon.'\nAdquiriste el Hacha Guerrera.\nSe añadieron dos dados de ataque.\n");
                bolso[2] += 2;
                bolso[5] = 2;
                bolso[1] -= 4;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 4 && bolso[5] == 1){

                printf("\n\n'Stranger, stranger! Now that's a weapon.\nReemplazaste tu Espada por el Hacha Guerrera.\nSe añadieron dos dados de ataque, pero perdiste el dado de ataque añadido por la Espada.\n");
                bolso[2] -= 1;
                bolso[5] = 2;
                bolso[1] -= 4;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();

            }

            else if(bolso[1] >= 4 && bolso[5] == 2){

                printf("\n\n'Stranger, stranger! Can't carry no more!'\nYa tienes el Hacha Guerrera\n");
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }
        }

        if(catalogo == 8){

            if(bolso[1] >= 5 && bolso[7] == 0){

                printf("\n\n'STRANGER! HA, HA! What do you need that for? Going hunting an elephant?'\nCompraste la Armadura con Espinas.\nAdquiriste 2 dados de ataque y 1 de defensa.\n");
                bolso[2] += 2;
                bolso[3] += 1;
                bolso[7] = 1;
                bolso[1] -= 5;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 5 && bolso[7] == 1){

                printf("\n\nYa posees la Armadura con Espinas.\n");
                presionarEnter();

            }

            else if(bolso[1] >= 5 && bolso[7] == 2){

                printf("\n\nYa posees la Armadura Mágica.\n");
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }

        }

        if(catalogo == 9){

            if(bolso[1] >= 6 && bolso[7] == 0){
                
                printf("\n\n'A choice of an avid armor collector!'\nCompraste la Armadura Mágica.\nSe han añadido 5 dados de defensa a tu arsenal.\n");
                bolso[3] += 5;
                bolso[1] -= 6;
                bolso[7] = 2;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 6 && bolso[7] == 1){

                printf("\n\n'A choice of an avid armor collector!'\nLa Armadura Mágica reemplazó tu Armadura con Espinas.\nSe han añadido 5 dados de defensa a tu arsenal, pero perdiste la bonificación de la Armadura con Espinas.\n");
                bolso[2] -= 2;
                bolso[3] -= 1;
                bolso[3] += 5;
                bolso[7] = 2;
                bolso[1] -= 6;
                printf("\nTe quedan %d tesoros.\n", bolso[1]);
                presionarEnter();
            }

            else if(bolso[1] >= 6 && bolso[7] == 2){

                printf("\n\n'STRANGER! Can NOT carry no more!'\nYa posees la Armadura Mágica.\n");
                presionarEnter();
            }

            else{

                printf("\n\n'Not enough cash, stranger'.\nTesoros insuficientes.\n");
                presionarEnter();
            }

        }
        if(catalogo == 10){
            mostrarCatalogo();
            printf("\nPosees %d tesoros.\n", bolso[1]);


        }
        //Si la opción del catálogo elegida por el usuario es 11, se termina la compra.
        if(catalogo == 11){
            saltarMucho();
            printf("\n'Come back anytime!'\n");
            presionarEnter();
            opcion = 2;
        }
        
    }

    saltarMucho();
    return bolso;
}

/*  Entrada: El tablero de juego y la mochila del jugador.
    Salida: La mochila del jugador modificada.
    Objetivo: Verificar si el jugador se ha encerrado con sus movimientos.
*/
int * jugadorEncerrado(int ** tablero, int * bolso){
    //Se declaran las variables fila y columna, y el arreglo ubicacion.
    int fila;
    int columna;
    int * ubicacion;

    //La ubicacion del jugador es encontrada por la función correspondiente y es guardad en un arreglo representativo.
    ubicacion = encontrarJugador(tablero);
    fila = ubicacion[0];
    columna = ubicacion[1];

    //Se verifica cada cuadro que rodea al jugador en el momento en el cual la función es llamada.
    //Si TODOS los cuadros que rodean al jugador han sido ya atravesados o son inválidos, entonces el bolso se modifica de una manera adecuada.
    if(ubicacion[0] != 0){
        if( tablero[fila - 1][columna - 1] != 0 &&
            tablero[fila - 1][columna] != 0 &&
            tablero[fila - 1][columna + 1] != 0 &&
            tablero[fila][columna + 1] != 0 &&
            tablero[fila + 1][columna + 1] != 0 &&
            tablero[fila + 1][columna] != 0 &&
            tablero[fila + 1][columna - 1] != 0 &&
            tablero[fila][columna - 1] != 0 ){
            //Si la vida del usuario sube a 33, significa que está atrapado.
            bolso[4] = 33;
        }
    }
    //Si el jugador se encuentra en el último nivel antes de llegar a Drácula.
    //Entonces es necesario validar que no tape su camino para el casillero final.
    if(ubicacion[0] == 1){
        //Si los tres casilleros en los cuales es posible acceder a Drácula ya han sido visitados por el jugador (es decir muestran un '3')
        //Entonces significa que su camino está tapado y no puede acceder al casillero final.
        if( tablero[1][4] == 3 &&
            tablero[1][5] == 3 &&
            tablero[1][3] == 3){
            //Esto es demostrado cambiando la cantidad de vidas as 33, que en la función main() será validado en el momento adecuado.
            bolso[4] = 33;
        }
    }
    //Si ninguno de los dos casos es cumplido, entonces el bolso del jugador es entregado tal cual vino como entrada.
    return bolso;
}

/*  Entrada: Nada.
    Salida: Entero 1 si la muerte de Drácula es efectiva.
    Objetivo: Romper el ciclo en la función main() si el enemigo final ha sido derrotado.
*/
int muerteDracula(){
    //Se declara la variable condicion.
    int condicion;

    //Se le hace notar al usuario que ganó el juego derrotando al jefe final.
    printf("\nDerrotaste a Drácula.\nEres el ganador.\n¡Bien hecho, enano!\n¡Hora de resumir las calderas y el minaje a todo volumen!\n¡HAY UNA GUERRA QUE GANAR!\n");
    presionarEnter();
    printf("\nHas ganado el juego.\n");
    //La condición es cambiada a 1.
    condicion = 1;
    presionarEnter();

    //Se retorna la condición para romper el ciclo en la funcion principal.
    return condicion;
}

/*  Entrada: Nada.
    Salida: Entero 1, si el jugador ha muerto.
    Objetivo: Revisar si el jugador ha muerto en batalla.
*/
int muerteJugador(){
    //Variable condición declarada.
    int condicion;

    //Se le avisa al jugador sobre su muerte y que perdió el juego.
    printf("\nHas muerto.\nTodos tus esfuerzos fueron en vano.\n¿Por qué paso esto?\nEsas preguntas no son importantes ahora...\nSientes como se nubla tu vista...\nEl dolor es ahora perfectamente ignorable...\n");
    presionarEnter();
    printf("\nFallaste tu misión.\nEl juego termina.\n");
    //La condición es cambiada de forma adecuada.
    condicion = 1;
    presionarEnter();

    //Se retorna la condición cambiada.
    return condicion;
}

/*  Entrada: La mochila del jugador, los dados de ataque y defensa del jugador y enemigo, una ID del mounstro a batallar.
    Salida: La mochila del jugador actualizada después de la batalla.
    Objetivo: Cuando el jugador se enfrente a un enemigo, esta función desarrollará toda la batalla.
*/
int * batallar(int * bolso, int dadosAtaqueEnemigo, int dadosDefensaEnemigo, int dadosAtaqueJugador, int dadosDefensaJugador, int monstruo){
// bolso = [pocion, tesoro, dadosAtaque, dadosDefensa, vida, arma, escudo, armadura]

    saltarMucho();

/*  Las variables declaradas son las siguientes:

    Instancia: Cantidad de hechos ocurridos (dados lanzados).
    Lanzamiento: El número del dado que alguno de los peleadores lanzó.
    Resultado: Se guardan los resultados de los dados obtenidos.

    dadoLanzado Ataque/Defensa Enemigo/Jugador [dados Ataque/Defensa Enemigo/Jugador]: Arreglo donde se guardarán cada uno de los resultados obtenidos por los lanzamientos de los dados. 
                                                                                       Tanto del jugador como del enemigo, tanto como en defensa y ataque.

    ataque/defensa Enemigo/Jugador: La cantidad de 'seis' obtenidos en los lanzamientos para cada instancia es guardada en éstas variables.

    finalCombate: Si el combate termina, ésta variable cambia para romper el ciclo.
    derrotaDracula: Si Drácula es derrotado, ésta variable cambia su valor, para así poder modificar la mochila del jugador de manera adecuada.
*/ 

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
    int derrotaDracula = 0;

    //Mientras finalCombate sea 0, el ciclo continuará.
    while(finalCombate == 0){
        //El enemigo comienza el combate atacando al jugador.
        for(instancia = 1; instancia <= dadosAtaqueEnemigo; instancia++){
            resultado = lanzarDado();
            //Dependiendo de la cantidad de dados de ataque que posea el enemigo, estos resultados son guardados en el arreglo adecuado.
            dadoLanzadoAtaqueEnemigo[instancia - 1] = resultado;

            }
        //Dependiendo de la cantidad de lanzamientos, estos son informados al jugador por pantalla.
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
            //Dependiendo de la cantidad de 6 obtenidos, se le informa al jugador sobre los ataques que están a punto de venir.
            printf("\nEl enemigo prepara %d ataque(s).\n", ataqueEnemigo);
            printf("Preparas tu mejor defensa...\n");
            presionarEnter();
            saltarMucho();

            //Análogamente, comienza la defensa del jugador.
            for(lanzamiento = 0; lanzamiento < dadosDefensaJugador; lanzamiento++){

                printf("Lanzaste un %d.\n", dadoLanzadoDefensaJugador[lanzamiento]);
            }
            //Se busca la cantidad de 'seis' obtenidos en los lanzamientos de los dados de defensa del jugador.
            defensaJugador = buscarSeis(dadoLanzadoDefensaJugador, dadosDefensaJugador);
            //Se le informa al jugador de cuántos ataques fueron bloqueados.
            printf("\nBloqueaste %d ataque(s).\n", defensaJugador);

            //Si la resta de la cantidad de '6' lanzados en la defensa del jugador con la cantidad de '6' en el ataque del enemigo es negativa, el jugador pierde una o más vidas.
            if((defensaJugador - ataqueEnemigo) < 0){
                

                aleatorizarFrase(1); // ID 1: El jugador pierde vida.
                //Se le informa al jugador cuántas vidas perdio en el ataque.
                printf("Perdiste %d vida(s).\n", -1*(defensaJugador - ataqueEnemigo));
                //Se le restan las vidas correspondiente al jugador.
                bolso[4] += (defensaJugador - ataqueEnemigo);
                //Se le informa al jugador cuántas vidas le restan.
                printf("Te quedan %d vidas.\n", bolso[4]);
                presionarEnter();

                //Si la vida del jugador se reduce a 0 o menor, el combate debe terminar en ese mismo instante.
                if(bolso[4] <= 0){

                    break;

                }

                saltarMucho();
            }
            //Si esta operación es mayor o igual a 0, siognifca que el jugador bloqueo todos los ataques que le fueron lanzados.
            if((defensaJugador - ataqueEnemigo) >= 0){

                aleatorizarFrase(2); // ID 2: El jugador bloquea todos los ataques del enemigo.
                presionarEnter();
                saltarMucho();
            }            
        }
        //Si la variable ataqueEnemigo sigue siendo 0, el enemigo falla todos sus ataques.
        else if(ataqueEnemigo == 0){

            aleatorizarFrase(3); // ID 3: El enemigo falla sus ataques.
        }

        aleatorizarFrase(4); // ID 4: El jugador prepara ataques.
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

            aleatorizarFrase(5); // ID 5: El jugador falla sus ataques.
        }

        presionarEnter();
        saltarMucho();

        if(ataqueJugador >= 1 && dadosDefensaEnemigo == 0){

            aleatorizarFrase(6); // ID 6: El jugador gana el combate.
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
                derrotaDracula = 1;

            }

            if((defensaEnemigo - ataqueJugador) >= 0){
                aleatorizarFrase(7); // ID 7: El enemigo esquiva todos los ataques.
                presionarEnter();
                saltarMucho();
            }   
        }
    }

    if(derrotaDracula == 1){
        //The answer to life, the universe and everything.
        bolso[4] = 42;  
    }
    //Se retorna el bolso modificado.
    return bolso;
}

/*  Entrada: El tablero del juego y la mochila del jugador.
    Salida: Mochila del jugador actualizada.
    Objetivo: Dependiendo de lo que el jugador encuentre o se enfrente, es necesario modificar pociones, tesoros o vidas, todas guardadas en el arreglo que hace referncia a la mochila del jugador.
*/
int * encontrarEntidad(int ** tablero, int * bolso){

/* Esta función es sumamente repetitiva, por lo tanto la explicación es la siguiente:

    Primero se busca la ubicación del jugador y es guardada en un arreglo (ubicacion).
    Dependiendo de la fila en la cual el jugador se encuentre (información guardada en ubicacion[0]), se entra al condicional adecuado.
    Una vez dentro del condicional adecuado, se procede a lanzar el dado.
    Según el resultado del dado y la tabla referenciada en el enunciado del proyecto, se le informa al jugador que encontró o con quién batallará.

    Si es batalla se llama a la función batalla con los parámetros del enemigo correspondientes.
    Si es poción o tesoro, se le suma a su mochila los items adecuados.
*/

    int * ubicacion;
    int dado;
    //La ubicación del jugador en el tablero es encontrada con la función adecuada y guardada en un arreglo.
    ubicacion = encontrarJugador(tablero);

    if(ubicacion[0] == 10){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){
            aleatorizarFrase(20);
            bolso[0] += 1;
            presionarEnter();
        }

        if(dado > 1 && dado < 5){
            
            aleatorizarFrase(8);
            presionarEnter();
            batallar(bolso, 1, 0, bolso[2], bolso[3], 1);
        }

        if(dado == 5){
            aleatorizarFrase(22);
            presionarEnter();
        }

        if(dado == 6){
            aleatorizarFrase(21);
            bolso[1] += 1;
            presionarEnter();
        }

    }

    if(ubicacion[0] == 9){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){
            aleatorizarFrase(8);
            presionarEnter();
            bolso = batallar(bolso, 1, 0, bolso[2], bolso[3], 1);
            
        }

        if(dado == 2){
            aleatorizarFrase(9);
            presionarEnter();
            bolso = batallar(bolso, 2, 0, bolso[2], bolso[3], 2);

        }

        if(dado == 3){
            aleatorizarFrase(22);
            presionarEnter();
        }

        if(dado == 4){
            aleatorizarFrase(22);
            presionarEnter();
        }

        if(dado == 5){
            aleatorizarFrase(22);
            presionarEnter();
        }

        if(dado == 6){
            aleatorizarFrase(21);
            bolso[1] += 1;
            presionarEnter();
        }
    }

    if(ubicacion[0] == 8){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){
            aleatorizarFrase(8);
            presionarEnter();
            bolso = batallar(bolso, 1, 0, bolso[2], bolso[3], 1);
        }

        if(dado == 2){
            aleatorizarFrase(9);
            presionarEnter();
            bolso = batallar(bolso, 2, 0, bolso[2], bolso[3], 2);

        }

        if(dado == 3){
            aleatorizarFrase(10);
            presionarEnter();
            bolso = batallar(bolso, 3, 0, bolso[2], bolso[3], 3);
        }

        if(dado == 4){
            aleatorizarFrase(21);
            bolso[1] += 1;
            presionarEnter();
        }

        if(dado == 5){
            aleatorizarFrase(20);
            bolso[0] += 1;
            presionarEnter();
        }

        if(dado == 6){
            aleatorizarFrase(22);
            presionarEnter();
        }
    }

    if(ubicacion[0] == 7){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){
            aleatorizarFrase(8);
            presionarEnter();
            bolso = batallar(bolso, 1, 0, bolso[2], bolso[3], 1);

        }

        if(dado == 2){
            aleatorizarFrase(9);
            presionarEnter();
            bolso = batallar(bolso, 2, 0, bolso[2], bolso[3], 2);
        }

        if(dado == 3){
            aleatorizarFrase(10);
            presionarEnter();
            bolso = batallar(bolso, 3, 0, bolso[2], bolso[3], 3);

        }

        if(dado == 4){
            aleatorizarFrase(11);
            presionarEnter();
            bolso = batallar(bolso, 4, 0, bolso[2], bolso[3], 4);
        }

        if(dado == 5){
            aleatorizarFrase(21);
            presionarEnter();
            bolso[1] += 1;
        }

        if(dado == 6){
            aleatorizarFrase(22);
            presionarEnter();
        }
    }

    if(ubicacion[0] == 6){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){
            aleatorizarFrase(9);
            presionarEnter();
            bolso = batallar(bolso, 2, 0, bolso[2], bolso[3], 2);
        }

        if(dado == 2){
            aleatorizarFrase(10);
            presionarEnter();
            bolso = batallar(bolso, 3, 0, bolso[2], bolso[3], 3);
        }

        if(dado == 3){
            aleatorizarFrase(11);
            presionarEnter();
            bolso = batallar(bolso, 4, 0, bolso[2], bolso[3], 4);
        }

        if(dado == 4){
            aleatorizarFrase(12);
            presionarEnter();
            bolso = batallar(bolso, 5, 0, bolso[2], bolso[3], 5);
        }

        if(dado == 5){
            aleatorizarFrase(21);
            bolso[1] += 1;
            presionarEnter();
        }

        if(dado == 6){
            aleatorizarFrase(22);
            presionarEnter();
        }
    }

    if(ubicacion[0] == 5){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){

            aleatorizarFrase(10);
            presionarEnter();
            bolso = batallar(bolso, 3, 0, bolso[2], bolso[3], 3);
        }

        if(dado == 2){

            aleatorizarFrase(11);
            presionarEnter();
            bolso = batallar(bolso, 4, 0, bolso[2], bolso[3], 4);
        }

        if(dado == 3){

            aleatorizarFrase(12);
            presionarEnter();
            bolso = batallar(bolso, 5, 0, bolso[2], bolso[3], 5);
        }

        if(dado == 4){

            aleatorizarFrase(13);
            presionarEnter();
            bolso = batallar(bolso, 6, 0, bolso[2], bolso[3], 6);
        }

        if(dado == 5){

            aleatorizarFrase(21);
            presionarEnter();
            bolso[1] += 1;
        }

        if(dado == 6){

            aleatorizarFrase(20);
            presionarEnter();
            bolso[0] += 1;
        }
    }

    if(ubicacion[0] == 4){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){

            aleatorizarFrase(11);
            presionarEnter();
            bolso = batallar(bolso, 4, 0, bolso[2], bolso[3], 4);
        }

        if(dado == 2){

            aleatorizarFrase(12);
            presionarEnter();
            bolso = batallar(bolso, 5, 0, bolso[2], bolso[3], 5);
        }

        if(dado == 3){

            aleatorizarFrase(13);
            presionarEnter();
            bolso = batallar(bolso, 6, 0, bolso[2], bolso[3], 6);
        }

        if(dado == 4){

            aleatorizarFrase(14);
            presionarEnter();
            bolso = batallar(bolso, 7, 0, bolso[2], bolso[3], 7);
        }

        if(dado == 5){

            aleatorizarFrase(21);
            bolso[1] += 1;
            presionarEnter();  
        }

        if(dado == 6){

            aleatorizarFrase(22);
            presionarEnter();
        }
    }   

    if(ubicacion[0] == 3){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){

            aleatorizarFrase(12);
            presionarEnter();
            bolso = batallar(bolso, 5, 0, bolso[2], bolso[3], 5);
        }

        if(dado == 2){

            aleatorizarFrase(13);
            presionarEnter();
            bolso = batallar(bolso, 6, 0, bolso[2], bolso[3], 6);
             
        }

        if(dado == 3){

            aleatorizarFrase(14);
            presionarEnter();
            bolso = batallar(bolso, 7, 0, bolso[2], bolso[3], 7); 
        }

        if(dado == 4){

            aleatorizarFrase(15);
            presionarEnter();
            bolso = batallar(bolso, 8, 0, bolso[2], bolso[3], 8);
        }

        if(dado == 5){

            aleatorizarFrase(21);
            presionarEnter();
            bolso[1] += 1;
        }

        if(dado == 6){

            aleatorizarFrase(22);
            presionarEnter();
        }
    }

    if(ubicacion[0] == 2){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){

            aleatorizarFrase(13);
            presionarEnter();
            bolso = batallar(bolso, 6, 0, bolso[2], bolso[3], 6);
        }

        if(dado == 2){

            aleatorizarFrase(14);
            presionarEnter();
            bolso = batallar(bolso, 7, 0, bolso[2], bolso[3], 7);

        }

        if(dado == 3){

            aleatorizarFrase(15);
            presionarEnter();
            bolso = batallar(bolso, 8, 0, bolso[2], bolso[3], 8);
        }

        if(dado == 4){

            aleatorizarFrase(16);
            presionarEnter();
            bolso = batallar(bolso, 9, 0, bolso[2], bolso[3], 9);
        }

        if(dado == 5){

            aleatorizarFrase(21);
            presionarEnter();
            bolso[1] += 1;  
        }

        if(dado == 6){

            aleatorizarFrase(20);
            presionarEnter();
            bolso[0] += 1;
        }
    }

    if(ubicacion[0] == 1){

        dado = lanzarDado();
        //Se le informa al jugador del resultado de su lanzamiento.
        printf("\nLanzaste un %d \n", dado);

        if(dado == 1){

            aleatorizarFrase(14);
            presionarEnter();
            bolso = batallar(bolso, 7, 0, bolso[2], bolso[3], 7);
        }

        if(dado == 2){

            aleatorizarFrase(15);
            presionarEnter();
            bolso = batallar(bolso, 8, 0, bolso[2], bolso[3], 8);
        }

        if(dado == 3){

            aleatorizarFrase(16);
            presionarEnter();
            bolso = batallar(bolso, 9, 0, bolso[2], bolso[3], 9);
        }

        if(dado == 4){

            aleatorizarFrase(666);
            presionarEnter();
            bolso = batallar(bolso, 10, 0, bolso[2], bolso[3], 10);
        }

        if(dado == 5){

            aleatorizarFrase(21);
            presionarEnter();
            bolso[1] += 1;
        }

        if(dado == 6){

            aleatorizarFrase(22);
            presionarEnter();
        }
    }
    
    if(ubicacion[0] == 0){

        printf("\n\nSientes el ambiente cambiar...\nNunca antes habías sentido algo por el estilo...\nLa penumbra te encapsula más y más.\n");
        printf("\nSientes tus párpados abrirse para poder captar la poca claridad restante...\n");
        printf("\nEmpieza a correr sangre por las paredes que te rodean...\n");
        printf("\nUna figura encapuchada aparece frente a ti...\nMuestra su rostro...\nEs horriblemente pálido y sus ojos rojos te abruman con miedo...\n");
        printf("\nUn grito irreconocible llena tus oidos de terror...\n");
        presionarEnter();
        saltarMucho();
        printf("\nÉsta bestia es la que empezó toda esta tragedia...\n");
        printf("\nCamina lentamente hacia a ti...\n");
        printf("\nSacas tus armas...\nY te preparas para el COMBATE FINAL.\n");
        presionarEnter();
        saltarMucho();
        printf("\nTodo lo que has pasado hasta el momento...\n");
        printf("\nHora de demostrar lo que realmente vales.\n");
        printf("\nHora de matar a DRÁCULA.\n");
        presionarEnter();
        saltarMucho();

        bolso = batallar(bolso, 9, 9, bolso[2], bolso[3], 9);

    }
    //Una vez que el jugador ya terminó de batallar, o ya se le sumó la poción o tesoro encontrado, o simplemente encontró nada, se abren las opciones de compra y beber pociones.
    //Si el jugador todavía sigue con vida y no se encuentra en el casillero donde reside Drácula.
    if(bolso[4] > 0 && ubicacion[0] != 0){
        //Si el jugador tiene pociones.
        if(bolso[0] > 0)
            bolso = beberPocion(bolso);

        //Si el jugador tiene tesoros.
        if(bolso[1] > 0)
          bolso = comprar(bolso);

        return bolso;
        saltarMucho();        
    
    }

    return bolso;
}

/*  Entrada: El tablero, la jugada ingresada por el jugador, la fila y columna del jugador.
    Salida: La jugada validad, si fuese necesario.
    Objetivo: Validar las jugadas de acuerdo al tablero que el jugado ingresa.
*/
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
        while(jugada > 3){

            printf("\nJugada inválida.\n");
            jugada = ingresarJugada();
            //Se vuelve a enviar la nueva jugada ingresada a la misma función presente.
            //De esta forma queda asegurado que la jugada ingresada será pedida de nuevo cuantas veces sea necesario.
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

/*  Entrada: El tablero del juego.
    Salida: El tablero del juego, actualizado con las jugadas válidas mostradas por pantalla.
    Objetivo: Mostrar las jugadas válidas disponibles al jugador.
*/
int ** mostrarJugadasValidas(int ** tablero){

    int * ubicacion;
    int fila;
    int columna;

    //Se busca la posición del jugador en el tablero y se guarda los parametros en el arreglo correspondiente.
    ubicacion = encontrarJugador(tablero);
    fila = ubicacion[0];
    columna = ubicacion[1];

    //Se ignora la primera fila para evitar errores catástroficos de fuera de rango.
    if(ubicacion[0] != 0 && ubicacion[1] != 0){
        //Siempre y cuando exista un 0 (casillero disponible), se escribirá el número de la jugada válida.
        //Como ya se habían ocupado los números 1, 2 y 3 para otras funciones, se decidió por representarlas con numeros de dos dígitos.
        if(tablero[fila - 1][columna - 1] == 0)
            tablero[fila - 1][columna - 1] = 11;

        if(tablero[fila - 1][columna] == 0)
            tablero[fila - 1][columna] = 22;

        if(tablero[fila - 1][columna + 1] == 0)
            tablero[fila - 1][columna + 1] = 33;

        if(tablero[fila][columna + 1] == 0)
            tablero[fila][columna + 1] = 44;

        if(tablero[fila + 1][columna + 1] == 0)
            tablero[fila + 1][columna + 1] = 55;

        if(tablero[fila + 1][columna] == 0)
            tablero[fila + 1][columna] = 66;

        if(tablero[fila + 1][columna - 1] == 0)
            tablero[fila + 1][columna - 1] = 77;

        if(tablero[fila][columna - 1] == 0)
            tablero[fila][columna - 1] = 88;
    }
    //Para evitar que la función entre en índices menores a 0 y aniquile la función liberarTablero(), se impide que, si el jugador se encuentra en la columna 0, muestre jugadas válidas en posiciones con índices menores a 0.
    //En este caso el 1,7 y 8.
    else if(ubicacion[0] != 0 && ubicacion[1] == 0){

        if(tablero[fila - 1][columna] == 0)
            tablero[fila - 1][columna] = 22;

        if(tablero[fila - 1][columna + 1] == 0)
            tablero[fila - 1][columna + 1] = 33;

        if(tablero[fila][columna + 1] == 0)
            tablero[fila][columna + 1] = 44;

        if(tablero[fila + 1][columna + 1] == 0)
            tablero[fila + 1][columna + 1] = 55;

        if(tablero[fila + 1][columna] == 0)
            tablero[fila + 1][columna] = 66;


    }
    //Se retorna el tablero ya modificado con las jugadas válidas.
    return tablero;
}

/*  Entrada: El tablero del juego.
    Salida: El tablero modificado.
    Objetivo: Borrar las jugadas válidas del turno anterior, para poder mostrar las del turno siguiente.
*/
int ** limpiarTablero(int ** tablero){

    int fila;
    int columna;

    //Un doble ciclo for para recorrer el arreglo bidimensional.
    for(fila = 0; fila < 12; fila++){
        for(columna = 0; columna < 9; columna++){
            //Si encuentra cualquiera de las representaciones de jugadas válidas, las reemplaza por un 0 (casillero disponible)
            if(tablero[fila][columna] == 11 || tablero[fila][columna] == 22 || tablero[fila][columna] == 33 || tablero[fila][columna] == 44 || tablero[fila][columna] == 55 || tablero[fila][columna] == 66 || tablero[fila][columna] == 77 || tablero[fila][columna] == 88)
                tablero[fila][columna] = 0;
        }
    }

    return tablero;
}

/*  Entrada: El tablero y la jugada realizada.
    Salida: El tablero modificado con la jugada realizada.
    Objetivo: Ingresar la jugada pedida por el usuario al tablero de juego.
*/
int ** modificarTablero(int ** tablero, int jugada){
    int * ubicacion;
    int fila;
    int columna;

    //Se busca al jugador con la función adecuada y su ubicación es guardad en un arreglo de nombre representativo.
    ubicacion = encontrarJugador(tablero);
    //La fila y columna de la ubicación del jugador son guardads en variables representativas.
    fila = ubicacion[0];
    columna = ubicacion[1];

    //Dependiendo de la jugada pedida por el jugador, el tablero es modificado de manera adecuada.
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

    //El casillero del turno anterior es reemplazado por un 3, simbolizando que es un casillero ya visitado.
    tablero[fila][columna] = 3;

    //Se retorna el tablero ya modificado.
    return tablero;

}

/*  Entrada: Un entero de dos dígitos.
    Salida: Un entero de un dígito.
    Objetivo: Convertir representaciones de jugadas válidas a números de un sólo dígito para ser mostradas por pantalla de manera legible.
*/
int cambiarDobleASolo(int doble){

    int solo;

    if(doble == 11)
        solo = 1;

    if(doble == 22)
        solo = 2;

    if(doble == 33)
        solo = 3;

    if(doble == 44)
        solo = 4;

    if(doble == 55)
        solo = 5;

    if(doble == 66)
        solo = 6;

    if(doble == 77)
        solo = 7;

    if(doble == 88)
        solo = 8;

    return solo;
}

/*  Entrada: Nada.
    Salida: Nada.
    Objetivo: Mostrar por pantalla el arte ASCII correspondiente al título del juego.
*/
void tituloJuego(){

    printf(" _______ _______ _       _______      ______          _       _______ _______ _______ _            ______  _______ _______         \n");

    printf("(  ____ (  ___  ( %c     (  ___  )    (  __  %c|%c     /( (    /(  ____ (  ____ (  ___  ( (    /|    (  __  %c(  ___  (  ____ |%c     /|\n", 92, 92, 92, 92, 92);

    printf("| (    %c| (   ) | (     | (   ) |    | (  %c  | )   ( |  %c  ( | (    %c| (    %c| (   ) |  %c  ( |    | (  %c  | (   ) | (    %c| )   ( |\n",92,92,92,92,92,92,92,92);

    printf("| (_____| |   | | |     | |   | |    | |   ) | |   | |   %c | | |     | (__   | |   | |   %c | |    | |   ) | (___) | (_____| (___) |\n",92,92);

    printf("(_____  | |   | | |     | |   | |    | |   | | |   | | (%c %c) | | ____|  __)  | |   | | (%c %c) |    | |   | |  ___  (_____  |  ___  |\n",92,92,92,92);

    printf("      ) | |   | | |     | |   | |    | |   ) | |   | | | %c   | | %c_  | (     | |   | | | %c   |    | |   ) | (   ) |     ) | (   ) |\n",92,92,92);

    printf("/%c____) | (___) | (____/| (___) |    | (__/  | (___) | )  %c  | (___) | (____/| (___) | )  %c  |    | (__/  | )   ( /%c____) | )   ( |\n",92,92,92,92);

    printf("%c_______(_______(_______(_______)    (______/(_______|/    )_(_______(_______(_______|/    )_)    (______/|/     %c%c_______|/     %c|\n",92,92,92,92);
    
    return;
}

/*  Entrada: Nada.
    Salida: Nada.
    Objetivo: Mostrar por pantalla el arte ASCII correspondiente al nombre de la mina donde el jugador se desenvuelve.
*/
void tituloMina(){

    printf(" ______  _______ _______         _       _______________________ _       _______ \n");
    printf("(  ___ %c(  ____ (  ___  |%c     /( (    /(  ____ %c__   __(  ___  ( (    /(  ____ %c\n",92,92,92,92);
    printf("| (   ) | (    )| (   ) | )   ( |  %c  ( | (    %c/  ) (  | (   ) |  %c  ( | (    %c/\n",92,92,92,92);
    printf("| (__/ /| (____)| |   | | | _ | |   %c | | (_____   | |  | |   | |   %c | | (__    \n",92,92);
    printf("|  __ ( |     __| |   | | |( )| | (%c %c) (_____  )  | |  | |   | | (%c %c) |  __)   \n",92,92,92,92);
    printf("| (  %c %c| (%c (  | |   | | || || | | %c   |     ) |  | |  | |   | | | %c   | (      \n",92,92,92,92,92);
    printf("| )___) | ) %c %c_| (___) | () () | )  %c  /%c____) |  | |  | (___) | )  %c  | (____/%c\n",92,92,92,92,92,92);
    printf("|/ %c___/|/   %c__(_______(_______|/    )_%c_______)  )_(  (_______|/    )_(_______/\n",92,92,92);

    return;
}

/*  Entrada: El tablero en forma de arreglo.
    Salida: Nada.
    Objetivo: Mostrar por pantalla un tablero legible para que el jugador pueda entender de mejor manera el desarrollo del juego.
*/
void imprimirTablero(int ** tablero){

    int fila;
    int columna;

    saltarMucho();
    //Se muestar el nombre de la mina.
    tituloMina();

    printf("\n\n\n");
    for ( fila = 0; fila < 12; fila++ ) {

        for ( columna = 0; columna < 9; columna++ ) {

            //Si la columna es necesario un salto de linea para separar los niveles correspondientes.
            if(columna == 8 && tablero[fila][columna] == 0){
                printf("||||   |\n");
                printf("\t---------------------------------------------------------------------\n");
            }
            //Si el jugador se encuentra en el lugar especificado, éste es representado por una X, más un salto de linea.
            else if(columna == 8 && tablero[fila][columna] == 1){
                printf("|||| X |\n");
                printf("\t---------------------------------------------------------------------\n");
            }

            else if(columna == 8 && tablero[fila][columna] == 2){
                printf("        \n");
                printf("\t---------------------------------------------------------------------\n");
            }
            //Si el casillero ya ha sido ocupado entonces se representa de una forma legible, más un salto de linea.
            else if(columna == 8 && tablero[fila][columna] == 3){
                printf("||||///|\n");
                printf("\t---------------------------------------------------------------------\n");
            }

            //Si la columna es la primera, con objetivo de centrar el tablero, se agrega una tabulación.
            else if(columna == 0 && tablero[fila][columna] == 0)
                printf("\t|   |");

            else if(columna == 0 && tablero[fila][columna] == 1)
                printf("\t| X |");

            else if(columna == 0 && tablero[fila][columna] == 2)
                printf("\t     ");
            //Si el casillero ya ha sido ocupado entonces se representa de una forma legible.
            else if(columna == 0 && tablero[fila][columna] == 3)
                printf("\t|///|");


            //Si el jugador se encuentra al inicio del tablero entonces es necesario mostrar la X solamente.
            else if(fila == 11 && columna == 4 && tablero[fila][columna] == 1)
                printf("   | X |");

            else if(fila == 11 && columna == 4 && tablero[fila][columna] == 3)
                printf("   |///|");
            //El casillero final.
            else if(fila == 0 && columna == 4 && tablero[fila][columna] == 0)
                printf("   |   |");

            //Si existe un 0, la casilla se muestra vacía.
            else if(tablero[fila][columna] == 0)
                printf("||||   |");

            //Si existe un 1, se muestra la posción del jugador.
            else if(tablero[fila][columna] == 1)
                printf("|||| X |");

            //Si la casilla es un 2, es una fila inaccesible, es muestra solo espacios.
            else if(tablero[fila][columna] == 2)
                printf("        ");

            //Si existe un 3, es un casillero ya circulado, se muestra de forma legible.
            else if(tablero[fila][columna] == 3)
                printf("||||///|");

            
            //Se muestra por pantalla las jugadas válidas utilizando la función cambiarDobleASolo().
            else if(columna == 8){
                printf("|||| %d |\n", cambiarDobleASolo(tablero[fila][columna]));
                printf("\t---------------------------------------------------------------------\n");
            }

            else if(columna == 0)
                printf("\t| %d |", cambiarDobleASolo(tablero[fila][columna]));

            else if(fila == 0 && columna == 4 && tablero[fila][columna] != 0)
                printf("\t| %d |", cambiarDobleASolo(tablero[fila][columna]));


            else
                printf("|||| %d |", cambiarDobleASolo(tablero[fila][columna]));
        }
    }

    return;
}

int main(){
    // Presentación del juego.
    saltarMucho();
    printf("\n\nBienvenido a...\n\n");
    tituloJuego();
    presionarEnter();

    saltarMucho();

    //Se le pregunta al jugador qué tipo de semilla alimentará al módulo random.
    int suerte;
    printf("\nAntes de empezar es necesario que tomes una decisión importantísima...\n");
    printf("\n¿Desearás dejar tu suerte a una semilla o prefieres dejarla al destino?\nPor favor elegir una opción:\n");
    printf("\n1. Deseo ingresar mi propia suerte basada en una semilla.\n2. Mi suerte será dejada al destino.\n>> ");
    scanf("%d", &suerte);
    getchar();

    //Se valida la opción que ingresó el usuario.
    while(suerte > 2 || suerte < 1){

        printf("\nPor favor, eliga una opción válida.\n");
        printf("\n1. Deseo ingresar mi propia suerte basada en una semilla.\n2. Mi suerte será dejada al destino.\n>> ");
        scanf("%d", &suerte);
        getchar();
    }

    //Si eligió una semilla específica, ésta es preguntada y el módulo random iniciado como corresponde.
    if(suerte == 1){
        int semilla;
        printf("\nEspero que sepas lo que estás haciendo...\nPor favor, ingresar una semilla\n>> ");
        scanf("%d", &semilla);
        getchar();

        srand(semilla);
    }

    //Caso contrario, se alimenta el módulo random con el tiempo, utilizando la función time.
    if(suerte == 2){

        printf("\nConfiar en el destino no siempre es lo mejor...\n");

        srand(time(NULL));

        presionarEnter();
    }
    //Presentación de la historia.
    saltarMucho();
    printf("\nHola ahí, mi nombre es Kelsier.\nNacido de la bruma de profesión y catalizador de los 16 metales.\nComo puedes ver, estoy muerto.\nMorí en la rebelión para derrocar al Lord Ruler hace casi 500 años.\n");
    printf("Como ya debes saber, estamos en guerra contra el Imperio Agrónomo, que desea terminar con el minaje y exterminar a todo Misting restante.\n");
    presionarEnter();
    saltarMucho();
    printf("\nEstamos en nuestra hora más oscura, el Imperio ha enviado a sus mejor capitán, Drácula, con sus secuaces para ocupar e impedir el minaje de BROWNSTONE. Y lo ha conseguido.\n");
    printf("Ustedes, los enanos, nos han ayudado a minar este valioso metal de color negro que entrega poderes inigualables a los Mistings y con ésta ayuda, hasta el momento, estabamos ganando la guerra.\n");
    presionarEnter();
    saltarMucho();
    printf("\nMuchos de tus compatriotas yacen muertos en intentos futiles de recuperar el territorio.\nEntiendo que la carga que recae en tus hombros es inmensa, pero de ti depende el desenlace de ésta guerra.\n");
    printf("Si no recuperas BROWNSTONE, el Imperio derrotará nuestros ejercitos y el minaje, junto a tu raza y la mía, desaparecerán.\n");
    presionarEnter();
    saltarMucho();
    printf("\nYo te acompañaré en tu travesía y te ayudaré en todo lo que pueda.\nTodo depende de ti.\n");
    presionarEnter();
    saltarMucho();
    printf("\nEntras con miedo por un portal de madera.\n'Todo depende de mi...'\n");
    presionarEnter();
    saltarMucho();

    //El juego comienza como tal.

/*  Se definen las siguientes variables:
    
    Jugada corresponde al valor ingresado por el jugador a la hora de moverse a través del tablero.
    Ubicación corresponde a la posición (fila y columna) del jugador en el momento actual.
    Mochila es un arreglo donde se guarda toda la información actualizada del jugador a medida que avanza por el juego (Armas, pociones, tesoros y vida).
    Tablero es un arreglo de dos dimensiones que representa el tablero, en forma de una "matriz".
    Condición corresponde a 0 si el juego debe seguir, ó 1 si el juego debe terminar (jugador muere, Drácula es derrotado o el jugador ha encerrado su camino). 
*/    
    int jugada;
    int * ubicacion;
    int * mochila;
    int ** tablero;
    int condicion;

    //La condición inicial es 0, el juego debe continuar.
    condicion = 0;
    //Se genera la primera versión del tablero, con el jugador en la posición inicial.
    tablero = generarTablero();
    //Se muestran las jugadas válidas que el jugador puede realizar visualmente en el tablero.
    tablero = mostrarJugadasValidas(tablero);
    //Se genera la mochila con todos los valores de pociones, tesoros, armamento, dados y vida iniciales.
    mochila = generarMochila();

    //Se imprime el tablero inicial.
    imprimirTablero(tablero);

    //Se "limpia" el tablero de las jugadas válidas mostradas visualmente con anterioridad para hacer espacio a las jugadas válidas del siguiente turno.
    tablero = limpiarTablero(tablero);

    //Se muestran todos los items que el jugador posee al momento del juego, en este  caso: todo lo inicial.
    imprimirMochila(mochila);

    //Mientras la condición siga siendo 0, el juego debe continuar.
    while(condicion == 0){

        //Se guarda en la variable jugada, el número correspondiente a la jugada que el jugador ingresó.
        jugada = ingresarJugada();
        //Se guarda en un arreglo unidimensional el número de fila y columna donde el jugador se encuentra.
        ubicacion = encontrarJugador(tablero);
        //Utilizando la ubicación del jugador obtenida anteriormente, el tablero generado y la jugada ingresada, se procede a validar ésta última.
        jugada = validarJugada(tablero, jugada, ubicacion[0], ubicacion[1]);

        saltarMucho();

        //Una vez validada la jugada ingresada por el usuario, se modifica el tablero con la correspondiente.
        tablero = modificarTablero(tablero, jugada);
        //Se muestran en el tablero todas las jugadas válidas disponibles al jugador.
        tablero = mostrarJugadasValidas(tablero);

        //Dependiendo de la posición del jugador (fila) y el resultado del lanzamiento de un dado, se definirá con qué entidad el jugador se encontrará en cada casillero al cual ha llegado.
        //El resultado de lo que sea que haya encontrado (poción, tesoro, batalla o simplemente nada), es guardado en la mochila generada con anterioridad.
        mochila = encontrarEntidad(tablero, mochila);

        //Se imprime el tablero actualizado.
        imprimirTablero(tablero);

        //Se eliminan las jugadas válidas mostradas con anterioridad para hacer espacio a las jugadas válidas del siguiente turno.
        tablero = limpiarTablero(tablero);

        //Se asegura que el jugador NO haya quedado encerrado por sus propios movimientos, si esto fuese así, se genera un número en el arreglo 'mochila' para indicar que el juego debe terminar.
        //Este número generado es el 33 en la parte de vidas (mochila[4]).
        mochila = jugadorEncerrado(tablero, mochila);

        //Se le muestra al jugador los items que hasta el momento posee.
        imprimirMochila(mochila);

        //Si en el índice 4 del arreglo mochila, que es donde se guardan las vidas, se reduce a 0 o menor a 0, el jugador muere y el juego termina.
        if(mochila[4] <= 0){

            saltarMucho();
            saltarMucho();
            //La condición de término (condicion = 1) es entregada por el return de la funcion muerteJugador().
            condicion = muerteJugador();
        }

        //Si el jugador mata a Drácula, se cambia la vida del jugador por un número específico que indica la victoria.
        if(mochila[4] == 42){

            saltarMucho();
            saltarMucho();
            //El cambio a la condición = 1 es dado por la función muerteDracula().
            condicion = muerteDracula();
        }

        //Si el jugador queda encerrado por sus propios movimientos, el apartado de vidas es cambiado por un número que indique esto.
        if(mochila[4] == 33){

            saltarMucho();
            saltarMucho();
            imprimirTablero(tablero);
            printf("\n");
            printf("\n¡Te has quedado encerrado!\n¿Como quieres liberar BROWNSTONE si no puedes llegar al final de la mina?\n¡INÚTIL!\nFracasaste tu misión.\nPerdiste el juego.\n");
            presionarEnter();
            //Se cambia la condición necesaria.
            condicion = 1;
        }
    }

    //Una vez terminado el juego, se libera la memoria donde el tablero ha sido guardado.
    liberarTablero(tablero);

    return 0;
}





