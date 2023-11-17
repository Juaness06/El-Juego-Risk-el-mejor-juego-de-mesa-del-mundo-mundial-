#ifndef __PARTIDA_H__
#define __PARTIDA_H__

#include <queue>
#include "Jugador.h"
#include "Continente.h"
#include "Territorio.h"
#include "Tablero.h"

class Partida
{
  public:
    std::string estado;
    std::queue<Jugador*> jugadores;
    Continente* continentes[6];
    char modoJuego;
    Jugador* jugadorActual;
    Tablero<std::string, int> tablero;

  public:
    Partida(char, int, Tablero<std::string, int>);
    Jugador* buscaJ (std::string);
    Continente* buscaC (std::string);
    Territorio *buscaT(std::string nombreT);
    void fortificar();
    void atacar();
    void gestorDados(Jugador* jugadorAtacante, Jugador* jugadorDefensor, Territorio* terriAtacoDesde, Territorio* terriAtaco);
    void guardarPartida(std::string);
    void guardarCompimido(std::string);
};

#include "Partida.cxx"

#endif