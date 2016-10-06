#ifndef PUENTE_H
#define PUENTE_H
#include <string>

using namespace std;

class Puente
{
private:
    int maxVehiculos;
    int nVehiculos;
    int extremoAbierto;
    int consecutivos;
    int esperandoEnA;
    int esperandoEnB;
    pthread_mutex_t sentido_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t sentido_A_threshold_cv = PTHREAD_COND_INITIALIZER;
    pthread_cond_t sentido_B_threshold_cv = PTHREAD_COND_INITIALIZER;
public:
    Puente(int max);
    void entrar (string matricula, int extremo);
    void salir (string matricula);
    static const int A = 0;
    static const int B = 1;
    pthread_mutex_t* getMutex();
};

#endif // PUENTE_H
