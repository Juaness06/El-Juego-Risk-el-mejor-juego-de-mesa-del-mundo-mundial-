#include "Partida.h"

Partida::Partida(char _modoJuego, int cantJugadores) : jugadores(), continentes(), modoJuego(_modoJuego) // Constructor de partida
{
  std::string coloresJ[6] = {"rojo", "azul", "amarillo", "naranja", "verde", "rosado"};

  estado = "En Curso"; // Posibles estados: "En Curso", "Terminada"

  for (int i = 0; i < cantJugadores; i++)
  {
    jugadores.push(new Jugador(cantJugadores, modoJuego, coloresJ[i]));
  }

  continentes[0] = new Continente("America Del Norte");
  continentes[1] = new Continente("America Del Sur");
  continentes[2] = new Continente("Asia");
  continentes[3] = new Continente("Africa");
  continentes[4] = new Continente("Europa");
  continentes[5] = new Continente("Australia");

  if (!jugadores.empty())
  {
    jugadorActual = jugadores.front(); // Inicializa el puntero al primer jugador
  }
}

Jugador *Partida::buscaJ(const std::string color)
{
  std::queue<Jugador*> jugadoresTemp = jugadores; // Copia la cola original
  while (!jugadoresTemp.empty())
  {
    Jugador* jugadorObj = jugadoresTemp.front();
    if (jugadorObj->color == color)
    {
      return jugadorObj; // Devuelve el puntero al jugador con el color especificado
    }
    jugadoresTemp.pop(); // Desencola el jugador actual
  }

  return NULL; // Si no encuentra el jugador
}

Continente *Partida::buscaC(std::string nombreC)
{
  // Uso de iteradores. en cada iteracion, el puntero contiObj señalara al siguiente puntero a continentes almacenados en "continentes"
  for (Continente *contiObj : continentes)
  {
    if (contiObj && contiObj->nombreCont == nombreC)
    {
      return contiObj; // Devuelve el puntero al continente especificado
    }
  }
  return NULL; // Si no encuentra el continente
}

void Partida::asignaTerri(Continente *elConti, std::string nomTerri, Jugador *elPlayer)
{

  //


  Territorio *elTerri = new Territorio(nomTerri);
  elTerri->duenoAct = elPlayer;  

  elTerri->uniEjercito = 1;
  elPlayer->ejercito = elPlayer->ejercito - 1;
}