#include "./game.h"

// crea el mazo de cartas (unicamente al inicio del juego)
void mazoCartas(Carta cartas[40])
{
    // inicializo las cartas
    for(int g = 0; g < CANTIDAD_CARTAS; g++)
    {
        cartas[g]->numero = 0;
        cartas[g]->palo = 'p';
        cartas[g]->puntos = 0.0;
        cartas[g]->inGame = false;
        cartas[g]->inMazo = false;
    }
    int count = 0;
    // asigno los valores a cada una
    for (int j = 0; j < 4; j++)
    {
        for (int i = 1; i < 11; i++)
        {
            switch (j)
            {
            case 0:
                if (i < 8)
                {
                    cartas[count]->palo = 'o';
                    cartas[count]->numero = i;
                    cartas[count]->puntos = (float) i;
                }
                else
                {
                    cartas[count]->palo = 'o';
                    cartas[count]->numero = i + 2;
                    cartas[count]->puntos = 0.5;
                }
                break;
            case 1:
                if (i < 8)
                {
                    cartas[count]->palo = 'c';
                    cartas[count]->numero = i;
                    cartas[count]->puntos = (float) i;
                }
                else
                {
                    cartas[count]->palo = 'c';
                    cartas[count]->numero = i + 2;
                    cartas[count]->puntos = 0.5;
                }
                break;
            case 2:
                if (i < 8)
                {
                    cartas[count]->palo = 'e';
                    cartas[count]->numero = i;
                    cartas[count]->puntos = (float) i;
                }
                else
                {
                    cartas[count]->palo = 'e';
                    cartas[count]->numero = i;
                    cartas[count]->puntos = 0.5;
                }
                break;
            case 3:
                if (i < 8)
                {
                    cartas[count]->palo = 'b';
                    cartas[count]->numero = i + 2;
                    cartas[count]->puntos = (float) i;
                }
                else
                {
                    cartas[count]->palo = 'b';
                    cartas[count]->numero = i + 2;
                    cartas[count]->puntos = 0.5;
                }
                break;
            }
            count++;
        }
    }
}

// ingresa en el arreglo de mazo de juego los objetos de cartas en una posicion al azar
void mezclarCartas(Carta cartas[40], Carta mazoJuego[40])
{
    for (int j = 0; j < CANTIDAD_CARTAS; j++)
    {
        cartas[j]->inMazo = false;
        cartas[j]->inGame = false;
    }
    for(int i = 0; i < CANTIDAD_CARTAS; i++)
    {
        //printf("Carta: %d de %c: %f\n", cartas[i]->numero, cartas[i]->palo, cartas[i]->puntos);
        int random;
        do
        {
            random = rand() % 40;
        }
        while (cartas[random]->inMazo);
        mazoJuego[i]->inGame = cartas[random]->inGame;
        mazoJuego[i]->numero = cartas[random]->numero;
        mazoJuego[i]->palo = cartas[random]->palo;
        mazoJuego[i]->puntos = cartas[random]->puntos;

        //printf("Carta: %d de %c: %f\n", mazoJuego[i]->numero, mazoJuego[i]->palo, mazoJuego[i]->puntos);
        cartas[random]->inMazo = true;
    }
}

// inicia los valores de cada jugador para el juego
void iniciarJuego(Jugador jugadores[6], int cantidadJugadores)
{
    for(int i = 0; i < cantidadJugadores; i++)
    {
        if (i != (cantidadJugadores - 1))
        {
            printf("Ingrese el nombre del jugador %d:\n", i + 1);
            scanf("%s", jugadores[i]->nombre);
            jugadores[i]->dinero = 5000.00;
            jugadores[i]->planta = false;
            jugadores[i]->puntos = 0.00;
            jugadores[i]->esBanca = 0;
            jugadores[i]->continuaJugando = true;
            printf("*********************************\n");
            printf("Jugador: %s\n", jugadores[i]->nombre);
            printf("Dinero: %f\n", jugadores[i]->dinero);
            printf("Puntos: %f\n", jugadores[i]->puntos);
            printf("*********************************\n");
        }
        else
        {
            strcpy(jugadores[i]->nombre, "BANCA");
            jugadores[i]->dinero = 100000.00;
            jugadores[i]->puntos = 0.00;
            jugadores[i]->esBanca = 1;
            printf("*********************************\n");
            printf("Jugador: %s\n", jugadores[i]->nombre);
            printf("Dinero: %f\n", jugadores[i]->dinero);
            printf("Puntos: %f\n", jugadores[i]->puntos);
            printf("*********************************\n");
        }
    }
}

