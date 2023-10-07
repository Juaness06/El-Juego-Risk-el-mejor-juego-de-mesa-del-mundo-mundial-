#ifndef __PARTIDA_H__
#define __PARTIDA_H__

#include <queue>
#include "Jugador.h"
#include "Continente.h"

class Partida
{
  public:
    std::string estado;
    std::queue<Jugador*> jugadores;
    Continente* continentes[6];
    char modoJuego;
    Jugador* jugadorActual;

  public:
    Partida(char, int);
    Jugador* buscaJ (std::string);
    Continente* buscaC (std::string);
    Territorio *buscaT(std::string nombreT);
    void fortificar();
    void atacar();
};

#include "Partida.cxx"

#endif