#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define CANTIDAD_CARTAS 40
#define MAX_JUGADORES 6
#define MIN_JUGADORES 1
#include <stdbool.h>

// estructura que representa a cada carta
typedef struct
{
    char palo;
    float puntos;
    int numero;
    bool inGame;
    bool inMazo;
} Carta[40];
// estructura que representa al jugador

typedef struct
{
    char nombre[10];
    float puntos;
    float dinero;
    float apuesta;
    bool planta;
    bool esBanca;
    bool continuaJugando;
    int cantidadCartas;
    bool mismoPalo;
    char palo;
} Jugador[6];


void mazoCartas(Carta cartas[40]);
void mezclarCartas(Carta cartas[40], Carta mazoJuego[40]);
void iniciarJuego(Jugador jugadores[6], int cantidadJugadores);
void iniciarRonda(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores);
void sePlanta(Jugador jugador, Carta mazoJuego[40], int pos);
void apuestaJugador(Carta mazoJuego[40], Jugador jugadores[6], int cantidadJugadores);
void pideCarta(Jugador jugador, Carta mazoJuego[40], int pos);
void repartirGanancias(Jugador jugadores[6], int cantidadJugadores);
void quienGanoMas(Jugador jugadores[6], int cantidadJugadores);
void podriaSeguirJugando(Jugador jugador);
void calcularBonus(Jugador jugador, char palo);

#endif // GAME_H_INCLUDED
