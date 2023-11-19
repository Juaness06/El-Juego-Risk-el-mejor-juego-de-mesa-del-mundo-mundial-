#include "SistemaApoyo.h"
#include "Tablero.h"

#include <iostream>
#include <climits>

#define red "\033[31m"
#define blue "\033[34m"
#define yellow "\033[33m"
#define orange "\033[38;5;208m"
#define green "\033[32m"
#define magenta "\033[35m"
#define reset "\033[0m"

Tablero<std::string, int> tablero;

struct infoTerri
{
  std::string continente;
  std::string nombre;
  int tropas;
};

struct infoPlayer
{
  std::string nombre;
  std::vector<infoTerri> territorios;
};

bool tieneTerriDisp(const std::vector<std::string> &continente);

SistemaApoyo::SistemaApoyo()
{
  partida = NULL;
}

void SistemaApoyo::crearPartida()
{

  int cantJugadores;
  char modoJuego;
  inicializarTablero();

  do
  {
    std::cout << std::endl;
    std::cout << "Cuantas personas van a jugar? (min 3 - max 6): ";
    std::cin >> cantJugadores;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (cantJugadores < 3 || cantJugadores > 6);

  std::cout << std::endl;
  std::cout << "Risk, tiene dos formas de jugar: " << std::endl;
  std::cout << "Para el modo por Misiones, ingrese la tecla 'm' " << std::endl;
  std::cout << "Para el modo Normal, ingrese la tecla 'n' " << std::endl;

  do
  {
    std::cout << "Ingrese un modo de juego valido: ";
    std::cin >> modoJuego;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (modoJuego != 'm' && modoJuego != 'n');

  this->partida = new Partida(modoJuego, cantJugadores, tablero);

  std::cout << std::endl;

  std::cout << "Presione Enter para continuar..." << std::endl;
  // std::cin.ignore();
  std::cin.get();
  system("clear");
}

void SistemaApoyo::reanudarPartida(std::string nombreArchivo)
{

  std::vector<infoPlayer> datos_jugadores;
  std::ifstream archivo(nombreArchivo);

  if (!archivo.is_open())
  {
    std::cout << "No se pudo abrir el archivo" << std::endl;
    return;
  }

  std::string linea;
  infoPlayer player;

  while (std::getline(archivo, linea))
  {
    std::istringstream iss(linea);

    if (linea.find("Jugador:") != std::string::npos)
    {
      // Si encuentras un nuevo jugador, agrega el jugador actual a datos_jugadores
      if (!player.nombre.empty())
      {
        datos_jugadores.push_back(player);
        player.territorios.clear();
      }
      player.nombre = linea.substr(linea.find(":") + 2);
    }
    else if (linea.find("Contienente:") != std::string::npos)
    {
      infoTerri territorio;
      territorio.continente = linea.substr(linea.find(":") + 2);
      std::getline(archivo, linea);
      territorio.nombre = linea.substr(linea.find(":") + 1);
      std::getline(archivo, linea);
      territorio.tropas = std::stoi(linea.substr(linea.find(":") + 1));

      player.territorios.push_back(territorio);
    }
  }

  // Se Agregar el último jugador a datos_jugadores
  if (!player.nombre.empty())
  {
    datos_jugadores.push_back(player);
  }

  archivo.close();



  int cantJugadores = datos_jugadores.size();
  char modoJuego = 'n';
  inicializarTablero();

  this->partida = new Partida(modoJuego, cantJugadores, tablero);

  // recorrer el vector datos_jugadores y asignar los territorios a los jugadores en la partida segun el archivo
  for (infoPlayer player : datos_jugadores)
  {
    for (infoTerri terri : player.territorios)
    {
      Jugador *jugador = partida->buscaJ(player.nombre);
      for (Continente *continente : partida->continentes)
      {
        if (continente->nombreCont == terri.continente)
        {
          for (Territorio *territorio : continente->territorios)
          {
            if (territorio->nombreTerri == terri.nombre)
            {
              territorio->duenoAct = jugador;
              territorio->uniEjercito = terri.tropas;
              jugador->ejercito = jugador->ejercito - terri.tropas;
            }
          }
        }
      }
    }
  }

  // llamado a la funcion que actualiza el grafo a partir de los datos actuales de la partida
  actTableroInfoActual();
  
}

void SistemaApoyo::escojerTerris(Partida *partidaAct)
{
  // partidas
  std::vector<std::string> AmericaNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales"};
  std::vector<std::string> AmericaSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
  std::vector<std::string> Europa = {"Gran Bretana", "Islandia", "Europa Del Norte", "Escandinavia", "Europa Del Sur", "Ucrania", "Europa Occidental"};
  std::vector<std::string> Africa = {"Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa Del Norte", "Africa Del Sur"};
  std::vector<std::string> Asia = {"Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
  std::vector<std::string> Australia = {"Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

  std::string salvaNomTerri;

  int conta_terr = 0;
  int cantJ = partidaAct->jugadores.size();
  int eleccion1;
  int eleccion2;
  std::string colJugadores[6] = {"rojo", "azul", "amarillo", "naranja", "verde", "rosado"};
  std::string coltext[6] = {red, blue, yellow, orange, green, magenta};
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
      std::cout << "Jugador " << coltext[i] << "(" + aux[i] + ")" << reset << " es su turno para:" << std::endl;
      std::cout << "Elijir uno de los siguientes continetes:" << std::endl;
      std::cout << "1. America Del Norte" << std::endl;
      std::cout << "2. America Del Sur" << std::endl;
      std::cout << "3. Europa" << std::endl;
      std::cout << "4. Africa" << std::endl;
      std::cout << "5. Asia" << std::endl;
      std::cout << "6. Australia" << std::endl;
      std::cout << "Ingrese el numero del continente seleccionado: ";
      std::cin >> eleccion1;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl;

      switch (eleccion1)
      {

      case 1:
      {
        if (!tieneTerriDisp(AmericaNorte))
        {
          std::cout << "No hay territorios disponibles en America del Norte." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en America del Norte:" << std::endl;
        for (size_t j = 0; j < AmericaNorte.size(); j++)
        {
          std::cout << j + 1 << ". " << AmericaNorte[j] << std::endl;
        }

        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (eleccion2 >= 1 && eleccion2 <= AmericaNorte.size())
        {
          salvaNomTerri = AmericaNorte[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 12; i++)
          {
            if (partidaAct->continentes[0]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[0]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[0]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << AmericaNorte[eleccion2 - 1] << std::endl;
          std::cout << std::endl;
          AmericaNorte.erase(AmericaNorte.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      case 2:
      {
        if (!tieneTerriDisp(AmericaSur))
        {
          std::cout << "No hay territorios disponibles en America Del Sur." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en America Del Sur:" << std::endl;
        for (size_t j = 0; j < AmericaSur.size(); j++)
        {
          std::cout << j + 1 << ". " << AmericaSur[j] << std::endl;
        }

        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (eleccion2 >= 1 && eleccion2 <= AmericaSur.size())
        {
          salvaNomTerri = AmericaSur[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 4; i++)
          {
            if (partidaAct->continentes[1]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[1]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[1]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << AmericaSur[eleccion2 - 1] << std::endl;
          std::cout << std::endl;

          AmericaSur.erase(AmericaSur.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      case 3:
      {
        if (!tieneTerriDisp(Europa))
        {
          std::cout << "No hay territorios disponibles en Europa." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en Europa:" << std::endl;
        for (size_t j = 0; j < Europa.size(); j++)
        {
          std::cout << j + 1 << ". " << Europa[j] << std::endl;
        }

        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (eleccion2 >= 1 && eleccion2 <= Europa.size())
        {
          salvaNomTerri = Europa[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 7; i++)
          {
            if (partidaAct->continentes[4]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[4]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[4]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << Europa[eleccion2 - 1] << std::endl;
          std::cout << std::endl;

          Europa.erase(Europa.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      case 4:
      {
        if (!tieneTerriDisp(Africa))
        {
          std::cout << "No hay territorios disponibles en Africa." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en Africa:" << std::endl;
        for (size_t j = 0; j < Africa.size(); j++)
        {
          std::cout << j + 1 << ". " << Africa[j] << std::endl;
        }
        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (eleccion2 >= 1 && eleccion2 <= Africa.size())
        {
          salvaNomTerri = Africa[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 6; i++)
          {
            if (partidaAct->continentes[3]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[3]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[3]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << Africa[eleccion2 - 1] << std::endl;
          std::cout << std::endl;

          Africa.erase(Africa.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      case 5:
      {
        if (!tieneTerriDisp(Asia))
        {
          std::cout << "No hay territorios disponibles en Asia." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en Asia:" << std::endl;
        for (size_t j = 0; j < Asia.size(); j++)
        {
          std::cout << j + 1 << ". " << Asia[j] << std::endl;
        }

        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (eleccion2 >= 1 && eleccion2 <= Asia.size())
        {
          salvaNomTerri = Asia[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 12; i++)
          {
            if (partidaAct->continentes[2]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[2]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[2]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << Asia[eleccion2 - 1] << std::endl;
          std::cout << std::endl;

          Asia.erase(Asia.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      case 6:
      {
        if (!tieneTerriDisp(Australia))
        {
          std::cout << "No hay territorios disponibles en Australia." << std::endl;
          std::cout << std::endl;

          i = i - 1;
          break;
        }

        std::cout << "Territorios disponibles en Australia:" << std::endl;
        for (size_t j = 0; j < Australia.size(); j++)
        {
          std::cout << j + 1 << ". " << Australia[j] << std::endl;
        }

        std::cout << "Ingrese el numero del territorio seleccionado: ";
        std::cin >> eleccion2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (eleccion2 >= 1 && eleccion2 <= Australia.size())
        {
          salvaNomTerri = Australia[eleccion2 - 1];
          Jugador *player = partidaAct->buscaJ(aux[i]);

          for (int i = 0; i < 4; i++)
          {
            if (partidaAct->continentes[5]->territorios[i]->nombreTerri == salvaNomTerri)
            {
              partidaAct->continentes[5]->territorios[i]->duenoAct = player;
              player->ejercito = player->ejercito - 1;
              partidaAct->continentes[5]->territorios[i]->uniEjercito = 1;
              break;
            }
          }

          std::cout << std::endl;
          std::cout << "Territorio elegido: " << Australia[eleccion2 - 1] << std::endl;
          std::cout << std::endl;

          Australia.erase(Australia.begin() + eleccion2 - 1);
          conta_terr++;

          std::cout << "Presione Enter para continuar..." << std::endl;
          // std::cin.ignore();
          std::cin.get();
          system("clear");
        }
        else
        {
          std::cout << std::endl;
          std::cout << "Numero de territorio invalido." << std::endl;
          std::cout << std::endl;
          i = i - 1;
        }

        break;
      }

      default:
      {
        std::cout << "Continente no valido. Intente nuevamente." << std::endl;
        std::cout << std::endl;
        i = i - 1;

        break;
      }
      }
      // limpiamos el buffer
      std::cin.clear();
    }
  }
  std::cout << "Se ha inizializado la partida correctamente" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

void SistemaApoyo::repartirTropas(Partida *partidaAct)
{
  int cantJ = partidaAct->jugadores.size();
  int asignTrops = 0;

  std::string colJugadores[6] = {"rojo", "azul", "amarillo", "naranja", "verde", "rosado"};
  std::string coltext[6] = {red, blue, yellow, orange, green, magenta};
  std::string aux[cantJ];

  for (int i = 0; i < cantJ; i++)
  {
    aux[i] = colJugadores[i];
  }

  std::cout << "Ahora cada jugador debe repartir sus tropas en los territorios que eligio." << std::endl;
  std::cout << std::endl;

  for (int h = 0; h < cantJ; h++)
  {
    std::cout << "Turno del Jugador " << coltext[h] << "(" + aux[h] + ")" << reset << " para distribuir tropas en los territorios que eligio:" << std::endl;
    for (int i = 0; i < 6; i++)
    {
      std::cout << std::endl;
      std::cout << "En el continente " << partidaAct->continentes[i]->nombreCont << " dominas los siguientes territorios: " << std::endl;
      for (int j = 0; j < partidaAct->continentes[i]->territorios.size(); j++) //
      {
        if (partidaAct->continentes[i]->territorios[j]->duenoAct->color == aux[h])
        {

          if (partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito == 0)
          {
            std::cout << "Ya no tienes mas tropas disponibles para repartir." << std::endl;
            std::cout << std::endl;
            break; // si el jugador no tiene mas tropas disponibles, se pasa al siguiente jugador
          }

          std::cout << std::endl;
          std::cout << "Recuerda que justo ahora tienes en total: " << partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito << " tropas disponibles." << std::endl;

          std::cout << " - " << partidaAct->continentes[i]->territorios[j]->nombreTerri << " tiene: " << partidaAct->continentes[i]->territorios[j]->uniEjercito << " tropas" << std::endl;
          std::cout << "Ingresa cuantas tropas quieres agregarle a este territorio: ";
          std::cin >> asignTrops;
          partidaAct->actualizarMatrizTropas(partidaAct->continentes[i]->territorios[j]->nombreTerri, asignTrops);
          
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << std::endl;

          while (asignTrops > partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito || asignTrops < 0)
          {
            std::cout << std::endl;
            std::cout << "Cantidad de tropas invalida." << std::endl;
            std::cout << "Recuerda que tienes: " << partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito << " tropas disponibles." << std::endl;
            std::cout << "Ingresa una cantidad de tropas no mayor ni menor a las que tienes disponibles" << std::endl;
            std::cout << std::endl;
            std::cout << " - " << partidaAct->continentes[i]->territorios[j]->nombreTerri << " tiene: " << partidaAct->continentes[i]->territorios[j]->uniEjercito << " tropas" << std::endl;
            std::cout << "Ingresa cuantas tropas quieres agregarle a este territorio: ";
            std::cin >> asignTrops;
            partidaAct->actualizarMatrizTropas(partidaAct->continentes[i]->territorios[j]->nombreTerri, asignTrops);
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl;
          }

          partidaAct->continentes[i]->territorios[j]->uniEjercito = partidaAct->continentes[i]->territorios[j]->uniEjercito + asignTrops;               // asigna las tropas al territorio
          partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito = partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito - asignTrops; // resta las tropas al jugador

          if (partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito == 0)
          {
            std::cout << "Ya no tienes mas tropas disponibles para repartir." << std::endl;
            std::cout << std::endl;
            break; // si el jugador no tiene mas tropas disponibles, se pasa al siguiente jugador
          }
        }
      }
      std::cout << std::endl;
      std::cout << "--------------------------------------------------------" << std::endl;
      std::cout << std::endl;
    }
    if (partidaAct->buscaJ(aux[h])->ejercito > 0) //
    {
      std::cout << "Aun tienes tropas disponibles para repartir." << std::endl;
      std::cout << std::endl;
      std::cout << "Presione Enter para continuar..." << std::endl;
      // std::cin.ignore();
      std::cin.get();
      system("clear");
      h = h - 1;
    }
    std::cout << "Presione Enter para continuar..." << std::endl;
    // std::cin.ignore();
    std::cin.get();
    system("clear");
  }
}

void SistemaApoyo::accionesTurno(Partida *partidaAct)
{
  int uniEjerAdicionales = 0;
  int asignTrops = 0;

  for (Continente *continente : partidaAct->continentes)
  {
    for (Territorio *territorio : continente->territorios)
    {
      if (partidaAct->jugadorActual->color == territorio->duenoAct->color)
      {
        uniEjerAdicionales++;
      }
    }
  }

  std::cout << std::endl;
  std::cout << "Como actualmente tienes " << uniEjerAdicionales << " territorios conquistados, vas a recibir: ";

  uniEjerAdicionales = uniEjerAdicionales / 3;

  std::cout << uniEjerAdicionales << " tropas adicionales." << std::endl;

  partidaAct->jugadorActual->ejercito = partidaAct->jugadorActual->ejercito + uniEjerAdicionales;

  do
  {
    for (int i = 0; i < 6; i++)
    {
      std::cout << "Del continente: " << partidaAct->continentes[i]->nombreCont << std::endl;
      for (int j = 0; j < partidaAct->continentes[i]->territorios.size(); j++) //
      {
        if (partidaAct->continentes[i]->territorios[j]->duenoAct->color == partidaAct->jugadorActual->color)
        {

          if (partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito == 0)
          {
            std::cout << "Ya no tienes mas tropas disponibles para repartir." << std::endl;
            std::cout << std::endl;
            break; // si el jugador no tiene mas tropas disponibles, se pasa al siguiente jugador
          }

          std::cout << "Justo ahora tienes en total: " << partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito << " tropas disponibles." << std::endl;
          std::cout << " - El territorio: " << partidaAct->continentes[i]->territorios[j]->nombreTerri << " va a tener " << partidaAct->continentes[i]->territorios[j]->uniEjercito << " + ";
          std::cin >> asignTrops;
          
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << std::endl;

          while (asignTrops > partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito || asignTrops < 0)
          {
            std::cout << std::endl;
            std::cout << "Recuerda que tienes: " << partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito << " tropas disponibles." << std::endl;
            std::cout << "Ingresa una cantidad de tropas valida para este territorio." << std::endl;
            std::cout << "- El territorio: " << partidaAct->continentes[i]->territorios[j]->nombreTerri << " va a tener " << partidaAct->continentes[i]->territorios[j]->uniEjercito << " + ";
            std::cin >> asignTrops;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl;
          }

          partidaAct->continentes[i]->territorios[j]->uniEjercito = partidaAct->continentes[i]->territorios[j]->uniEjercito + asignTrops;               // asigna las tropas al territorio
          partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito = partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito - asignTrops; // resta las tropas al jugador

          if (partidaAct->continentes[i]->territorios[j]->duenoAct->ejercito == 0)
          {
            std::cout << "Ya no tienes mas tropas disponibles para repartir." << std::endl;
            std::cout << std::endl;
            break; // si el jugador no tiene mas tropas disponibles, se pasa al siguiente jugador
          }
        }
      }
      std::cout << std::endl;
      std::cout << "--------------------------------------------------------" << std::endl;
      std::cout << std::endl;
    }

    std::cout << "Aun tienes tropas disponibles para repartir." << std::endl;
    std::cout << "Presione Enter para continuar..." << std::endl;
    
    actTableroInfoActual();

    std::cin.get();
    system("clear");

  } while (partidaAct->jugadorActual->ejercito > 0);

  std::cout << "Ya que recibiste tus tropas adicionales y las repartiste en tus territorios" << std::endl;

  // ciclo para asegurarse que el jugador ingrese una opcion valida
  int eleccion;
  do
  {
    std::cout << "Elije lo que deseas hacer en este turno: " << std::endl;
    std::cout << "1. Atacar" << std::endl;
    std::cout << "2. Fortificar" << std::endl;

    std::cout << "Ingrese el numero de la accion que desea realizar: ";
    std::cin >> eleccion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;

    switch (eleccion)
    {
    case 1:
    {
      std::cout << "Atacar" << std::endl;
      partidaAct->atacar();
      break;
    }

    case 2:
    {
      std::cout << "Fortificar" << std::endl;
      partidaAct->fortificar();
      break;
    }

    default:
    {
      std::cout << "Accion no valida. Vuelva aintentarlo" << std::endl;
      break;
    }
    }
  } while (eleccion != 1 && eleccion != 2);
}

bool tieneTerriDisp(const std::vector<std::string> &continente)
{
  return !continente.empty();
}

void SistemaApoyo::inicializarTablero()
{

  tablero.insertarTerritorio(("Alaska"));
  tablero.insertarTerritorio(("Alberta"));
  tablero.insertarTerritorio(("America Central"));
  tablero.insertarTerritorio(("Estados Unidos Orientales"));
  tablero.insertarTerritorio(("Groenlandia"));
  tablero.insertarTerritorio(("Territorio Noroccidental"));
  tablero.insertarTerritorio(("Ontario"));
  tablero.insertarTerritorio(("Quebec"));
  tablero.insertarTerritorio(("Estados Unidos Occidentales"));
  tablero.insertarTerritorio(("Argentina"));
  tablero.insertarTerritorio(("Brasil"));
  tablero.insertarTerritorio(("Peru"));
  tablero.insertarTerritorio(("Venezuela"));
  tablero.insertarTerritorio(("Gran Bretana"));
  tablero.insertarTerritorio(("Islandia"));
  tablero.insertarTerritorio(("Europa Del Norte"));
  tablero.insertarTerritorio(("Escandinavia"));
  tablero.insertarTerritorio(("Europa Del Sur"));
  tablero.insertarTerritorio(("Ucrania"));
  tablero.insertarTerritorio(("Europa Occidental"));
  tablero.insertarTerritorio(("Congo"));
  tablero.insertarTerritorio(("Africa Oriental"));
  tablero.insertarTerritorio(("Egipto"));
  tablero.insertarTerritorio(("Madagascar"));
  tablero.insertarTerritorio(("Africa Del Norte"));
  tablero.insertarTerritorio(("Africa Del Sur"));
  tablero.insertarTerritorio(("Afghanistan"));
  tablero.insertarTerritorio(("China"));
  tablero.insertarTerritorio(("India"));
  tablero.insertarTerritorio(("Irkutsk"));
  tablero.insertarTerritorio(("Japon"));
  tablero.insertarTerritorio(("Kamchatka"));
  tablero.insertarTerritorio(("Medio Oriente"));
  tablero.insertarTerritorio(("Mongolia"));
  tablero.insertarTerritorio(("Siam"));
  tablero.insertarTerritorio(("Siberia"));
  tablero.insertarTerritorio(("Ural"));
  tablero.insertarTerritorio(("Yakutsk"));
  tablero.insertarTerritorio(("Australia Oriental"));
  tablero.insertarTerritorio(("Indonesia"));
  tablero.insertarTerritorio(("Nueva Guinea"));
  tablero.insertarTerritorio(("Australia Occidental"));

  //! Conexiones America Del Norte

  Territorio *terriObj;
  //?Conexiones de Alaska
  tablero.InsertarCamino(("Alaska"), ("Territorio Noroccidental"), 1);
  tablero.InsertarCamino(("Alaska"), ("Alberta"), 1);
  tablero.InsertarCamino(("Alaska"), ("Kamchatka"), 1);
  //?Conexiones de Alberta
  tablero.InsertarCamino(("Alberta"), ("Alaska"), 1);
  tablero.InsertarCamino(("Alberta"), ("Territorio Noroccidental"), 1);
  tablero.InsertarCamino(("Alberta"), ("Ontario"), 1);
  tablero.InsertarCamino(("Alberta"), ("Quebec"), 1);
  //?Conexiones de America Central
  tablero.InsertarCamino(("America Central"), ("Estados Unidos Orientales"), 1);
  tablero.InsertarCamino(("America Central"), ("Estado Unidos Occidentales"), 1);
  tablero.InsertarCamino(("America Central"), ("Venezuela"), 1);
  //?Conexiones de Estados Unidos Orientales
  tablero.InsertarCamino(("Estados Unidos Orientales"), ("America Central"), 1);
  tablero.InsertarCamino(("Estados Unidos Orientales"), ("Ontario"), 1);
  tablero.InsertarCamino(("Estados Unidos Orientales"), ("Quebec"), 1);
  tablero.InsertarCamino(("Estados Unidos Orientales"), ("Estados Unidos Occidentales"), 1);
  //?Conexiones de Groenlandia
  tablero.InsertarCamino(("Groenlandia"), ("Territorio Noroccidental"), 1);
  tablero.InsertarCamino(("Groenlandia"), ("Ontario"), 1);
  tablero.InsertarCamino(("Groenlandia"), ("Quebec"), 1);
  tablero.InsertarCamino(("Groenlandia"), ("Islandia"), 1);
  //?Conexiones de Territorio Noroccidental
  tablero.InsertarCamino(("Territorio Noroccidental"), ("Alaska"), 1);
  tablero.InsertarCamino(("Territorio Noroccidental"), ("Alberta"), 1);
  tablero.InsertarCamino(("Territorio Noroccidental"), ("Ontario"), 1);
  tablero.InsertarCamino(("Territorio Noroccidental"), ("Groenlandia"), 1);
  //?Conexiones de Ontario
  tablero.InsertarCamino(("Ontario"), ("Alberta"), 1);
  tablero.InsertarCamino(("Ontario"), ("Territorio Noroccidental"), 1);
  tablero.InsertarCamino(("Ontario"), ("Groenlandia"), 1);
  tablero.InsertarCamino(("Ontario"), ("Quebec"), 1);
  tablero.InsertarCamino(("Ontario"), ("Estados Unidos Orientales"), 1);
  tablero.InsertarCamino(("Ontario"), ("Estados Unidos Occidentales"), 1);
  //?Conexiones de Quebec
  tablero.InsertarCamino(("Quebec"), ("Ontario"), 1);
  tablero.InsertarCamino(("Quebec"), ("Groenlandia"), 1);
  tablero.InsertarCamino(("Quebec"), ("Estados Unidos Orientales"), 1);
  //?Conexiones de Estados Unidos Occidentales
  tablero.InsertarCamino(("Estados Unidos Occidentales"), ("America Central"), 1);
  tablero.InsertarCamino(("Estados Unidos Occidentales"), ("Estados Unidos Orientales"), 1);
  tablero.InsertarCamino(("Estados Unidos Occidentales"), ("Ontario"), 1);
  tablero.InsertarCamino(("Estados Unidos Occidentales"), ("Alberta"), 1);

  //! Conexiones America Del Sur

  //?Conexiones de Argentina
  tablero.InsertarCamino(("Argentina"), ("Peru"), 1);
  tablero.InsertarCamino(("Argentina"), ("Brasil"), 1);
  //?Conexiones de Brasil
  tablero.InsertarCamino(("Brasil"), ("Argentina"), 1);
  tablero.InsertarCamino(("Brasil"), ("Peru"), 1);
  tablero.InsertarCamino(("Brasil"), ("Venezuela"), 1);
  tablero.InsertarCamino(("Brasil"), ("Africa Del Norte"), 1);
  //?Conexiones de Peru
  tablero.InsertarCamino(("Peru"), ("Argentina"), 1);
  tablero.InsertarCamino(("Peru"), ("Brasil"), 1);
  tablero.InsertarCamino(("Peru"), ("Venezuela"), 1);
  //?Conexiones de Venezuela
  tablero.InsertarCamino(("Venezuela"), ("America Central"), 1);
  tablero.InsertarCamino(("Venezuela"), ("Brasil"), 1);
  tablero.InsertarCamino(("Venezuela"), ("Peru"), 1);

  //! Conexiones Europa

  //?Conexiones de Gran Bretana
  tablero.InsertarCamino(("Gran Bretana"), ("Islandia"), 1);
  tablero.InsertarCamino(("Gran Bretana"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Gran Bretana"), ("Escandinavia"), 1);
  tablero.InsertarCamino(("Gran Bretana"), ("Europa Occidental"), 1);
  //?Conexiones de Islandia
  tablero.InsertarCamino(("Islandia"), ("Groenlandia"), 1);
  tablero.InsertarCamino(("Islandia"), ("Gran Bretana"), 1);
  tablero.InsertarCamino(("Islandia"), ("Escandinavia"), 1);
  //?Conexiones de Europa Del Norte, con Gran Bretana, Escandinavia, Europa del Sur, Ucrania, Europa Occidental
  tablero.InsertarCamino(("Europa Del Norte"), ("Gran Bretana"), 1);
  tablero.InsertarCamino(("Europa Del Norte"), ("Escandinavia"), 1);
  tablero.InsertarCamino(("Europa Del Norte"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Europa Del Norte"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Europa Del Norte"), ("Europa Occidental"), 1);
  //?Conexiones de Escandinavia con Gran Bretana, Isalndia, Europa Del Norte, Ucrania.
  tablero.InsertarCamino(("Escandinavia"), ("Gran Bretana"), 1);
  tablero.InsertarCamino(("Escandinavia"), ("Islandia"), 1);
  tablero.InsertarCamino(("Escandinavia"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Escandinavia"), ("Ucrania"), 1);
  //?Conexiones de Europa Del Sur con Europa Del Norte, Ucrania, Europa Occidental, Egipto, Africa Del Norte, Medio Oriente.
  tablero.InsertarCamino(("Europa Del Sur"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Europa Del Sur"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Europa Del Sur"), ("Europa Occidental"), 1);
  tablero.InsertarCamino(("Europa Del Sur"), ("Egipto"), 1);
  tablero.InsertarCamino(("Europa Del Sur"), ("Africa Del Norte"), 1);
  tablero.InsertarCamino(("Europa Del Sur"), ("Medio Oriente"), 1);
  //?Conexiones de Ucrania con Europa Del Norte, Escandinavia, Europa Del Sur, Afghanistan, Medio Oriente, Ural.
  tablero.InsertarCamino(("Ucrania"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Escandinavia"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Afghanistan"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Medio Oriente"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Ural"), 1);
  //?Conexiones de Europa Occidental con Gran Bretana, Europa Del Norte, Europa Del Sur, Africa Del Norte.
  tablero.InsertarCamino(("Europa Occidental"), ("Gran Bretana"), 1);
  tablero.InsertarCamino(("Europa Occidental"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Europa Occidental"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Europa Occidental"), ("Africa Del Norte"), 1);

  //! Conexiones Africa

  //?Conexiones de Congo con Africa Del Norte, Africa Oriental, Africa Del Sur.
  tablero.InsertarCamino(("Congo"), ("Africa Del Norte"), 1);
  tablero.InsertarCamino(("Congo"), ("Africa Oriental"), 1);
  tablero.InsertarCamino(("Congo"), ("Africa Del Sur"), 1);
  //?Conexiones de Africa Oriental con Congo, Africa Del Norte, Egipto, Madagascar, Africa Del Sur.
  tablero.InsertarCamino(("Africa Oriental"), ("Congo"), 1);
  tablero.InsertarCamino(("Africa Oriental"), ("Africa Del Norte"), 1);
  tablero.InsertarCamino(("Africa Oriental"), ("Egipto"), 1);
  tablero.InsertarCamino(("Africa Oriental"), ("Madagascar"), 1);
  tablero.InsertarCamino(("Africa Oriental"), ("Africa Del Sur"), 1);
  //?Conexiones de Egipto con Europa Del Sur, Africa Del Norte, Africa Oriental, Medio Oriente.
  tablero.InsertarCamino(("Egipto"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Egipto"), ("Africa Del Norte"), 1);
  tablero.InsertarCamino(("Egipto"), ("Africa Oriental"), 1);
  tablero.InsertarCamino(("Egipto"), ("Medio Oriente"), 1);
  //?Conexiones de Madagascar con Africa Oriental, Africa Del Sur.
  tablero.InsertarCamino(("Madagascar"), ("Africa Oriental"), 1);
  tablero.InsertarCamino(("Madagascar"), ("Africa Del Sur"), 1);
  //?Conexiones de Africa Del Norte con Brasil, Europa Del Sur, Congo, Africa Oriental, Egipto, Europa Occidental.
  tablero.InsertarCamino(("Africa Del Norte"), ("Brasil"), 1);
  tablero.InsertarCamino(("Africa Del Norte"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Africa Del Norte"), ("Congo"), 1);
  tablero.InsertarCamino(("Africa Del Norte"), ("Africa Oriental"), 1);
  tablero.InsertarCamino(("Africa Del Norte"), ("Egipto"), 1);
  tablero.InsertarCamino(("Africa Del Norte"), ("Europa Occidental"), 1);
  //?Conexiones de Africa Del Sur con Congo, Africa Oriental, Madagascar.
  tablero.InsertarCamino(("Africa Del Sur"), ("Congo"), 1);
  tablero.InsertarCamino(("Africa Del Sur"), ("Africa Oriental"), 1);
  tablero.InsertarCamino(("Africa Del Sur"), ("Madagascar"), 1);

  //! Conexiones Asia

  //?Conexiones de Afghanistan con Ucrania, Medio Oriente, China, India, Ural.
  tablero.InsertarCamino(("Afghanistan"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Afghanistan"), ("Medio Oriente"), 1);
  tablero.InsertarCamino(("Afghanistan"), ("China"), 1);
  tablero.InsertarCamino(("Afghanistan"), ("India"), 1);
  tablero.InsertarCamino(("Afghanistan"), ("Ural"), 1);
  //?Conexiones de China con Afghanistan, India, Mongolia, Siam, Siberia, Ural.
  tablero.InsertarCamino(("China"), ("Afghanistan"), 1);
  tablero.InsertarCamino(("China"), ("India"), 1);
  tablero.InsertarCamino(("China"), ("Mongolia"), 1);
  tablero.InsertarCamino(("China"), ("Siam"), 1);
  tablero.InsertarCamino(("China"), ("Siberia"), 1);
  tablero.InsertarCamino(("China"), ("Ural"), 1);
  //?Conexiones de India con Afghanistan, China, Siam, Medio Oriente.
  tablero.InsertarCamino(("India"), ("Afghanistan"), 1);
  tablero.InsertarCamino(("India"), ("China"), 1);
  tablero.InsertarCamino(("India"), ("Siam"), 1);
  tablero.InsertarCamino(("India"), ("Medio Oriente"), 1);
  //?Conexiones de Irkutsk con Siberia, Yakutsk, Kamchatka, Mongolia.
  tablero.InsertarCamino(("Irkutsk"), ("Siberia"), 1);
  tablero.InsertarCamino(("Irkutsk"), ("Yakutsk"), 1);
  tablero.InsertarCamino(("Irkutsk"), ("Kamchatka"), 1);
  tablero.InsertarCamino(("Irkutsk"), ("Mongolia"), 1);
  //?Conexiones de Japon con Kamchatka, Mongolia.
  tablero.InsertarCamino(("Japon"), ("Kamchatka"), 1);
  tablero.InsertarCamino(("Japon"), ("Mongolia"), 1);
  //?Conexiones de Kamchatka con Alaska, Irkutsk, Japon, Mongolia, Yakutsk.
  tablero.InsertarCamino(("Kamchatka"), ("Alaska"), 1);
  tablero.InsertarCamino(("Kamchatka"), ("Irkutsk"), 1);
  tablero.InsertarCamino(("Kamchatka"), ("Japon"), 1);
  tablero.InsertarCamino(("Kamchatka"), ("Mongolia"), 1);
  //?Conexiones de Medio Oriente con Ucrania, Afghanistan, India, Egipto, Europa Del Sur.
  tablero.InsertarCamino(("Medio Oriente"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Medio Oriente"), ("Afghanistan"), 1);
  tablero.InsertarCamino(("Medio Oriente"), ("India"), 1);
  tablero.InsertarCamino(("Medio Oriente"), ("Egipto"), 1);
  tablero.InsertarCamino(("Medio Oriente"), ("Europa Del Sur"), 1);
  //?Conexiones de Mongolia con Siberia, China, Irkutsk, Japon, Kamchatka.
  tablero.InsertarCamino(("Mongolia"), ("Siberia"), 1);
  tablero.InsertarCamino(("Mongolia"), ("China"), 1);
  tablero.InsertarCamino(("Mongolia"), ("Irkutsk"), 1);
  tablero.InsertarCamino(("Mongolia"), ("Japon"), 1);
  tablero.InsertarCamino(("Mongolia"), ("Kamchatka"), 1);
  //?Conexiones de Siam con India, China, Indonesia.
  tablero.InsertarCamino(("Siam"), ("India"), 1);
  tablero.InsertarCamino(("Siam"), ("China"), 1);
  tablero.InsertarCamino(("Siam"), ("Indonesia"), 1);
  //?Conexiones de Siberia con Ural, China, Irkutsk, Mongolia, Yakutsk.
  tablero.InsertarCamino(("Siberia"), ("Ural"), 1);
  tablero.InsertarCamino(("Siberia"), ("China"), 1);
  tablero.InsertarCamino(("Siberia"), ("Irkutsk"), 1);
  tablero.InsertarCamino(("Siberia"), ("Mongolia"), 1);
  //?Conexiones de Ural con Ucrania, Afghanistan, Siberia, China.
  tablero.InsertarCamino(("Ural"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Ural"), ("Afghanistan"), 1);
  tablero.InsertarCamino(("Ural"), ("Siberia"), 1);
  tablero.InsertarCamino(("Ural"), ("China"), 1);
  //?Conexiones de Yakutsk con Siberia, Irkutsk, Kamchatka.
  tablero.InsertarCamino(("Yakutsk"), ("Siberia"), 1);
  tablero.InsertarCamino(("Yakutsk"), ("Irkutsk"), 1);
  tablero.InsertarCamino(("Yakutsk"), ("Kamchatka"), 1);

  //! Conexiones Oceania

  //?Conexiones de Australia Oriental con Indonesia, Nueva Guinea, Australia Occidental.
  tablero.InsertarCamino(("Australia Oriental"), ("Indonesia"), 1);
  tablero.InsertarCamino(("Australia Oriental"), ("Nueva Guinea"), 1);
  //?Conexiones de Indonesia con Siam, Nueva Guinea, Australia Oriental.
  tablero.InsertarCamino(("Indonesia"), ("Siam"), 1);
  tablero.InsertarCamino(("Indonesia"), ("Nueva Guinea"), 1);
  tablero.InsertarCamino(("Indonesia"), ("Australia Oriental"), 1);
  //?Conexiones de Nueva Guinea con Indonesia, Australia Oriental, Australia Occidental.
  tablero.InsertarCamino(("Nueva Guinea"), ("Indonesia"), 1);
  tablero.InsertarCamino(("Nueva Guinea"), ("Australia Oriental"), 1);
  tablero.InsertarCamino(("Nueva Guinea"), ("Australia Occidental"), 1);
  //?Conexiones de Australia Occidental con Indonesia, Nueva Guinea, Australia Oriental.
  tablero.InsertarCamino(("Australia Occidental"), ("Indonesia"), 1);
  tablero.InsertarCamino(("Australia Occidental"), ("Nueva Guinea"), 1);
  tablero.InsertarCamino(("Australia Occidental"), ("Australia Oriental"), 1);

  std::cout << "-------------------------------------------------------------------------------" << std::endl;
  tablero.imprimirMatriz();
  std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void SistemaApoyo::actTableroInfoActual()
{
  std::string nombreTerriDestino;

  // recorrer la matriz de adyacencia, rescatar el nombre del territorio de origen y el nombre del territorio de destino, buscar los territorios en la partida y actualizar el peso de la conexion
  for (int i = 0; i < 42; i++)
  {
    for (int j = 0; j < 42; j++)
    {
      if (tablero.matriz_adyacencia[i][j] != 0)
      { // si el peso de la conexion es distinto de 0 es decir si hay una conexion
        nombreTerriDestino = tablero.territorios[j]; // rescatar el nombre del territorio de destino

        for (Continente *continente : partida->continentes)
        { // buscar el territorio de destino en la partida
          for (Territorio *territorio : continente->territorios)
          {
            if (territorio->nombreTerri == nombreTerriDestino)
            {
              tablero.matriz_adyacencia[i][j] = territorio->uniEjercito; // actualizar el peso de la conexion
            }
          }
        }
      }
    }
  }

  std::cout << "------------- Matriz de adyacencia actualizada -------------" << std::endl;
  tablero.imprimirMatriz();
  std::cout << "------------------------------------------------------------" << std::endl;


  this->partida->tablero = tablero;
}

void SistemaApoyo::costoConquista(std::string objetivoAtaque)
{
  actTableroInfoActual();

  std::string jugadorAct = partida->jugadorActual->color;

  // almacenar los nombres de todos los territorios del jugador actual
  std::vector<std::string> conquistados;

  for (Continente *continente : partida->continentes)
  {
    for (Territorio *territorio : continente->territorios)
    {
      if (territorio->duenoAct->color == jugadorAct)
      {
        conquistados.push_back(territorio->nombreTerri);
      }
    }
  }

  //verificar si el objetivo de ataque es un territorio del jugador actual
  bool propio = false;
  for (int i = 0; i < conquistados.size(); i++)
  {
    if (conquistados[i] == objetivoAtaque)
    {
      propio = true;
    }
  }

  // si el objetivo de ataque es un territorio del jugador actual mensaje de que no se puede atacar y salir de la funcion
  if (propio)
  {
    std::cout << "No puedes atacar a un territorio que ya es tuyo." << std::endl;
    return;
  }
  else // si el objetivo de ataque no es un territorio del jugador actual
  {
    // verificar si el objetivo de ataque es un territorio del tablero
    bool existe = false;
    for (int i = 0; i < 42; i++)
    {
      if (tablero.territorios[i] == objetivoAtaque)
      {
        existe = true;
        std::cout << "El territorio que ingresaste si existe." << std::endl;
      }
    }

    // si el objetivo de ataque no es un territorio del tablero, mensaje de que no existe y salir de la funcion
    if (existe == false)
    {
      std::cout << "El territorio que ingresaste no existe." << std::endl;
      return;
    }
    else // si el objetivo de ataque es un territorio del tablero
    {
      // almacenar los caminos mas cortos entre los territorios conquistados y el objetivo de ataque
      std::vector< std::vector< std::pair<std::string, std::string> > > caminosCortos;
      for (int i = 0; i < conquistados.size(); i++)
      {
        std::cout << "Cantidad de territorios conquistados: " << conquistados.size() << std::endl;
        std::vector<std::pair<std::string, std::string>> camCortosPais = tablero.dijkstra(conquistados[i]);

        std::stack<std::pair<std::string, std::string>> caminosCortosInvertidos;
        std::vector<std::pair<std::string, std::string>> final;

        bool listo = false;
        std::string destino = objetivoAtaque;

        while(listo == false)
        {
          for (int i = 0; i < camCortosPais.size(); i++) //
          {
            if (camCortosPais[i].second.compare(destino) == 0) 
            {
              destino = camCortosPais[i].first;
              caminosCortosInvertidos.push(camCortosPais[i]);
            }
          }

          if (destino.compare(conquistados[i]) == 0) 
          {
            listo = true;
          }
        }

        std::cout << "Salio del while de listo" << std::endl;

        while (!caminosCortosInvertidos.empty())
        {
          final.push_back(caminosCortosInvertidos.top());
          caminosCortosInvertidos.pop();
        }

        caminosCortos.push_back(final);
          
      }

      std::cout << "Salio del 1er for" << std::endl;

      int minPos = 0;
      for(int i = 1; i < caminosCortos.size(); i++)
      {
        if (caminosCortos[i].size() < caminosCortos[minPos].size())
        {
          minPos = i;
        }
      }

      std::cout << "El camino mas corto para conquistar el territorio \"" << objetivoAtaque << "\" es: " << std::endl;
      for (int i = 0; i < caminosCortos[minPos].size(); i++)
      {
        std::cout << caminosCortos[minPos][i].first << " -> ";
      }

      int costo = 0;
      for (int i = 0; i < caminosCortos[minPos].size(); i++)
      {
        std::string origen = caminosCortos[minPos][i].first;
        std::string destino = caminosCortos[minPos][i].second;
        int calConexion = tablero.valorConexion(origen, destino);
        costo = costo + calConexion;
      }

      std::cout << "El costo de conquista es: " << costo << std::endl;

    }
  }

}

void SistemaApoyo::conquistaMasBarata(Partida *partidaAct)
{
  for (Continente *continente : partidaAct->continentes)
  {
    for (Territorio *territorio : continente->territorios)
    {
      if (territorio->duenoAct->color == partidaAct->jugadorActual->color)
      {
        int territorioIndex = tablero.indiceTerritorio(territorio->nombreTerri);
        std::cout << "\nEn el territorio: " << territorio->nombreTerri << ", la conquista mas barata es:" << std::endl;

        int menorCosto = INT_MAX; // Inicializamos el menorCosto con un valor alto
        for (int i = 0; i < 42; i++)
        {
          if (i != territorioIndex && tablero.matriz_adyacencia[territorioIndex][i] == 1)
          {
            if (tablero.matriz_adyacencia[territorioIndex][i] < menorCosto)
            {
              menorCosto = tablero.matriz_adyacencia[territorioIndex][i];
            }
          }
        }

        // Después de recorrer la fila, mostramos los territorios con el menor costo encontrado
        for (int i = 0; i < 42; i++)
        {
          if (i != territorioIndex && tablero.matriz_adyacencia[territorioIndex][i] == 1 && tablero.matriz_adyacencia[territorioIndex][i] == menorCosto)
          {
            std::cout << "Para el territorio \"" << tablero.territorios[i] << "\" con costo de: " << menorCosto << " tropas" << std::endl;
          }
        }
      }
    }
  }
}