// inicia la ronda
void iniciarRonda(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores)
{
    apuestaJugador(mazoJuego, jugadores, cantidadJugadores);
    for(int i = 0; i < cantidadJugadores; i++)
    {
        // iteracion para inicializar en valores nulos las cartas
        // de cada jugador por ronda iniciada
        jugadores[i]->cantidadCartas = 0;
        jugadores[i]->mismoPalo = false;
        jugadores[i]->puntos = 0;
        int pos = 0;
        int random;
        do
        {
            random = rand() % 40;
        }
        while (mazoJuego[random]->inGame);
        jugadores[i]->puntos += mazoJuego[random]->puntos;
        //strcpy(jugadores[i]->palo, mazoJuego[random]->palo);
        jugadores[i]->cantidadCartas = jugadores[i]->cantidadCartas + 1;
        pos++;
        printf("Salio el %d de %c\n", mazoJuego[random]->numero, mazoJuego[random]->palo);
        mazoJuego[random]->inGame = true;
        if (i != (cantidadJugadores-1))
        {
            sePlanta(jugadores[i], mazoJuego, pos);
            if (jugadores[i]->puntos == 0)
            {
                // jugadores[cantidadJugadores-1]->dinero += jugadores[i]->apuesta;
                printf("El dinero de %s se entregó a la banca.\n", jugadores[i]->nombre);
            }
        }
        else
        {
            printf("BANCA: \n");
            printf("DINERO: %f\n", jugadores[i]->dinero);
            printf("PUNTOS: %f\n", jugadores[i]->puntos);
            pideCarta(jugadores[i], mazoJuego, pos);
        }
    }
}

// pregunta al jugador si se planta o no
void sePlanta(Jugador jugador, Carta mazoJuego[40], int pos)
{
    int b;
    printf("%s tiene: %f puntos.\n", jugador->nombre, jugador->puntos);
    do
    {
        printf("%s Se planta? (0 = NO, 1 = SI)\n", jugador->nombre);
        scanf("%d", &b);
    }
    while (0 != b && b != 1);
    jugador->planta = b;
    if (jugador->planta == 1)
    {
        printf("El jugador %s se planta.\n", jugador->nombre);
    }
    else
    {
        printf("El jugador %s no se planta.\n", jugador->nombre);
        pideCarta(jugador, mazoJuego, pos);
    }
}

// apuesta de cada jugador menos de la banca
void apuestaJugador(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores)
{
    for (int i = 0; i < cantidadJugadores - 1; i++)
    {
        if (jugadores[i]->continuaJugando)
        {
            do
            {
                printf("%s Ingrese apuesta (entre 100 y 1500): ", jugadores[i]->nombre);
                scanf("%f", &jugadores[i]->apuesta);
            }
            while (jugadores[i]->apuesta < 100 || jugadores[i]->apuesta > 1500 || jugadores[i]->dinero < jugadores[i]->apuesta);
            jugadores[i]->dinero -= jugadores[i]->apuesta;
            printf("El jugador %s apuesta %f.\n", jugadores[i]->nombre, jugadores[i]->apuesta);
            printf("Dinero restante: %f\n", jugadores[i]->dinero);
        }
    }
}

// pide carta porque no se plantó
void pideCarta(Jugador jugador, Carta mazoJuego[40], int pos)
{
    int random;
    do
    {
        random = rand() % 40;
    }
    while (mazoJuego[random]->inGame);
    jugador->puntos += mazoJuego[random]->puntos;
    //strcpy(jugador->palo, mazoJuego[random]->palo);
    jugador->cantidadCartas++;
    pos++;
    printf("Salio el %d de %c\n", mazoJuego[random]->numero, mazoJuego[random]->palo);
    printf("%s TIENE PUNTOS: %f\n", jugador->nombre, jugador->puntos);
    mazoJuego[random]->inGame = true;
    if (jugador->esBanca && jugador->puntos < 6)
    {
        pideCarta(jugador, mazoJuego, pos);
    }
    else
    {
        if (jugador->esBanca && jugador->puntos <= 7.5)
        {
            jugador->planta = true;
        }
        else if (jugador->puntos <= 7.5)
        {
            // de nuevo preguntamos si se planta
            // unicamente en caso de que tenga 7.5 o menos
            sePlanta(jugador, mazoJuego, pos);
        }
        else
        {
            jugador->puntos = 0;
            jugador->planta = true;
            printf("El jugador %s se paso de 7.5.\n", jugador->nombre);
        }
    }
}

