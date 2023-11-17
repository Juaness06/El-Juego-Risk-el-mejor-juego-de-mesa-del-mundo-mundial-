#include "Tablero.h"

#include <iostream>
#include <stack>
#include <limits>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>

template <class T, class U>
bool Tablero<T, U>::buscarTerritorio(T territorio)
{
    if (territorios.size() == 0)
    {
        return false;
    }
    for (int i = 0; i < this->territorios.size(); i++)
    {
        if (this->territorios[i] == territorio)
        {
            return true;
        }
    }
    return false;
}

template <class T, class U>
int Tablero<T, U>::indiceTerritorio(T territorio)
{
    int indice = -1;
    for (int i = 0; i < this->territorios.size(); i++)
    {
        if (this->territorios[i] == territorio)
        {
            indice = i;
        }
    }
    return indice;
}

template <class T, class U>
bool Tablero<T, U>::insertarTerritorio(T territorio)
{

    if (buscarTerritorio(territorio))
    {
        return false;
    }
    this->territorios.push_back(territorio);

    int n = this->territorios.size();
    this->matriz_adyacencia.resize(n);
    for (int i = 0; i < this->matriz_adyacencia.size(); i++)
        this->matriz_adyacencia[i].resize(n);
    return true;
}

template <class T, class U>
bool Tablero<T, U>::InsertarCamino(T territorio1, T territorio2, U peso)
{
    if (!buscarTerritorio(territorio1))
    {
        return false;
    }
    if (!buscarTerritorio(territorio2))
    {
        return false;
    }

    int n1 = indiceTerritorio(territorio1);
    int n2 = indiceTerritorio(territorio2);

    this->matriz_adyacencia[n1][n2] = peso;
    return true;
}

template <class T, class U>
bool Tablero<T, U>::buscarCamino(T territorio1, T territorio2)
{

    if (!buscarTerritorio(territorio1))
    {
        return false;
    }
    if (!buscarTerritorio(territorio2))
    {
        return false;
    }

    int n1 = indiceTerritorio(territorio1);
    int n2 = indiceTerritorio(territorio2);
    return this->matriz_adyacencia[n1][n2] != 0; //
}

template <class T, class U>
U Tablero<T, U>::valorConexion(T territorio1, T territorio2)
{
    if (!buscarTerritorio(territorio1))
    {
        return 0;
    }
    if (!buscarTerritorio(territorio2))
    {
        return 0;
    }

    int n1 = indiceTerritorio(territorio1);
    int n2 = indiceTerritorio(territorio2);
    return this->matriz_adyacencia[n1][n2];
}

template <class T, class U>
void Tablero<T, U>::imprimirMatriz()
{
    std::cout << "\t\t";
    cout << "\n\nMatriz de adyacencia:\n\n";
    for (int i = 0; i < this->matriz_adyacencia.size(); i++){
        std::cout << " " << i;
    }
    std::cout << "\n";
    for (int i = 0; i < this->matriz_adyacencia.size(); i++)
    {
        std::cout << "  ";
    }
    std::cout << "\n";
    for (int i = 0; i < this->matriz_adyacencia.size(); i++)
    {
        if (i < 10)
        {
            std::cout << i << "  ";
        }
        else
        {
            std::cout << i << " ";
        }
        for (int j = 0; j < this->matriz_adyacencia.size(); j++)
        {
            std::cout << this->matriz_adyacencia[i][j] << "  ";
        }
        std::cout << "\n";
    }        
}

