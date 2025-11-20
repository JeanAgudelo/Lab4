#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Enlace.h"

const int INF = 999999;

using namespace std;

class Enrutador
{
private:
    string nombre;
    vector<Enlace> vecinos;
    map<string, int> tablaCostos;
    map<string, vector<string>> tablaCaminos;
public:
    Enrutador(string n);
    string getNombre();
    void agregarVecino(string destino, int costo);
    vector<Enlace> getVecinos();

    void setTablaCostos(map<string, int> tabla);
    void setTablaCaminos(map<string, vector<string>> tabla);

    int getCosto(string destino);

    void imprimirTablaCostos(vector<string> todosEnrutadores);
    void imprimirTablaSimple();
    void imprimirCamino(string destino);

    void eliminarVecino(string nombreVecino);
};

#endif // ENRUTADOR_H
