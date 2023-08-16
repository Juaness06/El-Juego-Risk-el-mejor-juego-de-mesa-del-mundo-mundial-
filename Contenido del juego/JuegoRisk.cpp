#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

bool empezado = false; // variable global que sirve para establecer si una partida ha sido iniciada; se inicializa en false y cambiaria a true una vez se inicialice una partida correctamente
bool finalizado; // variable global que siver para establecer si una partida ya ha finalizado


void iniciar_partida(); // funcion para inicializar una partida
bool tieneTerritoriosDisponibles(const std::vector<std::string>& continente); // funcion que verifica los territorios disponibles para la repaticion inicial

int main(int argc, char **argv) 
{
    std::string command; // variable tipo string que tomara valores ingresados por teclado; esta se utiliza para los comandos
    bool esta = false; // variable boolean que se utilizara para almacenar el valor que retornara una funcion que determina si un jugador esta "registrado" en una partida
    bool ver_turno =false; //variable booleana que se utilizara para determinar si el turno de un jugador especifico


    std::cout << "El presente juego fue realizado por los estudiantes de la carrera de ingenieria de sistemas: " << std::endl;
    std::cout << "----------Hermann David Hernandez Pinto ----- & ----- Juan Esteban Granada OBrien -----------" << std::endl;
    std::cout << std::endl;
    std::cout << "              RRRRRRRR        IIIIII        SSSS      KKKK  KKKK              " << std::endl;
    std::cout << "              RRRRRRRRR       IIIIII       SSSSSS     KKKK  KKKK              " << std::endl;
    std::cout << "               RR    RR         II        SSS  SS      KK  KKK                " << std::endl;
    std::cout << "               RR    RR         II        SSS          KK KKK                 " << std::endl;
    std::cout << "               RRRRRRR          II         SSSS        KKKKK	                " << std::endl;
    std::cout << "               RRRRRRR          II          SSSSS      KKKKK	                " << std::endl;
    std::cout << "               RR   RR          II            SSS      KK KKK	                " << std::endl;
    std::cout << "               RR    RR         II        SSS  SS      KK  KKK                " << std::endl;
    std::cout << "              RRRR  RRRR      IIIIII      SSS  SS     KKKK  KKKK              " << std::endl;
    std::cout << "              RRRR  RRRR      IIIIII       SSSSS      KKKK  KKKK              " << std::endl;
    std::cout << std::endl;
    std::cout << "Bienvvenido, recuerde que el juego funciona por comandos, si no sabe los comandos escriba ayuda" << std::endl;
    
    
    while (true) {
        std::cout << "$ "; // esto es para que el indicador de línea de comando sea $

        if (!std::getline(std::cin, command) || command == "salir") {
            // Si el usuario ingresa "exit", el programa finaliza el bucle y sale.
            break;
        }
        else if (command == "inicializar") {
            // Si el usuario ingresa "inicializar" pasa esto 
            if (empezado == true){
                // esto sucede cuando la partida ya habia sido inicializada
                std::cout <<"El juego ya ha sido inicializado" << std::endl;
            }else{
                // esto sucede cuando no habia una partida iniciada
                iniciar_partida(); // se llama a la funcion para incializar una partida
                std::cout<<"Se ha inizializado la partida correctamente"<<std::endl; // mensaje de confirmacion de inicializacion correcta
                empezado = true;
            }
        } 
        else if (command == "turno <id_jugador>"){
            // Esto sucede cuando no se ha inicializado una partida
            if (empezado == false){
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (empezado == true && finalizado == true){
                // esto sucede cuando se trata de usar este comando y la partida ya ha finalizado
                std::cout <<"Esta partida ya tuvo un ganador" << std::endl;
            }

            if (empezado == true && esta==false){
                // esto sucede cuando se trata de usar este comando pero el solicitado no esta registrado en la partida iniciada 
                std::cout <<"El jugador <id_jugador> no forma parte de esta partida" << std::endl;
            }

            if (empezado == true && ver_turno==false){
                // esto es cuando el jugador buscado esta registrado en la partida inicada pero no es su turno
                std::cout <<"No es el turno del jugador <id_jugador>" << std::endl;
            }
            if (empezado == true && ver_turno==true){
                // esto es cuando el jugador buscado esta registrado en la partida inicada y es su turno
                std::cout <<"El turno del jugador <id_jugador> ha terminado." << std::endl;
            }
        }
        else if (command == "ayuda"){
            // se muestra la lista de comandos 
            std::cout << " ------------------ LISTA DE COMANDOS ------------------"<< std::endl;
            std::cout << "| -> inicializar                                        |" << std::endl;
            std::cout << "| -> guardar <nombre_archivo>                           |" << std::endl;
            std::cout << "| -> guardar_comprimido <nombre_archivo>                |" << std::endl;
            std::cout << "| -> inicializar <nombre_archivo>                       |" << std::endl;
            std::cout << "| -> costo_conquista <territorio>                       |" << std::endl;
            std::cout << "| -> conquista_mas_barata                               |" << std::endl;
            std::cout << "| -> turno <id_jugador>                                 |" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;          
        }
        else if (command == "guardar <nombre_archivo>")
        {
            if (empezado == false){
                // esto aparece cuando se trata de usar el comando y no se ha inializado una partida
                // esto sucede porque no se puede guardar una partida que no se ha iniciado (no hay nada que guardar)
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (empezado == true){
                // esto aparece caundo se trata de usar el comando y si se ha inicializado una partida
                // esto si se deja gurdar porque ahora si hay algo que guardar "salvar" para poder recuperar la partida
                std::cout <<"La partida ha sido guardada correctamente" << std::endl;
            }
            
            // Para el caso (Error al guardar) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if (command == "guardar_comprimido <nombre_archivo>")
        {
            if (empezado == false){
                // esto aparece cuando se trata de usar el comando y no se ha inializado una partida
                // esto sucede porque no se puede guardar una partida que no se ha iniciado (no hay nada que guardar) 
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (empezado == true){
                // esto aparece caundo se trata de usar el comando y si se ha inicializado una partida
                // esto si se deja gurdar porque ahora si hay algo que guardar "salvar" para poder recuperar la partida
                std::cout <<"La partida ha sido codificada y guardada correctamente" << std::endl;
            }

            // Para el caso (Error al codificar y/o guardar) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if (command == "inicializar <nombre_archivo>")
        {
            if (empezado == false){
                // aqui se debe llamar una funcion o desarrollar un proceso para recuperar una partida ya iniciada y guardada previamente
                std::cout <<"El juego ya ha sido inicializado" << std::endl; // mensaje de confirmacion de que la partida solicitada ya fue inicializada
            }

            // Para el caso (Archivo vacío o incompleto) como aun no se han creado los archivos para guardar
            // para la entrega cero se dejo esto comentado

        }
        else if(command == "costo_conquista <territorio>")
        {
            if (empezado == false){
                // esto aparece cuando se trata de uasr el comando y la partida no habia empezado
                // esto es asi ya que no se puede calcular el costo de una conquista sin la informacion de una partida
                std::cout <<"Esta partida no ha sido inicializada correctament" << std::endl;
            }
            if (finalizado == true){
                // esto aparece cuando se trarta de usar el comando y la partida ya ha finalizado "terminado"
                // esto es asi ya que  no se puede calcular el costo de una conquista si la partida ya ha terminado
                std::cout <<"Esta partida ya tuvo un ganador" << std::endl;
            }
            if (empezado == true){
                // aqui se debe llamar una funcion o desarrollar un proceso para realizar los calculos para saber el costo de conquista de un territorio especifico dado por el usuario
                // el siguiente cout seria el foramato del mensaje de salida que tocaria mostrar en pantalla
                std::cout <<"Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército" << std::endl;
                // esto solo se puede hacer cuando la partida este mepezada y en curso ya que es la unica forma de tener los datos para hacer los calculos 
            }
        }
        else if (command == "conquista_mas_barata")
        {
            if (empezado == false){
                // esto aparece cuando se trata de uasar el comando y la partida no habia empezado
                // esto es asi ya que no se puede calcular la conquista mas barata sin la informacion de una partida
                std::cout <<"Esta partida no ha sido inicializada correctamente" << std::endl;
            }
            if (finalizado == true){
                // esto aparece cuando se trarta de usar el comando y la partida ya ha finalizado "terminado"
                // esto es asi ya que  no se puede calcular la conquista mas varata de una partida ya ha terminado
                std::cout <<"Esta partida ya tuvo un ganador" << std::endl;
            }
            if (empezado == true){
                // aqui se debe llamar una funcion o desarrollar un proceso para saber cual es la conquista mas varata
                // el siguiente cout seria el foramato del mensaje de salida que tocaria mostrar en pantalla
                std::cout <<"La conquista más barata es avanzar sobre el territorio <territorio_1> desde el territorio <territorio_2>. Para conquistar el territorio <territorio_1>, debe atacar desde <territorio_2>, pasando por los territorios <territorio_3>, <territorio_4>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército" << std::endl;
            }
        }
        else 
        {
            // esto es para cuando se ingrsa un comando invalido
            std::cout << "Comando desconocido. Inténtalo nuevamente" << std::endl;
        }
    }
}

void iniciar_partida() // funcion para incilizar la partida 
{
    int conta_terr = 0; // contador para determinar cuantos territorios se han repartido
    int cant_j = 0; // variable que tomara el valor de la cantidad de jugadores 
    int eleccion1; // variable que toma los valores que representan el contienete elegido en cierto momento
    int eleccion2; // variable que toma los valores que representan el territorio elegido en cierto momento

    // vectores de strings que lamacenan los territorios disponibles de cada continente
    std::vector<std::string> AmericaNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Orientales"};
    std::vector<std::string> AmericaSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
    std::vector<std::string> Europa = {"Gran Bretaña", "Islandia", "Europa del Norte", "Escandinavia", "Europa del Sur", "Ucrania", "Europa Occidental"};
    std::vector<std::string> Africa = {"Congo", "África Oriental", "Egipto", "Madagascar", "África del Norte", "África del Sur"};
    std::vector<std::string> Asia = {"Afghanistán", "China", "India", "Irkutsk", "Japón", "Kamchatka", "Medio Oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
    std::vector<std::string> Australia = {"Australia","Indonesia","Nueva Guinea","Australia Occidental"};

    do // ciclo para asegurarnos se que la cantidad de los jugadores ingresada esta entre 3 y 6 ni mas ni menos
    {
        std::cout << "Cuantas personas van a jugar? (min 3 - max 6): ";
        std::cin >> cant_j;
    } while (cant_j < 3 || cant_j > 6);

    std::vector<std::string> jugadores(cant_j); // se crea el vector jugadores que almacenara los nombres "id" de los jugadores 

    for (int i = 0; i < cant_j; i++) // este ciclo lo utilizamos para el ingreso y registro de los nombres de los jugadores 
    {
        std::cout << "Jugador " << i + 1 << " ingrese su nombre: ";
        std::cin >> jugadores[i];
    }

    while (conta_terr<42) // este ciclo se utiliza para realizar las preguntas para la reparticion inicial de los territorios. Este ciclo termina cuando todos los territorios han sido repartidos
    {
        // se muestra el menu de las opciones de continentes
        std::cout << "Elija uno de los siguientes continetes:" << std::endl;
        std::cout << "1. America del Norte" << std::endl;
        std::cout << "2. América del Sur" << std::endl;
        std::cout << "3. Europa" << std::endl;
        std::cout << "4. Africa" << std::endl;
        std::cout << "5. Asia" << std::endl;
        std::cout << "6. Australia" << std::endl;
        std::cout << "Ingrese el número del continente seleccionado: ";
        std::cin >> eleccion1;

        switch (eleccion1) // se utiliza este switch para mostrar los territorios disponibles del continente seleccionado y que el usuario elija uno
        {
        case 1:
        {
            if (!tieneTerritoriosDisponibles(AmericaNorte)) {
                // esto sucede cuando el usuario elige un contienente que ya no tiene territorios disponibles
                std::cout << "No hay territorios disponibles en América del Norte." << std::endl;
                break;
            }
            // cuando se elige un contienente que SI tiene territorios disponibles 
            std::cout << "Territorios disponibles en América del Norte:" << std::endl;
            for (size_t j = 0; j < AmericaNorte.size(); j++) // se imprimen los territorios disponibles del continente eligido
            {
                std::cout << j + 1 << ". " << AmericaNorte[j] << std::endl;
            }

            std::cout << "Ingrese el número del territorio seleccionado: "; // se pregunta por el territorio que se quiere elegir
            std::cin >> eleccion2;

            if (eleccion2 >= 1 && eleccion2 <= AmericaNorte.size())
            {
                // si el identificador del territorio ingresado es valido pasa esto 
                std::cout << "Territorio elegido: " << AmericaNorte[eleccion2 - 1] << std::endl; // se muestra en pantalla el territorio elegido
                AmericaNorte.erase(AmericaNorte.begin() + eleccion2 - 1); // se borra del arreglo de territorios disponibles de este continente el territorio elegido por el usuario 
                conta_terr++; // se umenta el contador de territorios asignados
            }
            else
            {
                // esto sucede cuando el identificador del territorio ingresado NO es valido
                std::cout << "Número de territorio inválido." << std::endl;
            }

            break;
        }

        case 2:
        {
            if (!tieneTerritoriosDisponibles(AmericaSur)) {
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
            
            if (!tieneTerritoriosDisponibles(Europa)) {
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
            if (!tieneTerritoriosDisponibles(Africa)) {
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
            if (!tieneTerritoriosDisponibles(Asia)) {
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
            if (!tieneTerritoriosDisponibles(Australia)) {
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

bool tieneTerritoriosDisponibles(const std::vector<std::string>& continente) {
    return !continente.empty();
}
