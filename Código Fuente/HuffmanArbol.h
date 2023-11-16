#ifndef HUFFMANARBOL_H_INCLUDED
#define HUFFMANARBOL_H_INCLUDED

#include "HuffmanNodo.h"
#include <utility>
#include <vector>
#include <queue>
#include <iostream>

class HuffmanArbol
{
private:
    HuffmanNodo *raiz;
    std::vector<std::pair<char, std::string>> codigos;

public:
    HuffmanArbol();
    void generarArbol(char dato[], long freq[], int size);
    struct comparar;
    void guardarCodigos(HuffmanNodo *inicio, std::string str);
    void imprimirCodigos();
    std::string obtenerCodigo(char caracter);
    std::vector<char> cifrar(std::string sec); //TODO cambios aca
    std::string desCifrar(std::string cif, long longiSec);
    HuffmanNodo *deCodificar(HuffmanNodo *nodo, char dir, int &cont, std::string &des);
    HuffmanNodo *getRaiz();
};

#include "HuffmanArbol.hxx"
#endif 
