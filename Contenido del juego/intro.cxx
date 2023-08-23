#include "intro.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

bool esta = false;
bool ver_turno =false;
bool empezado = false;
bool finalizado;

bool tieneTerriDisp(const std::vector<std::string>& continente);

void Intro::titulo()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "El presente juego fue realizado por los estudiantes de la carrera de ingenieria de sistemas: " << std::endl;
    std::cout << "----------Hermann David Hernandez Pinto ----- & ----- Juan Esteban Granada OBrien -----------" << std::endl;
    std::cout << std::endl;
    std::cout << "                    RRRRRRRR        IIIIII        SSSS      KKKK  KKKK                       " << std::endl;
    std::cout << "                    RRRRRRRRR       IIIIII       SSSSSS     KKKK  KKKK                       " << std::endl;
    std::cout << "                     RR    RR         II        SSS  SS      KK  KKK                         " << std::endl;
    std::cout << "                     RR    RR         II        SSS          KK KKK                          " << std::endl;
    std::cout << "                     RRRRRRR          II         SSSS        KKKKK	                       " << std::endl;
    std::cout << "                     RRRRRRR          II          SSSSS      KKKKK	                       " << std::endl;
    std::cout << "                     RR   RR          II            SSS      KK KKK	                       " << std::endl;
    std::cout << "                     RR    RR         II        SSS  SS      KK  KKK                         " << std::endl;
    std::cout << "                    RRRR  RRRR      IIIIII      SSS  SS     KKKK  KKKK                       " << std::endl;
    std::cout << "                    RRRR  RRRR      IIIIII       SSSSS      KKKK  KKKK                       " << std::endl;
    std::cout << std::endl;
    std::cout << "----------------------------------- RISK TAKER - FUN MAKER ----------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void Intro::comandos()
{
    std::string command;
    bool esta = false;
    bool ver_turno =false;

    while (true)
    {
        std::cout << "$ "; // Indicador de línea de comando
        std::getline(std::cin, command);

        if (command == "ayuda")
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << " ------------------ LISTA DE COMANDOS ------------------"<< std::endl;
            std::cout << "| -> inicializar                                        |" << std::endl;
            std::cout << "| -> guardar <nombre_del_archivo>                       |" << std::endl;
            std::cout << "| -> guardar_comprimido <nombre_archivo>                |" << std::endl;
            std::cout << "| -> costo_conquista <territorio>                       |" << std::endl;
            std::cout << "| -> conquista_mas_barata                               |" << std::endl;
            std::cout << "| -> turno <nombre_del_jugador>                         |" << std::endl;
            std::cout << "| -> salir                                              |" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << " ----------- SI NO SABE COMO USAR UN COMANDO -----------"<< std::endl;
            std::cout << "| -> inicializar?                                       |" << std::endl;
            std::cout << "| -> guardar?                                           |" << std::endl;
            std::cout << "| -> guardar_comprimido?                                |" << std::endl;
            std::cout << "| -> costo_conquista?                                   |" << std::endl;
            std::cout << "| -> conquista_mas_barata?                              |" << std::endl;
            std::cout << "| -> turno?                                             |" << std::endl;
            std::cout << "| -> salir?                                             |" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else if (command == "inicializar?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando inicializar se puede utilizar de dos formas:" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << " - Para empezar-crear una partida nueva (desde cero):" << std::endl;
            std::cout << " inicializar" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para continuar una partida ya empezada (ya guardada):" << std::endl;
            std::cout << "inicializar <nombre_archivo>" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (command == "inicializar") {
            if (empezado == true){
                std::cout <<"El juego ya ha sido inicializado" << std::endl;
            }else{
                Inicializar::nueva();
                std::cout<<"Se ha inizializado la partida correctamente"<<std::endl;
                empezado = true;
            }
        } 
        else if (command == "inicializar <nombre_archivo>")
        {
            if (empezado == false){
                std::cout <<"El juego ya ha sido inicializado" << std::endl;
            }

            // Para el caso (Archivo vacío o incompleto) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if (command == "guardar?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando guardar sirve para: que el estado actual del " << std::endl;
            std::cout << "juego sea guardado en un archivo de texto" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para utilizarlo escriba: guardar " << std::endl;
            std::cout << "  seguido del nombre de el nombre del archivo entre <> " << std::endl;
            std::cout << "Ejemplo: " << std::endl;
            std::cout << "guardar <nombre_del_archivo>" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (command == "guardar <nombre_archivo>")
        {
            if (empezado == false){
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (empezado == true){
                std::cout <<"La partida ha sido guardada correctamente" << std::endl;
            }
            
            // Para el caso (Error al guardar) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if (command == "guardar_comprimido?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando guardar_comprimido sirve para: que el estado " << std::endl;
            std::cout << "actual del juego sea guardado en un archivo de binario  " << std::endl;
            std::cout << "con la información comprimida" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para utilizarlo escriba: guardar_comprimido " << std::endl;
            std::cout << "  seguido del nombre de el nombre del archivo entre <> " << std::endl;
            std::cout << "Ejemplo: " << std::endl;
            std::cout << "guardar_comprimido <nombre_del_archivo>" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (command == "guardar_comprimido <nombre_archivo>")
        {
            if (empezado == false){
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (empezado == true){
                std::cout <<"La partida ha sido codificada y guardada correctamente" << std::endl;
            }

            // Para el caso (Error al codificar y/o guardar) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if (command == "costo_conquista?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando costo_conquista sirve para: calcular el costo" << std::endl;
            std::cout << "y la secuencia de territorios a ser conquistados para   " << std::endl;
            std::cout << "lograr controlar el territorio dado por el usuario." << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para utilizarlo escriba: costo_conquista " << std::endl;
            std::cout << "  seguido del nombre del territorio entre <> " << std::endl;
            std::cout << "Ejemplo: " << std::endl;
            std::cout << "costo_conquista <territorio>" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if(command == "costo_conquista <territorio>")
        {
            if (empezado == false){
                std::cout <<"Esta partida no ha sido inicializada correctament" << std::endl;
            }
            if (finalizado == true){
                std::cout <<"Esta partida ya tuvo un ganador" << std::endl;
            }
            if (empezado == true){
                // Se realizan los calculos para saber el costo de conquista de un territorio especifico dado por el usuario
                std::cout <<"Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército" << std::endl;
            }
        }
        else if (command == "conquista_mas_barata?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando conquista_mas_barata sirve para: de todos los" << std::endl;
            std::cout << "territorios posibles, calcular aquel que pueda implicar " << std::endl;
            std::cout << "un menor número de unidades de ejército perdidas." << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para utilizarlo escriba:" << std::endl;
            std::cout << "conquista_mas_barata" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (command == "conquista_mas_barata")
        {
            if (empezado == false){
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (finalizado == true){
                std::cout <<"Esta partida ya tuvo un ganador" << std::endl;
            }
            if (empezado == true){
                // Se realizan los calculos para saber cual es la conquista mas varata
                std::cout <<"La conquista más barata es avanzar sobre el territorio <territorio_1> desde el territorio <territorio_2>. Para conquistar el territorio <territorio_1>, debe atacar desde <territorio_2>, pasando por los territorios <territorio_3>, <territorio_4>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército" << std::endl;
            }
        }
        else if (command == "salir?") 
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "El comando salir sirve para: termina la ejecución de    " << std::endl;
            std::cout << "la aplicación.                                          " << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "- Para utilizarlo escriba:" << std::endl;
            std::cout << "salir" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (command == "salir") 
        {
            // Si el usuario ingresa "exit", el programa finaliza el bucle y sale.
            break;
        }
        else 
        {
            std::cout << "Comando desconocido. Inténtelo nuevamente" << std::endl;
            std::cout << "Para " << std::endl;
        }
    }
}

void Inicializar::nueva()
{
    int conta_terr = 0;
    int cant_j = 0;
    int eleccion1;
    int eleccion2;

    std::vector<std::string> AmericaNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Orientales"};
    std::vector<std::string> AmericaSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
    std::vector<std::string> Europa = {"Gran Bretaña", "Islandia", "Europa del Norte", "Escandinavia", "Europa del Sur", "Ucrania", "Europa Occidental"};
    std::vector<std::string> Africa = {"Congo", "África Oriental", "Egipto", "Madagascar", "África del Norte", "África del Sur"};
    std::vector<std::string> Asia = {"Afghanistán", "China", "India", "Irkutsk", "Japón", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
    std::vector<std::string> Australia = {"Australia","Indonesia","Nueva Guinea","Australia Occidental"};

    do
    {
        std::cout << "Cuantas personas van a jugar? (min 3 - max 6): ";
        std::cin >> cant_j;
    } while (cant_j < 3 || cant_j > 6);

    std::vector<std::string> jugadores(cant_j);

    for (int i = 0; i < cant_j; i++)
    {
        std::cout << "Jugador " << i + 1 << " ingrese su nombre: ";
        std::cin >> jugadores[i];
    }

    //for (int i = 0; i < 42; i++) // Toca cambiarlo porque si 
    while (conta_terr<42)
    {
        std::cout << "Elija uno de los siguientes continetes:" << std::endl;
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
            if (!tieneTerriDisp(AmericaNorte)) {
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
            if (!tieneTerriDisp(AmericaSur)) {
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
            
            if (!tieneTerriDisp(Europa)) {
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
            if (!tieneTerriDisp(Africa)) {
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
            if (!tieneTerriDisp(Asia)) {
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
            if (!tieneTerriDisp(Australia)) {
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
            std::cout << "Continente no válido. Intente nuevamente." << std::endl;
            break;
        }
    }
}

bool tieneTerriDisp(const std::vector<std::string>& continente) {
    return !continente.empty();
}
