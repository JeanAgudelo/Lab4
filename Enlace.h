#ifndef ENLACE_H
#define ENLACE_H

#include <string>
using namespace std;

class Enlace{
public:
    string destino;
    int costo;

    Enlace(string dest, int c);
};

#endif // ENLACE_H
