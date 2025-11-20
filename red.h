#ifndef RED_H
#define RED_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <queue>
#include "enrutador.h"
extern const int INF;

using namespace std;

class Red
{
private:
    map<string, Enrutador*> enrutadores;

    void dijkstra(string origen);
public:
    Red();
    ~Red();

    void agregarEnrutador(string nombre);
    void eliminarEnrutador(string nombre);
    void agregarConexion(string origen, string destino, int costo);

    void calcularRutas();

    void cargarDesdeArchivo(string nombreArchivo);
    void crearRedAleatoria(int numEnrutadores, int numConexiones);

    void imprimirTodasLasTablas();
    void imprimirTablaIndividual(string nombre);

    void imprimirCamino(string origen, string destino);
};

#endif // RED_H
