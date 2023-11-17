#include "Partida.h"
#include "fstream"
#include "HuffmanArbol.h"
#include "Tablero.h"
#include <sstream>
#include <map>
#include <limits>

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

// funcion que busca un Terriorio dado el nombre del territorio y devuelve el puntero al territorio
Territorio *Partida::buscaT(std::string nombreT)
{
  for (Continente *contiObj : continentes) // Itera sobre los continentes
  {
    for (Territorio *terriObj : contiObj->territorios) // Itera sobre los territorios de cada continente
    {
      if (terriObj && terriObj->nombreTerri == nombreT) // Si el territorio existe y tiene el nombre especificado
      {
        return terriObj; // Devuelve el puntero al territorio especificado
      }
    }
  }
  return NULL; // Si no encuentra el territorio
}

void Partida::fortificar()
{
  std::string leQuitoA;
  std::string lePongoA;
  int cantEjercitos;

  std::cout << std::endl;
  std::cout << "Recuerda que actualmente los territorios que dominas son: " << std::endl;
  // Muestra los territorios del jugador actual y la cantidad de ejercitos que tiene en cada uno
  for (Continente *continente : continentes)
  {
    std::cout << continente->nombreCont << std::endl;
    for (Territorio *territorio : continente->territorios)
    {
      if (jugadorActual->color == territorio->duenoAct->color)
      {
        std::cout << " - " << territorio->nombreTerri << " tiene: " << territorio->uniEjercito << " tropas" << std::endl;
      }
    }
  }

  // preguntar al usuario que territorio quiere fortificar (asignarle mas ejercitos), y a cual territorio se los quiere quitar para el traslado
  std::cout << std::endl;
  std::cout << "A cual territorio le quieres quitar tropas? ";
  std::getline(std::cin, leQuitoA);
  //std::cin >> leQuitoA;
  std::cout << "A que territorio quieres ponerle esas tropas? ";
  std::getline(std::cin, lePongoA);
  //std::cin >> lePongoA;
  std::cout << "Cuantas tropas quieres ponerle? ";
  std::cin >> cantEjercitos;

  // Busca el territorio al que se le quitaran ejercitos
  Territorio *terriQuito = buscaT(leQuitoA);
  // Busca el territorio al que se le pondran ejercitos
  Territorio *terriPongo = buscaT(lePongoA);

  // Si se encuentran ambos territorios
  if (terriQuito && terriPongo)
  {
    // Si el territorio al que se le quitan ejercitos es del jugador actual
    if (terriQuito->duenoAct == jugadorActual)
    {
      // Si el territorio al que se le ponen ejercitos es del jugador actual
      if (terriPongo->duenoAct == jugadorActual)
      {
        // Si el territorio al que se le quitan ejercitos tiene mas ejercitos que los que se quieren quitar
        if (terriQuito->uniEjercito > cantEjercitos && cantEjercitos < terriQuito->uniEjercito - 1) // Se le resta 1 porque siempre debe quedar al menos 1 ejercito en el territorio
        {
          // Se le quitan los ejercitos al territorio
          terriQuito->uniEjercito = terriQuito->uniEjercito - cantEjercitos;
          // Se le agregan los ejercitos al territorio
          terriPongo->uniEjercito = terriPongo->uniEjercito + cantEjercitos;
          std::cout << std::endl;
          std::cout << "Ahora el territorio " << terriPongo->nombreTerri << " tiene " << terriPongo->uniEjercito << " tropas" << std::endl;
          std::cout << "Y el territorio " << terriQuito->nombreTerri << " tiene " << terriQuito->uniEjercito << " tropas" << std::endl;
          std::cout << std::endl;

          // actualizar el jugador actual, entonces el siguiente jugador en la cola de jugadores sera el jugador actual y el jugador actual pasara a ser el siguiente jugador en la cola
          Jugador *jugadorTemp = jugadorActual;
          jugadores.pop();
          jugadores.push(jugadorTemp);
          jugadorActual = jugadores.front();

          std::cout << "Presione Enter para continuar..." << std::endl;
          std::cin.ignore();
          std::cin.get();
          //system("clear");	
        }
        else
        {
          if (cantEjercitos > terriQuito->uniEjercito - 1)
          {
            std::cout << std::endl;
            std::cout << "Recuerda que siempre debe quedar al menos 1 ejercito en el territorio" << std::endl;
          }
          std::cout << "No se puede realizar la accion" << std::endl;
          std::cout<<std::endl;
          std::cout << "No perdiste tu turno" << std::endl;
          std::cout << "Presiona Enter para volverlo a intentar..." << std::endl;
          std::cin.ignore();
          std::cin.get();
          system("clear");
        }
      }
      else
      {
        std::cout << std::endl;
        std::cout << "No se puede realizar la accion" << std::endl;
        std::cout << "El territorio al que quieres ponerle tropas no es tuyo" << std::endl;
        std::cout<<std::endl;
        std::cout << "No perdiste tu turno" << std::endl;
        std::cout << "Presiona Enter para volverlo a intentar..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        system("clear");
      }
    }
    else
    {
      std::cout << std::endl;
      std::cout << "No se puede realizar la accion" << std::endl; // Si el territorio al que se le quitan ejercitos no es del jugador actual
      std::cout << "El territorio al que quieres quitarle tropas no es tuyo" << std::endl;
      std::cout<<std::endl;
      std::cout << "No perdiste tu turno" << std::endl;
      std::cout << "Presione Enter para volverlo a intentar..." << std::endl;
      std::cin.ignore();
      std::cin.get();
      system("clear");
      
    }
  }
  else
  {
    std::cout << std::endl;
    std::cout << "No se puede realizar la accion" << std::endl; // Si no se encuentran ambos territorios
    std::cout << "Uno o los dos Territorios que ingresaste no existen" << std::endl;
    std::cout<<std::endl;
    std::cout << "No perdiste tu turno" << std::endl;
    std::cout << "Presione Enter para volverlo a intentar..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    system("clear");
  }
}

