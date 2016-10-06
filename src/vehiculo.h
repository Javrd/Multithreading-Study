#ifndef VEHICULO_H
#define VEHICULO_H
#include <puente.h>

class Puente;

class Vehiculo
{
private:
    Puente *puente;
    string matricula;
    struct timespec tim, tim2;

public:
    static string getRandMatricula();
    static void *creaVehiculo(void* object);
    Vehiculo(string matricula, Puente *puente);
    void cruzaPuente();


};

#endif // VEHICULO_H