// reparte las ganancias entre los jugadores y
// quita a la banca el dinero para cada uno
void repartirGanancias(Jugador jugadores[6], int cantidadJugadores)
{
    for (int i = 0; i < cantidadJugadores; i++)
    {
        char palo = ' ';
        int cantCartas = 0;
        //calcularBonus(jugadores[i], palo);
        if (!jugadores[i]->esBanca)
        {
            if (jugadores[i]->puntos == 7.5 && jugadores[i]->puntos > jugadores[cantidadJugadores-1]->puntos && !(jugadores[i]->mismoPalo) && jugadores[i]->cantidadCartas == 2)
            {
                // Gana con: 7 + figura, el premio es 50% de lo apostado
                jugadores[i]->dinero += jugadores[i]->apuesta * 1.5;
                jugadores[cantidadJugadores-1]->dinero -= jugadores[i]->apuesta * 1.5 - jugadores[i]->apuesta;
                printf("%s HA GANADO: %f\n", jugadores[i]->nombre, jugadores[i]->apuesta * 1.5);
            }
            else if (jugadores[i]->puntos == 7.5 && jugadores[i]->puntos > jugadores[cantidadJugadores-1]->puntos && jugadores[i]->mismoPalo && jugadores[i]->cantidadCartas == 2)
            {
                // Gana con: 7 + figura, del mismo palo, premio 75% de lo apostado
                jugadores[i]->dinero += jugadores[i]->apuesta * 1.75;
                jugadores[cantidadJugadores-1]->dinero -= jugadores[i]->apuesta * 1.75 - jugadores[i]->apuesta;
                printf("%s HA GANADO: %f\n", jugadores[i]->nombre, jugadores[i]->apuesta * 1.75);
            }
            else if (jugadores[i]->puntos == 7.5 && jugadores[i]->puntos > jugadores[cantidadJugadores-1]->puntos && jugadores[i]->mismoPalo /*&& strcmp(palo, 'o')*/)
            {
                jugadores[i]->dinero += jugadores[i]->apuesta * 2;
                jugadores[cantidadJugadores-1]->dinero -= jugadores[i]->apuesta * 2 - jugadores[i]->apuesta;
                printf("%s HA GANADO: %f\n", jugadores[i]->nombre, jugadores[i]->apuesta * 2);
            }
            else if (jugadores[i]->puntos > jugadores[cantidadJugadores-1]->puntos && jugadores[i]->cantidadCartas >= 3)
            {
                jugadores[i]->dinero += jugadores[i]->apuesta * 1.25;
                jugadores[cantidadJugadores-1]->dinero -= jugadores[i]->apuesta * 1.25 - jugadores[i]->apuesta;
                printf("%s HA GANADO: %f\n", jugadores[i]->nombre, jugadores[i]->apuesta * 1.25);
            }
            else
            {
                jugadores[cantidadJugadores-1]->dinero += jugadores[i]->apuesta;
                podriaSeguirJugando(jugadores[i]);
            }
        }
    }
}

void calcularBonus(Jugador jugador, char palo)
{
    for (int i = 1; i < 6; i++)
    {
        if (jugador->palo == palo)
        {
            jugador->mismoPalo = true;
            //strcpy(palo, jugador->palo);
        }
        else
        {
            jugador->mismoPalo = false;
            break;
        }
    }
}

void podriaSeguirJugando(Jugador jugador)
{
    jugador->continuaJugando = jugador->dinero > 0;
}

void quienGanoMas(Jugador jugadores[6], int cantidadJugadores)
{
    Jugador ganador;
    float dinero = 0;
    float gananciaJugador;
    float gananciasEnConjunto = 0;
    float perdidasEnConjunto = 0;
    for (int i = 0; i < cantidadJugadores; i++)
    {
        if (jugadores[i]->dinero != 0)
        {
            if (jugadores[i]->esBanca)
            {
                gananciaJugador = jugadores[i]->dinero - 100000.0;
                if (gananciaJugador > 0) {
                    gananciasEnConjunto += gananciaJugador;
                } else {
                    perdidasEnConjunto += gananciaJugador * (-1);
                }
                if (gananciaJugador > dinero)
                {
                    dinero = gananciaJugador;
                    strcpy(ganador->nombre, jugadores[i]->nombre);
                    ganador->dinero = jugadores[i]->dinero;
                }
            }
            else
            {
                gananciaJugador = jugadores[i]->dinero - 5000.0;
                if (gananciaJugador > 0) {
                    gananciasEnConjunto += gananciaJugador;
                } else {
                    perdidasEnConjunto += gananciaJugador * (-1);
                }
                if (gananciaJugador > dinero)
                {
                    dinero = gananciaJugador;
                    strcpy(ganador->nombre, jugadores[i]->nombre);
                    ganador->dinero = jugadores[i]->dinero;
                }
            }
        }
    }
    printf("El jugador que obtuvo mas ganancias fue: %s. Gano: %f\n", ganador->nombre, dinero);
    if (gananciasEnConjunto > perdidasEnConjunto) {
        printf("En conjunto se obtuvieron mas ganancias que perdidas.\n");
    } else {
        printf("En conjunto se obtuvieron mas perdidas que ganancias.\n");
    }

}