void Partida::atacar()
{
  std::string atacoA;
  std::string atacoDesde;
  int cantEjercitos;

  std::queue<Jugador *> jugadoresTemp = jugadores; // Copia la cola original

  std::cout << std::endl;
  std::cout << "Recuerda que actualmente los territorios que dominas son: " << std::endl;
  for (Continente *continente : continentes)
  {
    std::cout << continente->nombreCont << std::endl;
    for (Territorio *territorio : continente->territorios)
    {
      if (jugadorActual->color == territorio->duenoAct->color)
      {
        std::cout << " - " << territorio->nombreTerri << " tiene: " << territorio->uniEjercito << " tropas" << std::endl;
      }
    }
  }

  std::cout << std::endl;
  std::cout << "Presione Enter para continuar..." << std::endl;
  //std::cin.ignore();
  std::cin.get();

  std::cout << "Antes de atacar, recuerda que actualmente los territorios se encuentran dominados de la siguiente manera: " << std::endl;

  // Muestra los territorios de los otros jugadores y la cantidad de ejercitos que tiene en cada uno, junto con el nombre del jugador
  // porque el siguiente ciclo no imprime los territorios del jugador actual?
  while (!jugadoresTemp.empty())
  {
    Jugador *jugadorObj = jugadoresTemp.front();
    if (jugadorObj->color != jugadorActual->color)
    {
      std::cout << "El jugador " << jugadorObj->color << " domina: " << std::endl;
      for (Continente *continente : continentes)
      {
        std::cout << continente->nombreCont << std::endl;
        for (Territorio *territorio : continente->territorios)
        {
          if (jugadorObj->color == territorio->duenoAct->color)
          {
            std::cout << " - " << territorio->nombreTerri << " tiene: " << territorio->uniEjercito << " tropas" << std::endl;
          }
        }
      }
    }
    std::cout << std::endl;
    jugadoresTemp.pop(); // Desencola el jugador actual de la copia
  }

  // preguntar al usuario que territorio quiere atacar, y desde que territorio quiere atacar
  std::cout << "Desde que territorio quieres atacar? ";
  std::getline(std::cin, atacoDesde);
  //std::cin >> atacoDesde;
  std::cout << "A que territorio quieres atacar? ";
  std::getline(std::cin, atacoA);
  //std::cin >> atacoA;

  Jugador *jugadorDefensor = buscaT(atacoA)->duenoAct;

  // Busca el territorio al que se le quitaran ejercitos
  Territorio *terriAtaco = buscaT(atacoA);
  // Busca el territorio al que se le pondran ejercitos
  Territorio *terriAtacoDesde = buscaT(atacoDesde);

  // Si se encuentran ambos territorios
  if (terriAtaco && terriAtacoDesde)
  {
    // Si el territorio desde el que se ataca es del jugador actual
    if (terriAtacoDesde->duenoAct == jugadorActual)
    {
      gestorDados(jugadorActual, jugadorDefensor, terriAtacoDesde, terriAtaco);
      Jugador *jugadorTemp = jugadorActual;
      jugadores.pop();
      jugadores.push(jugadorTemp);
      jugadorActual = jugadores.front();
    }
    else
    {
      std::cout << "No se puede realizar la accion" << std::endl; // Si el territorio desde el que se ataca no es del jugador actual
      std::cout << "El territorio desde el que quieres atacar no es tuyo" << std::endl;
      std::cout<<std::endl;
      std::cout << "No perdiste tu turno" << std::endl;
      std::cout << "Presione Enter para volverlo a intentar..." << std::endl;
      std::cin.ignore();
      std::cin.get();
      system("clear");
    }
  }
  else
  {
    std::cout << "No se puede realizar la accion" << std::endl; // Si no se encuentran ambos territorios
    std::cout << "Uno o los dos territorios que ingresaste no existen" << std::endl;
    std::cout<<std::endl;
    std::cout << "No perdiste tu turno" << std::endl;
    std::cout << "Presione Enter para volverlo a intentar..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    system("clear");
  }
}

