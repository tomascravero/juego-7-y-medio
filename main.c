#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "./game.c"

int main() {
    Carta cartas[40];
    Carta mazoJuego[40];
    Jugador jugadores[6];

    float apuestaMaxima = 0;
    char jugadorApuestaMaxima[10];
    int numeroRonda;
    int cantidadJugadores = 0;
    int cantidadRondas = 0;

    printf("COMIENZO DEL JUEGO 7 Y MEDIO\n");
    // en este punto ya tengo todos los objetos de cartqas en el arreglo
    mazoCartas(cartas);
    // ingresan las cartas en orden aleatorio en el mazo de juego
    //mezclarCartas(cartas, mazoJuego);

    do {
        printf("Ingrese la cantidad de jugadores (entre 1 y 5)\n");
        scanf("%d", &cantidadJugadores);
    } while (cantidadJugadores < 1 || cantidadJugadores > 5 || (isdigit(cantidadJugadores) == 1)); // hasta 5 porque contando la banca ya llegaria al max.

    do {
        printf("Ingrese la cantidad de rondas (entre 2 y 4)\n");
        scanf("%d", &cantidadRondas);
    } while (cantidadRondas < 2 || cantidadRondas > 4 || (isdigit(cantidadRondas) == 1));

    // la cantidad de jugadores +1 porque la banca tambien juega
    cantidadJugadores++;
    // inicializan los valores de los jugadores y la banca
    iniciarJuego(jugadores, cantidadJugadores);

    // en este punto del programa ya tengo los jugadores iniciador y el mazo de cartas para comenzar
    int contadorDeRondas = 0;
    for (int i = 0; i < cantidadRondas; i++) {
        // ingresan las cartas en orden aleatorio en el mazo de juego

        mezclarCartas(cartas, mazoJuego);
        printf("Inicia la RONDA %d\n", i+1);

        // contador para llevar la cuenta de las rondas y guardar el valor de la ronda donde mas se aposto
        contadorDeRondas++;
        iniciarRonda(mazoJuego, jugadores, cantidadJugadores);

        repartirGanancias(jugadores, cantidadJugadores);

        for (int j = 0; j < cantidadJugadores; j++) {
            printf("*********************************\n");
            printf("JUGADOR: %s\n", jugadores[j]->nombre);
            printf("DINERO: %f\n", jugadores[j]->dinero);
            printf("PUNTOS: %f\n", jugadores[j]->puntos);
            printf("APUESTA: %f\n", jugadores[j]->apuesta);
            printf("*********************************\n");
            if (jugadores[j]->apuesta > apuestaMaxima) {
                apuestaMaxima = jugadores[j]->apuesta;
                strcpy(jugadorApuestaMaxima, jugadores[j]->nombre);
                numeroRonda = i+1;
            }
        }
    }
    // determinar quien gano mas
    quienGanoMas(jugadores, cantidadJugadores);
    // print mayor apuesta, nombre y ronda
    printf("El jugador que mas aposto fue: %s, con: %f en la ronda: %d\n", jugadorApuestaMaxima, apuestaMaxima, numeroRonda);

    return 0;
}