template <class T, class U>
void Tablero<T, U>::prim(T territorio)
{
    vector<T> visitados;
    vector<T> componente = componenteVertice(territorio);
    vector<T> noVisitados = componente;
    vector<pair<T, T>> aristas;
    // Se agrega el nodo inicial a visitados
    visitados.push_back(territorio);
    // Se elimina el nodo inicial de noVisitados
    noVisitados.erase(noVisitados.begin() + indiceVertice(territorio));
    T nuevo;
    T actual;
    // Mientras no se hayan visitado todos los nodos
    while (visitados.size() != componente.size())
    {
        // Se inicializa el menor valor de conexion con el maximo valor de U
        U menor = numeric_limits<U>::max();
        // Se recorren los nodos visitados
        for (int i = 0; i < visitados.size(); i++)
        {
            // Se recorren los nodos no visitados
            for (int j = 0; j < noVisitados.size(); j++)
            {
                // Si existe una conexion entre los nodos
                if (buscarArista(visitados[i], noVisitados[j]))
                {
                    // Si el valor de la conexion es menor al menor valor de conexion
                    if (valorConexion(visitados[i], noVisitados[j]) < menor)
                    {
                        // Se actualiza el menor valor de conexion
                        menor = valorConexion(visitados[i], noVisitados[j]);
                        // Se actualizan los nodos visitado y no visitado
                        actual = visitados[i];
                        nuevo = noVisitados[j];
                    }
                }
            }
        }
        // Se agrega el nodo no visitado a visitados
        visitados.push_back(nuevo);
        // Se elimina el nodo no visitado de noVisitados
        auto it = find(noVisitados.begin(), noVisitados.end(), nuevo);
        noVisitados.erase(it);
        aristas.push_back(make_pair(actual, nuevo));
    }

    // Se imprime la ruta del arbol de expansion minima
    cout << "\n\nRuta del árbol de expansión mínima generada por Prim:\n\n";
    for (int i = 0; i < aristas.size(); i++)
    {
        cout << "(" << aristas[i].first << ", " << aristas[i].second << ") ";
    }
}

template <class T, class U>
void Tablero<T, U>::dijkstra(T territorio)
{
    T territorioActual = territorio;
    vector<T> distancias;
    vector<T> visitados;
    vector<T> componente = componenteTerritorio(territorio);
    vector<T> noVisitados = componenteTerritorio(territorio);
    vector<T> prev(componente.size());

    // Se inicializan las distancias en infinito
    for (int i = 0; i < componente.size(); i++)
    {
        distancias.push_back(numeric_limits<U>::max());
    }
    // Se inicializa la distancia del territorio inicial en 0
    distancias[indiceTerritorio(territorioActual)] = 0;

    // Mientras no se hayan visitado todos los nodos
    while (!noVisitados.empty())
    {
        

        // Se inicializa la menor distancia con el maximo valor de U
        U menor = numeric_limits<U>::max();
        // Se recorren los nodos no visitados
        for (int i = 0; i < noVisitados.size(); i++)
        {
            // Si la distancia del nodo no visitado es menor a la menor distancia
            if (distancias[indiceTerritorio(noVisitados[i])] < menor)
            {
                // Se actualiza la menor distancia
                menor = distancias[indiceTerritorio(noVisitados[i])];
                // Se actualiza el nodo visitado
                territorioActual = noVisitados[i];
            }
        }

        // Se agrega el nodo visitado a visitados
        visitados.push_back(territorioActual);
        // Se elimina el nodo visitado de noVisitados
        // noVisitados.erase(remove(noVisitados.begin(), noVisitados.end(), verticeActual), noVisitados.end());
        auto it = find(noVisitados.begin(), noVisitados.end(), territorioActual);
        noVisitados.erase(it);

        // Se recorren los vecinos del nodo visitado
        for (int i = 0; i < componente.size(); i++)
        {

            // Si existe una conexion entre el nodo visitado y el vecino
            if (buscarArista(territorioActual, componente[i]))
            {

                // Si la distancia del nodo visitado es mayor
                //  a la del vecino mas la distancia entre el nodo visitado y el vecino
                U distanciaTerritorio = distancias[indiceTerritorio(territorioActual)];
                U distanciaVecino = distancias[indiceTerritorio(componente[i])];
                U nuevaDistancia = distanciaTerritorio + valorConexion(territorioActual, componente[i]);

                if (distanciaVecino > nuevaDistancia)
                {
                    // Se actualiza la distancia del nodo visitado
                    distancias[indiceTerritorio(componente[i])] = nuevaDistancia;
                    prev[indiceTerritorio(componente[i])] = territorioActual;
                }
            }
        }
    }
    cout << "\n\nRutas generadas con Dijkstra:\n";
    for (int i = 0; i < visitados.size(); i++)
    {
        if (visitados[i] != territorio)
        {
            cout << "\n"
                 << territorio << " -> " << visitados[i] << ": ";
            stack<T> ruta;
            territorioActual = visitados[i];

            while (territorioActual != territorio)
            {
                ruta.push(territorioActual);
                territorioActual = prev[indiceTerritorio(territorioActual)];
            }

            cout << "(" << territorio << ") ";
            while (!ruta.empty())
            {
                cout << "(" << ruta.top() << ") ";
                ruta.pop();
            }
        }
    }
}
