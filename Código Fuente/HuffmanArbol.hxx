#include "HuffmanArbol.h"

HuffmanArbol::HuffmanArbol()
{
    this->raiz = NULL;
}
struct HuffmanArbol::comparar
{

    bool operator()(HuffmanNodo *l, HuffmanNodo *r)

    {
        return (l->obtenerFreq() > r->obtenerFreq());
    }
};
void HuffmanArbol::generarArbol(char dato[], long freq[], int tama)
{
    HuffmanNodo *left, *right, *top;

    priority_queue<HuffmanNodo *, vector<HuffmanNodo *>, comparar> minHeap;
    for(int i = 0; i < minHeap.size();++i){
        minHeap.pop();
    }
    for (int i = 0; i < tama; i++)
    {
        minHeap.push(new HuffmanNodo(dato[i], freq[i]));
    }
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();
        unsigned int nuevaFreq = left->obtenerFreq() + right->obtenerFreq();
        top = new HuffmanNodo(' ', nuevaFreq);
        top->fijarHijoDer(right);
        top->fijarHijoIzq(left);
        minHeap.push(top);
    }
    this->raiz = minHeap.top();
    guardarCodigos(this->raiz, "");
}
void HuffmanArbol::guardarCodigos(HuffmanNodo *inicio, string str)
{
    if (!inicio)
        return;
    if (inicio->obtenerDato() != ' ')
    {
        codigos.push_back(make_pair(inicio->obtenerDato(), str));
    }
    this->guardarCodigos(inicio->obtenerHijoIzq(), str + "0");
    this->guardarCodigos(inicio->obtenerHijoDer(), str + "1");
}
void HuffmanArbol::imprimirCodigos()
{
    vector<pair<char, string>>::iterator it;
    for (it = codigos.begin(); it != codigos.end(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }
}
string HuffmanArbol::obtenerCodigo(char caracter)
{
    string codigo = "";
    bool encontrado = false;
    vector<pair<char, string>>::iterator it;
    for (it = codigos.begin(); it != codigos.end() && !encontrado; ++it)
    {
        if (it->first == caracter)
            codigo = it->second;
    }
    return codigo;
}
std::vector<char> HuffmanArbol::cifrar(std::string sec)
{
    std::string cifradoBinario;
    for (char c : sec)
    {
        cifradoBinario += obtenerCodigo(c);
    }
    // Asegurarse de que el tamaño de cifradoBinario sea múltiplo de 8
    while (cifradoBinario.size() % 8 != 0)
    {
        cifradoBinario += "0";
    }

    std::vector<char> resultado;
    for (size_t i = 0; i < cifradoBinario.size(); i += 8)
    {
        char byte = 0;
        for (size_t j = 0; j < 8; ++j)
        {
            if (cifradoBinario[i + j] == '1')
            {
                byte |= 1 << (7 - j);
            }
        }
        resultado.push_back(byte);
    }
    return resultado;
}
string HuffmanArbol::desCifrar(string sec, long longiSec)
{
    HuffmanNodo *nodo = this->raiz;
    string desCifrado = "";
    int contador = 0;
    for (int i = 0; i < sec.size() +1; i++)
    {
        if (nodo->esHoja())
        {
            desCifrado += nodo->obtenerDato();
            nodo = this->raiz;
            contador++;
            if(contador == longiSec){
                break;
            }
        }
        if (sec[i] == '1')
        {
            nodo = nodo->obtenerHijoDer();
        }
        else
        {
            nodo = nodo->obtenerHijoIzq();
        }
    }
    return desCifrado;
}
HuffmanNodo * HuffmanArbol::getRaiz(){
    return this->raiz;
}
HuffmanNodo * HuffmanArbol::deCodificar(HuffmanNodo *nodo, char dir, int &cont, string &des)
{
    if(nodo->esHoja()){
        des+= nodo->obtenerDato();
        nodo = this->raiz;
        cont++;
    }
    if(dir == '1'){
        nodo = nodo->obtenerHijoDer();
    }
    else if(dir == '0'){
        nodo = nodo->obtenerHijoIzq();
    }
    return nodo;
}