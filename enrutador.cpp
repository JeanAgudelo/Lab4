#include "Enrutador.h"

Enrutador::Enrutador(string n) : nombre(n) {}

string Enrutador::getNombre() { return nombre; }

void Enrutador::agregarVecino(string destino, int costo) {
    for (size_t i = 0; i < vecinos.size(); i++) {
        if (vecinos[i].destino == destino) {
            vecinos[i].costo = costo;
            return;
        }
    }
    vecinos.push_back(Enlace(destino, costo));
}

vector<Enlace> Enrutador::getVecinos() {
    return vecinos;
}

void Enrutador::setTablaCostos(map<string, int> tabla) {
    tablaCostos = tabla;
}

void Enrutador::setTablaCaminos(map<string, vector<string>> tabla) {
    tablaCaminos = tabla;
}

int Enrutador::getCosto(string destino) {
    if (tablaCostos.find(destino) != tablaCostos.end()) {
        return tablaCostos[destino];
    }
    return INF;
}

void Enrutador::imprimirTablaCostos(vector<string> todosEnrutadores) {
    cout << nombre << " |";
    for (size_t i = 0; i < todosEnrutadores.size(); i++) {
        if (todosEnrutadores[i] == nombre)
            cout << "\t0";
        else if (tablaCostos.count(todosEnrutadores[i])) {
            int costo = tablaCostos[todosEnrutadores[i]];
            if (costo == INF)
                cout << "\t-";
            else
                cout << "\t" << costo;
        }
        else
            cout << "\t-";
    }
    cout << "\n";
}

void Enrutador::imprimirTablaSimple() {
    cout << "\nTabla de costos de " << nombre << ":\nDestino\tCosto\n";
    for (auto &it : tablaCostos)
        if (it.second < INF)
            cout << it.first << "\t" << it.second << "\n";
}

void Enrutador::imprimirCamino(string destino) {
    if (!tablaCaminos.count(destino) || tablaCostos.count(destino) == 0 || tablaCostos[destino] >= INF) {
        cout << "No hay camino hacia " << destino << "\n";
        return;
    }
    cout << "Camino " << nombre << " -> " << destino << ": ";
    auto camino = tablaCaminos[destino];
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i];
        if (i < camino.size() - 1) cout << " -> ";
    }
    cout << " (Costo: ";
    if (tablaCostos.count(destino))
        cout << tablaCostos[destino];
    else
        cout << "INF";
    cout << ")\n";
}

void Enrutador::eliminarVecino(string nombreVecino) {
    for (size_t i = 0; i < vecinos.size(); i++) {
        if (vecinos[i].destino == nombreVecino) {
            vecinos.erase(vecinos.begin() + i);
            break;
        }
    }
}
