#ifndef __MISION__H__
#define __MISION__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Mision
{
  public:
    bool completada;
    int cantTerri;
    int uniEjer;
    std::vector<std::string> nomTerris;

  public:
    Mision(std::string);

};
#endif

#ifndef __TARJETA__H__
#define __TARJETA__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Tarjeta
{
  public:
    std::string tipoTar;
    std::string tipoEjer;
    std::string terriTar;

  public:


};
#endif

#ifndef __JUGADOR__H__
#define __JUGADOR__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Jugador
{
  public:
    std::string color;
    char modoPartida;
    int ejercito[3];
    Mision* mision;
    std::vector<Tarjeta> tarjetas;

  public:
    Jugador(int,char,std::string);

};
#endif

#ifndef __TERRITORIO__H__
#define __TERRITORIO__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Territorio
{
  public:
    std::string nombreTerri;
    std::vector<std::string> terriAdy;
    std::string duenoAct;
    int uniInfanteria;

  public:
    Territorio(std::string);
      
};
#endif

#ifndef __CONTINENTE__H__
#define __CONTINENTE__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Continente
{
    public:
        std::string nombreCont;
        std::vector<Territorio>territorios;
    public:
        Continente(std::string);
        Territorio* buscaT (std::string);
};
#endif

#ifndef __PARTIDA__H__
#define __PARTIDA__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class Partida
{
  public:
    bool empezada;
    int idPartida;
    std::queue<Jugador> jugadores;
    Continente* continentes[6];
    char modoJuego;
    Jugador* jugadorActual;

  public:
    Partida(char, int);
    Jugador* buscaJ (std::string);
    Continente* buscaC (std::string);
    void asignaTerri(Continente*, std::string, Jugador*);
    
      
};
#endif


#ifndef __SISTEMAAPOYORISK__H__
#define __SISTEMAAPOYORISK__H__

#include <list>
#include <queue>
#include <string>
#include <vector>
#include <array>

class SistemaApoyo
{
    public:
      std::list<Partida>partidas;
    public:
      SistemaApoyo();
      void crearPartida();
      void escojerTerris();

};
#endif



