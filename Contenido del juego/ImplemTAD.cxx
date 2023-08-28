#include "TADs.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <array>
#include <algorithm>

bool tieneTerriDisp(const std::vector<std::string> &continente);

Mision::Mision(std::string colorJ) : nomTerris()
{
  std::srand(std::time(0));
  std::vector<int> randTerri;
  std::string confirmacion;
  std::string terris[42] = {"Alaska", "Alberta", "Ameica Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales",
                            "Argentina", "Brasil", "Peru", "Venezuela",
                            "Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk",
                            "Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa del Norte", "Africa del Sur",
                            "Gran Bretana", "Islandia", "Europa del Norte", "Escandinavia", "Europa del Sur", "Ucrania", "Europa Occidental",
                            "Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

  completada = false;
  cantTerri = std::rand() % 6 + 10; // de 10 a 15
  uniEjer = std::rand() % 7 + 3;    // de 3 a 9

  for (int i = 0; i < 42; i++)
  {
    randTerri.push_back(i);
  }
  std::random_shuffle(randTerri.begin(), randTerri.end());
  for (int i = 0; i < cantTerri; ++i)
  {
    int cual = randTerri[i];
    nomTerris.push_back(terris[cual]);
  }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Al estar en modo de juego por Misiones secretas," << std::endl;
  std::cout << "se tiene que definir su mision para poder ganar el juego." << std::endl;
  std::cout << std::endl;
  std::cout << "Para esto, de forma aleatoria se definen cuantos territorios y cuales debe conquistar para ganar" << std::endl;
  std::cout << "- El jugador (" + colorJ + ") tiene que conquistar: ";
  std::cout << cantTerri;
  std::cout << " territorios." << std::endl;
  std::cout << "- Para ser mas especificos: " << std::endl;
  for (std::vector<std::string>::iterator miIterador = nomTerris.begin(); miIterador != nomTerris.end(); miIterador++)
  {
    std::cout << "  - ";
    std::cout << *miIterador << " " << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Adicionalmente, hay que establecer cuantas unidades de ejercito, por cada uno de los contientes anteriores," << std::endl;
  std::cout << "debe tener para ganar el juego. esto tambien se define de forma aleatoria." << std::endl;
  std::cout << "Unidades de ejercito para ganar: ";
  std::cout << uniEjer << std::endl;
  std::cout << std::endl;
  std::cout << "Para continuar escriba cualquier cosa: ";
  std::cin >> confirmacion;
  std::cout << std::endl;
  std::cout << std::endl;
}

Jugador::Jugador(int _cantJugadores, char _modoPartida, std::string _color) : ejercito(), tarjetas()
{
  color = _color;
  modoPartida = _modoPartida;

  if (_cantJugadores == 3)
  {
    ejercito[0] = 35;
  }
  else if (_cantJugadores == 4)
  {
    ejercito[0] = 30;
  }
  else if (_cantJugadores == 5)
  {
    ejercito[0] = 25;
  }
  else if (_cantJugadores == 6)
  {
    ejercito[0] = 20;
  }

  modoPartida = _modoPartida;
  if (modoPartida == 'm')
  {
    mision = new Mision(color);
  }
}

void Jugador::miMision(std::string _color) // Constructor de Territorio
{
  int cuantosTerri = mision->cantTerri;
  int cantasUniEjer = mision->uniEjer;
  std::vector<std::string> cualesTerri = mision->nomTerris;

  std::cout << "La mision del jugador (" + _color + ") es:" << std::endl;
  std::cout << "- Conquistar: " + cuantosTerri;
  std::cout << " territorios." << std::endl;
  std::cout << "- Los territorios que debe conquistar son:" << std::endl;
  for (std::vector<std::string>::iterator miIterador = cualesTerri.begin(); miIterador != cualesTerri.end(); miIterador++)
  {
    std::cout << "  - ";
    std::cout << *miIterador << " " << std::endl;
  }
  std::cout << "- Cada uno de los anteriores territorios debe tener: " + cantasUniEjer;
  std::cout << " unidades de ejercito." << std::endl;
}
//

Territorio::Territorio(std::string _nombreTerri) // Constructor de Territorio
{
  nombreTerri = _nombreTerri;
}

Continente::Continente(std::string _nombreCont) : nombreCont(_nombreCont), territorios() // Constructor de Continente
{
  std::string terrisANOR[12] = {"Alaska", "Alberta", "Ameica Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales"};
  std::string terrisASUR[4] = {"Argentina", "Brasil", "Peru", "Venezuela"};
  std::string terrisASIA[12] = {"Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
  std::string terrisAFRC[6] = {"Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa del Norte", "Africa del Sur"};
  std::string terrisEROP[7] = {"Gran Bretana", "Islandia", "Europa del Norte", "Escandinavia", "Europa del Sur", "Ucrania", "Europa Occidental"};
  std::string terrisASTR[4] = {"Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

  // nombreCont = _nombreCont;

  if (nombreCont == "America Del Norte")
  {
    for (int i = 0; i < 9; i++)
    {
      territorios.push_back(new Territorio(terrisANOR[i]));
    }
  }
  else if (nombreCont == "America Del Sur")
  {
    for (int i = 0; i < 4; i++)
    {
      Territorio actTerri(terrisASUR[i]);

      territorios.push_back(new Territorio(terrisASUR[i]));
    }
  }
  else if (nombreCont == "Asia")
  {
    for (int i = 0; i < 12; i++)
    {
      territorios.push_back(new Territorio(terrisASIA[i]));
    }
  }
  else if (nombreCont == "Africa")
  {
    for (int i = 0; i < 6; i++)
    {

      territorios.push_back(new Territorio(terrisAFRC[i]));
    }
  }
  else if (nombreCont == "Europa")
  {
    for (int i = 0; i < 7; i++)
    {

      territorios.push_back(new Territorio(terrisEROP[i]));
    }
  }
  else if (nombreCont == "Australia")
  {
    for (int i = 0; i < 4; i++)
    {

      territorios.push_back(new Territorio(terrisASTR[i]));
    }
  }
}

Territorio *Continente::buscaT(std::string nombTerri)
{
  for (Territorio *terriObj : territorios)
  {
    if (terriObj && terriObj->nombreTerri == nombTerri)
    {
      return terriObj; // Devuelve el puntero al territorio con el nombre especificado
    }
  }
  return nullptr; // Si no se encuentra el territorio
}

Partida::Partida(char _modoJuego, int cantJugadores) : jugadores(), continentes(), modoJuego(_modoJuego) // Constructor de partida
{
  std::string coloresJ[6] = {"Rojo", "Azul", "Amarillo", "Naranja", "Verde", "Rasado"};

  idPartida = rand() % 10000;

  empezada = true;
  terminada = false;

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
  std::queue<Jugador *> jugadoresTemp = jugadores; // Copia la cola original
  while (!jugadoresTemp.empty())
  {
    Jugador *jugadorObj = jugadoresTemp.front();
    if (jugadorObj->color == color)
    {
      return jugadorObj; // Devuelve el puntero al jugador con el color especificado
    }
    jugadoresTemp.pop(); // Desencola el jugador actual
  }

  return nullptr; // Si no encuentra el jugador
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
  return nullptr; // Si no encuentra el continente
}

void Partida::asignaTerri(Continente *elConti, std::string nomTerri, Jugador *elPlayer)
{
  //Territorio *elTerri = elConti->buscaT(nomTerri);
  Territorio *elTerri = new Territorio(nomTerri);
  elTerri->duenoAct = elPlayer->color;

  elTerri->uniInfanteria = 1;
  elPlayer->ejercito[0] = elPlayer->ejercito[0] - 1;
}

SistemaApoyo::SistemaApoyo()
{
  partidas = std::list<Partida *>();
}

// POSIBLE CAMBIO devolver el puntero de la cartida recien creada
void SistemaApoyo::crearPartida()
{

  int cantJugadores;
  char modoJuego;

  do
  {
    std::cout << "Cuantas personas van a jugar? (min 3 - max 6): ";
    std::cin >> cantJugadores;
  } while (cantJugadores < 3 || cantJugadores > 6);

  std::cout << "Risk, tiene dos formas de jugar: " << std::endl;
  std::cout << "Para el modo por Misiones, ingrese la tecla 'M' " << std::endl;
  std::cout << "Para el modo Normal, ingrese la tecla 'N' " << std::endl;

  do
  {
    std::cout << "Ingrese un modo de juego valido: ";
    std::cin >> modoJuego;
  } while (modoJuego != 'm' && modoJuego != 'n');

  partidas.push_back(new Partida(modoJuego, cantJugadores));

  std::cout << "El juego ya ha sido inicializado" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

void SistemaApoyo::escojerTerris()
{
  Partida *partidaAct = partidas.back();

  std::vector<std::string> AmericaNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Orientales"};
  std::vector<std::string> AmericaSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
  std::vector<std::string> Europa = {"Gran Bretaña", "Islandia", "Europa del Norte", "Escandinavia", "Europa del Sur", "Ucrania", "Europa Occidental"};
  std::vector<std::string> Africa = {"Congo", "África Oriental", "Egipto", "Madagascar", "África del Norte", "África del Sur"};
  std::vector<std::string> Asia = {"Afghanistán", "China", "India", "Irkutsk", "Japón", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
  std::vector<std::string> Australia = {"Australia", "Indonesia", "Nueva Guinea", "Australia Occidental"};

  std::string salvaNomTerri;

  int conta_terr = 0;
  int cantJ = partidaAct->jugadores.size();
  int eleccion1;
  int eleccion2;
  std::string colJugadores[6] = {"Rojo", "Azul", "Amarillo", "Naranja", "Verde", "Rasado"};
  std::string auxContis[6] = {"America Del Norte", "America Del Sur", "Asia", "Africa", "Europa", "Australia"};

  std::string aux[cantJ];

  for (int i = 0; i < cantJ; i++)
  {
    aux[i] = colJugadores[i];
  }

  while (conta_terr < 42)
  {
    for (int i = 0; i < cantJ; i++)
    {
      std::cout << "Jugador (" + aux[i] + ") es su turno para:" << std::endl;
      std::cout << "Elijir uno de los siguientes continetes:" << std::endl;
      std::cout << "1. America del Norte" << std::endl;
      std::cout << "2. América del Sur" << std::endl;
      std::cout << "3. Europa" << std::endl;
      std::cout << "4. Africa" << std::endl;
      std::cout << "5. Asia" << std::endl;
      std::cout << "6. Australia" << std::endl;
      std::cout << "Ingrese el número del continente seleccionado: ";
      std::cin >> eleccion1;

      switch (eleccion1)
      {
      case 1:
      {
        if (!tieneTerriDisp(AmericaNorte))
        {
          std::cout << "No hay territorios disponibles en América del Norte." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en América del Norte:" << std::endl;
        for (size_t j = 0; j < AmericaNorte.size(); j++)
        {
          std::cout << j + 1 << ". " << AmericaNorte[j] << std::endl;
        }

        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;

        if (eleccion2 >= 1 && eleccion2 <= AmericaNorte.size())
        {
          salvaNomTerri = AmericaNorte[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << AmericaNorte[eleccion2 - 1] << std::endl;
          AmericaNorte.erase(AmericaNorte.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      case 2:
      {
        if (!tieneTerriDisp(AmericaSur))
        {
          std::cout << "No hay territorios disponibles en América del Sur." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en América del Sur:" << std::endl;
        for (size_t j = 0; j < AmericaSur.size(); j++)
        {
          std::cout << j + 1 << ". " << AmericaSur[j] << std::endl;
        }

        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;

        if (eleccion2 >= 1 && eleccion2 <= AmericaSur.size())
        {
          salvaNomTerri = AmericaSur[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << AmericaSur[eleccion2 - 1] << std::endl;
          AmericaSur.erase(AmericaSur.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      case 3:
      {
        if (!tieneTerriDisp(Europa))
        {
          std::cout << "No hay territorios disponibles en Europa." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en Europa:" << std::endl;
        for (size_t j = 0; j < Europa.size(); j++)
        {
          std::cout << j + 1 << ". " << Europa[j] << std::endl;
        }

        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;
        if (eleccion2 >= 1 && eleccion2 <= Europa.size())
        {
          salvaNomTerri = Europa[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << Europa[eleccion2 - 1] << std::endl;
          Europa.erase(Europa.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      case 4:
      {
        if (!tieneTerriDisp(Africa))
        {
          std::cout << "No hay territorios disponibles en Africa." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en Africa:" << std::endl;
        for (size_t j = 0; j < Africa.size(); j++)
        {
          std::cout << j + 1 << ". " << Africa[j] << std::endl;
        }
        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;

        if (eleccion2 >= 1 && eleccion2 <= Africa.size())
        {
          salvaNomTerri = Africa[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << Africa[eleccion2 - 1] << std::endl;
          Africa.erase(Africa.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      case 5:
      {
        if (!tieneTerriDisp(Asia))
        {
          std::cout << "No hay territorios disponibles en Asia." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en Asia:" << std::endl;
        for (size_t j = 0; j < Asia.size(); j++)
        {
          std::cout << j + 1 << ". " << Asia[j] << std::endl;
        }

        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;
        if (eleccion2 >= 1 && eleccion2 <= Asia.size())
        {
          salvaNomTerri = Asia[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << Asia[eleccion2 - 1] << std::endl;
          Asia.erase(Asia.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      case 6:
      {
        if (!tieneTerriDisp(Australia))
        {
          std::cout << "No hay territorios disponibles en Australia." << std::endl;
          break;
        }

        std::cout << "Territorios disponibles en Australia:" << std::endl;
        for (size_t j = 0; j < Australia.size(); j++)
        {
          std::cout << j + 1 << ". " << Australia[j] << std::endl;
        }

        std::cout << "Ingrese el número del territorio seleccionado: ";
        std::cin >> eleccion2;
        if (eleccion2 >= 1 && eleccion2 <= Australia.size())
        {
          salvaNomTerri = Australia[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);
          Continente *conti = partidaAct->buscaC(auxContis[0]);
          partidaAct->asignaTerri(conti, salvaNomTerri, player);

          std::cout << "Territorio elegido: " << Australia[eleccion2 - 1] << std::endl;
          Australia.erase(Australia.begin() + eleccion2 - 1);
          conta_terr++;
        }
        else
        {
          std::cout << "Número de territorio inválido." << std::endl;
        }

        break;
      }

      default:
      {
        std::cout << "Continente no válido. Intente nuevamente." << std::endl;
        break;
      }
      }
    }
  }
  std::cout << "Se ha inizializado la partida correctamente" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

bool tieneTerriDisp(const std::vector<std::string> &continente)
{
  return !continente.empty();
}
