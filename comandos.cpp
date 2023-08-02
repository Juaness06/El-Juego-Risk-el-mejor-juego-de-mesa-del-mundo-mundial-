#include <iostream>
#include <string>
#include <map>

void iniciar_partida(std::string command);
int main()
{

    std::string command;
    int n, n2;
    int num_jugadores;

    std::cout << "El presente juego fue realizado por los estudiantes de la carrera de ingenieria de sistemas: " << std::endl;
    std::cout << "----------Hermann David Hernandez Pinto ----- & ----- Juan Esteban Granada OBrien -----------" << std::endl;
    std::cout << std::endl;
    std::cout << "              RRRRRRRR        IIIIII        SSSS      KKKK  KKKK              " << std::endl;
    std::cout << "              RRRRRRRRR       IIIIII       SSSSSS     KKKK  KKKK              " << std::endl;
    std::cout << "               RR    RR         II        SSS  SS      KK  KKK                " << std::endl;
    std::cout << "               RR    RR         II        SSS          KK KKK                 " << std::endl;
    std::cout << "               RRRRRRR          II         SSSS        KKKKK	               " << std::endl;
    std::cout << "               RRRRRRR          II          SSSSS      KKKKK	               " << std::endl;
    std::cout << "               RR   RR          II            SSS      KK KKK	               " << std::endl;
    std::cout << "               RR    RR         II        SSS  SS      KK  KKK                " << std::endl;
    std::cout << "              RRRR  RRRR      IIIIII      SSS  SS     KKKK  KKKK              " << std::endl;
    std::cout << "              RRRR  RRRR      IIIIII       SSSSS      KKKK  KKKK              " << std::endl;
    std::cout << std::endl;

    do
    {
        std::cout << "$ ";
        std::cin >> command;

        if (command == "ayuda" || "inicializar" || "inicializar <nombre_del_archivo" || "guardar_comprimido <nombre_del_archivo"||"salir")
        {
            if (command == "ayuda")
                n = 1;
            else if (command == "inicializar")
                n = 2;
            else if (command == "inicializar <nombre_del_archivo")
                n = 3;
            else if (command == "guardar_comprimido <nombre_del_archivo")
                n = 4;
        

            switch (n)
            {
            case 1:
                std::cout << "\nLISTA DE COMANDOS\n"
                          << std::endl;
                std::cout << "inicializar" << std::endl;
                std::cout << "guardar <nombre_del_archivo>" << std::endl;
                std::cout << "guardar_comprimido <nombre_archivo>" << std::endl;
                std::cout << "inicializar <nombre_archivo>" << std::endl;
                std::cout << "costo_conquista <territorio>" << std::endl;
                std::cout << "conquista_mas_barata" << std::endl;
                std::cout << "turno <nombre_del_jugador>" << std::endl;
                break;
            case 2:
                std::cout << "Se ha inizializado la partida correctamente" << std::endl;
                iniciar_partida(command);
                break;
            case 3:
                std::cout << "Se ha inicializado la partida con el archivo  x" << std::endl;
                break;
            case 4:
                std::cout<<"La partida ha sido codificada y guardada correctamente"<<std::endl;
                break;
            default:
                system("");
                break;
            }
        }
        else if(command == "turno ")
        {
            std::cout << "Esta partida no ha sido inicializada correctamente" << std::endl;
        }

    } while (command != "salir");

    system("pause");
    return 0;
}

void iniciar_partida(std::string command)
{
    int num_jugadores;
    std::cout << "Ingrese el numero de jugadores: ";
    std::cin >> num_jugadores;
    std::cout << "Se ha ingresado " << num_jugadores << " jugadores" << std::endl;
    std::cout << "Ingrese el nombre de los jugadores: " << std::endl;
    std::string jugadores[num_jugadores];
    for (int i = 0; i < num_jugadores; i++)
    {
        std::cout << "Jugador: ";
        std::cin >> jugadores[i];
    }
    std::cout << "Los jugadores son: " << std::endl;
    for (int i = 0; i < num_jugadores; i++)
    {
        std::cout << jugadores[i] << std::endl;
    }
    std::cout << "Escoger territorios: " << std::endl;
    std::cout << "Territorios disponibles: " << std::endl;
}
