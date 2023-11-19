#ifndef __TABLERO__H__
#define __TABLERO__H__

#include <iostream>
#include <vector>

using namespace std;

template <class T, class U>
class Tablero
{
  public:
    std::vector<T> territorios;
    std::vector<std::vector<U>> matriz_adyacencia;
  public:
    bool buscarTerritorio(T territorio);
    int indiceTerritorio(T territorio);
    bool insertarTerritorio(T territorio);
    bool InsertarCamino(T territorio1, T territorio2, U peso);
    bool buscarCamino(T territorio1, T territorio2);
    U valorConexion(T territorio1, T territorio2);
    vector<T> componenteTerritorio(T vertice);
    void imprimirMatriz();
    void prim(T territorio);
    std::vector< std::pair<T, T> > dijkstra(T territorio);
    
};

#include "Tablero.hxx"

#endif