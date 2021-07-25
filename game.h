#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define CANTIDAD_CARTAS 40
#define MAX_JUGADORES 6
#define MIN_JUGADORES 1
#include <stdbool.h>

// estructura que representa al jugador
typedef struct
{
    char nombre[10];
    float puntos;
    float dinero;
    float apuesta;
    bool planta;
    bool esBanca;
    //Carta cartasPorRonda[6];
} Jugador[6];

// estructura que representa a cada carta
typedef struct
{
    char palo;
    float puntos;
    int numero;
    bool inGame;
    bool inMazo;
} Carta[40];

void mazoCartas(Carta cartas[40]);
void mezclarCartas(Carta cartas[40], Carta mazoJuego[40]);
void iniciarJuego(Jugador jugadores[6], int cantidadJugadores);
void iniciarRonda(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores);
void sePlanta(Jugador jugador, Carta mazoJuego[40]);
void apuestaJugador(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores);
void pideCarta(Jugador jugador, Carta mazoJuego[40]);
void repartirGanancias(Jugador jugadores[6], int cantidadJugadores);
void quienGanoMas(Jugador jugadores[6], int cantidadJugadores);

#endif // GAME_H_INCLUDED
