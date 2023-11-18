#ifndef __TERRITORIO_H__
#define __TERRITORIO_H__

#include <vector>
#include <string>
#include "Jugador.h"

class Territorio
{
  public:
    std::string nombreTerri;
    Jugador* duenoAct;
    int uniEjercito;

  public:
    Territorio(std::string);
};

#include "Territorio.cxx"

#endif