// funcion para los dados
void Partida::gestorDados(Jugador *jugadorAtacante, Jugador *jugadorDefensor, Territorio *terriAtacoDesde, Territorio *terriAtaco)
{
  int dadosAtac;
  int dadosDefen;
  int cantDados;

  do
  {
    std::cout << "Cuantos dados quieres tirar? ";
    std::cin >> cantDados;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (cantDados < 1 || cantDados > 3);

  // ciclo para determinar cuando termina el ataque
  bool terminaAtaque = false;
  while (terminaAtaque != true)
  {
    int confirmOAtaque;

    if (cantDados == 1)
    {
      dadosAtac = rand() % 6 + 1;
      dadosDefen = rand() % 6 + 1;

      std::cout << "------------------------------------------" << std::endl;
      std::cout << "El atacante saco: " << dadosAtac << std::endl;
      std::cout << "El defensor saco: " << dadosDefen << std::endl;
    }
    else if (cantDados == 2)
    {
      dadosAtac = rand() % 6 + 1;
      dadosAtac = dadosAtac + rand() % 6 + 1;
      dadosDefen = rand() % 6 + 1;
      dadosDefen = dadosDefen + rand() % 6 + 1;

      std::cout << "El atacante saco en total: " << dadosAtac << std::endl;
      std::cout << "El defensor saco en total: " << dadosDefen << std::endl;
    }
    else if (cantDados == 3)
    {
      dadosAtac = rand() % 6 + 1;
      dadosAtac = dadosAtac + rand() % 6 + 1;
      dadosAtac = dadosAtac + rand() % 6 + 1;

      dadosDefen = rand() % 6 + 1;
      dadosDefen = dadosDefen + rand() % 6 + 1;
      dadosDefen = dadosDefen + rand() % 6 + 1;

      std::cout << "El atacante saco en total: " << dadosAtac << std::endl;
      std::cout << "El defensor saco en total: " << dadosDefen << std::endl;
    }

    // si el atacante saca mas que el defensor
    if (dadosAtac > dadosDefen)
    {
      terriAtaco->uniEjercito = terriAtaco->uniEjercito - 1;
      // si el defensor tiene mas de 0 ejercitos
      if (terriAtaco->uniEjercito <= 0)
      {
        std::cout << "El atacante gano el combate" << std::endl;
        std::cout << "El territorio " << terriAtaco->nombreTerri << " ahora tiene " << terriAtaco->uniEjercito << " tropas" << std::endl;
        std::cout << "El atacante conquisto el territorio " << terriAtaco->nombreTerri << std::endl;
        terriAtaco->duenoAct = jugadorAtacante;
        terriAtaco->uniEjercito = 1;
        std::cout << "El territorio " << terriAtaco->nombreTerri << " ahora pertenece al jugador " << jugadorAtacante->color << std::endl;
        std::cout << " - Como " << terriAtaco->nombreTerri <<" fue conquistado ahora tiene : "<< terriAtaco->uniEjercito << " tropas del jugador " << jugadorAtacante->color << std::endl;
        std::cout<<std::endl;
        std::cout << "Presione Enter para continuar..." << std::endl;
        //std::cin.ignore();
        std::cin.get();
        system("clear");
        terminaAtaque = true;
        break;
      }
      else if (terriAtaco->uniEjercito >= 1)
      {

        // terriAtaco->uniEjercito = terriAtaco->uniEjercito - 1;
        std::cout << "El atacante gano el combate" << std::endl;
        std::cout << "El territorio " << terriAtaco->nombreTerri << " ahora tiene " << terriAtaco->uniEjercito << " tropas" << std::endl;
        do
        {
          std::cout << "Quieres seguir atacando? (1 = si, 2 = no) ";
          std::cin >> confirmOAtaque;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (confirmOAtaque < 1 || confirmOAtaque > 2);
        if (confirmOAtaque == 2)
        {
          terminaAtaque = true;
          break;
        }
      }
    }
    // si el defensor saca mas o igual que el atacante
    else if (dadosAtac <= dadosDefen)
    {
      terriAtacoDesde->uniEjercito = terriAtacoDesde->uniEjercito - 1;
      if (terriAtacoDesde->uniEjercito <= 1) // Si el territorio desde el que se ataca tiene mas de 1 ejercito
      {

        std::cout << "El defensor (" << jugadorDefensor->color << ") logro resistir el ataque" << std::endl;
        std::cout << "El territorio " << terriAtacoDesde->nombreTerri << " ahora tiene " << terriAtacoDesde->uniEjercito << " tropas" << std::endl;
        std::cout << "El territorio " << terriAtaco->nombreTerri << " ahora tiene " << terriAtaco->uniEjercito << " tropas" << std::endl;
        terriAtacoDesde->uniEjercito = 1;
        std::cout<<std::endl;
        std::cout << "Presione Enter para continuar..." << std::endl;
        //std::cin.ignore();
        std::cin.get();
        system("clear");
        terminaAtaque = true;
        break;
      }
      else if (terriAtacoDesde->uniEjercito > 1)
      {

        // terriAtacoDesde->uniEjercito = terriAtacoDesde->uniEjercito - 1;
        std::cout << "El defensor gano el combate" << std::endl;
        std::cout << "El territorio " << terriAtacoDesde->nombreTerri << " ahora tiene " << terriAtacoDesde->uniEjercito << " tropas" << std::endl;
        do
        {
          std::cout << "Quieres seguir atacando? (1 = si, 2 = no) ";
          std::cin >> confirmOAtaque;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (confirmOAtaque < 1 || confirmOAtaque > 2);
        if (confirmOAtaque == 2)
        {
          terminaAtaque = true;
          break;
        }
      }
    }
  }
}

void Partida::guardarPartida(std::string nombreArchivo)
{
  // crear un archivo.txt con el nombre que recibe por parametro
  std::ofstream archivoDePartida(nombreArchivo + ".txt");
  std::queue<Jugador *> jugadoresTemp = jugadores; // Copia la cola original

  if (!archivoDePartida.is_open())
  {
    std::cout << "No se pudo abrir el archivo" << std::endl;
  }
  else
  {
    std::cout << "El archivo se creo correctamente" << std::endl;
  }

  archivoDePartida << "Partida de Risk" << std::endl;
  archivoDePartida << std::endl;

  // Guardar la informacion de los jugadores
  while (!jugadoresTemp.empty())
  {

    archivoDePartida << "Jugador: " << jugadoresTemp.front()->color << std::endl;

    // Guardar los territorios del jugador y cuantas tropas tiene en cada uno
    for (Continente *contiObj : continentes)
    {
      for (Territorio *terriObj : contiObj->territorios)
      {
        if (jugadoresTemp.front()->color == terriObj->duenoAct->color)
        {
          archivoDePartida << "Contienente: " << contiObj->nombreCont << std::endl;
          archivoDePartida << "Territorio:" << terriObj->nombreTerri << std::endl;
          archivoDePartida << "Tropas:" << terriObj->uniEjercito << std::endl;
        }
      }
    }

    archivoDePartida << std::endl;
    jugadoresTemp.pop();
  }

  archivoDePartida.close();
}


void Partida::guardarCompimido(std::string nombreArchivo)
{
  std::ofstream archivoDePartida(nombreArchivo + ".bin", std::ios::binary);
  if (!archivoDePartida.is_open())
  {
    std::cout << "No se pudo abrir el archivo" << std::endl;
    return;
  }

  std::cout << "El archivo se creo correctamente" << std::endl;

  std::stringstream output;
  std::queue<Jugador *> jugadoresTemp = jugadores; // Copia la cola original
  while (!jugadoresTemp.empty())
  {

    output << "Jugador: " << jugadoresTemp.front()->color << std::endl;

    // Guardar los territorios del jugador y cuantas tropas tiene en cada uno
    for (Continente *contiObj : continentes)
    {
      for (Territorio *terriObj : contiObj->territorios)
      {
        if (jugadoresTemp.front()->color == terriObj->duenoAct->color)
        {
          output << "Contienente: " << contiObj->nombreCont << std::endl;
          output << "Territorio:" << terriObj->nombreTerri << std::endl;
          output << "Tropas:" << terriObj->uniEjercito << std::endl;
        }
      }
    }

    output << std::endl;
    jugadoresTemp.pop();
  }

  std::string resultado = output.str();

  // Calcular las frecuencias de los caracteres en 'resultado'
  const int maxCaracteres = 256;
  long frecuencias[maxCaracteres] = {0};
  for (char c : resultado)
  {
    frecuencias[static_cast<unsigned char>(c)]++;
  }

  HuffmanArbol arbolhuffman;
  arbolhuffman.generarArbol(const_cast<char *>(resultado.c_str()), frecuencias, maxCaracteres);

  // Cifrar el texto y obtener un vector de bytes
  std::vector<char> textoComprimido = arbolhuffman.cifrar(resultado);

  // Escribir los bytes directamente en el archivo
  archivoDePartida.write(textoComprimido.data(), textoComprimido.size());

  if (!archivoDePartida.good())
  {
    std::cout << "Error al escribir en el archivo" << std::endl;
  }
  else
  {
    std::cout << "El archivo fue guardado correctamente" << std::endl;
  }

  archivoDePartida.close();
}

void Partida::crearTablero()
{
  Tablero<std::string, int> tablero;

  tablero.insertarTerritorio(("Alaska"));
  tablero.insertarTerritorio(("Alberta"));
  tablero.insertarTerritorio(("America Central"));
  tablero.insertarTerritorio(("Estados Unidos Del Este"));
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
  tablero.insertarTerritorio(("Afganistan"));
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
  //?Conexiones de Ucrania con Europa Del Norte, Escandinavia, Europa Del Sur, Afganistan, Medio Oriente, Ural.
  tablero.InsertarCamino(("Ucrania"), ("Europa Del Norte"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Escandinavia"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Europa Del Sur"), 1);
  tablero.InsertarCamino(("Ucrania"), ("Afganistan"), 1);
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

  //?Conexiones de Afganistan con Ucrania, Medio Oriente, China, India, Ural.
  tablero.InsertarCamino(("Afganistan"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Afganistan"), ("Medio Oriente"), 1);
  tablero.InsertarCamino(("Afganistan"), ("China"), 1);
  tablero.InsertarCamino(("Afganistan"), ("India"), 1);
  tablero.InsertarCamino(("Afganistan"), ("Ural"), 1);
  //?Conexiones de China con Afganistan, India, Mongolia, Siam, Siberia, Ural.
  tablero.InsertarCamino(("China"), ("Afganistan"), 1);
  tablero.InsertarCamino(("China"), ("India"), 1);
  tablero.InsertarCamino(("China"), ("Mongolia"), 1);
  tablero.InsertarCamino(("China"), ("Siam"), 1);
  tablero.InsertarCamino(("China"), ("Siberia"), 1);
  tablero.InsertarCamino(("China"), ("Ural"), 1);
  //?Conexiones de India con Afganistan, China, Siam, Medio Oriente.
  tablero.InsertarCamino(("India"), ("Afganistan"), 1);
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
  //?Conexiones de Medio Oriente con Ucrania, Afganistan, India, Egipto, Europa Del Sur.
  tablero.InsertarCamino(("Medio Oriente"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Medio Oriente"), ("Afganistan"), 1);
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
  //?Conexiones de Ural con Ucrania, Afganistan, Siberia, China.
  tablero.InsertarCamino(("Ural"), ("Ucrania"), 1);
  tablero.InsertarCamino(("Ural"), ("Afganistan"), 1);
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

  std::cout<<std::endl;
  std::cout<<"El tablero ha sido creado"<<std::endl;
  std::cout<<std::endl;
  
}
