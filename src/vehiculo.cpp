#include <vehiculo.h>
#include <stdlib.h>

Vehiculo::Vehiculo(string matricula, Puente *puente)
{
    this->puente = puente;
    this->matricula = matricula;
    cruzaPuente();

}


void Vehiculo::cruzaPuente()
{
    int extremo = (rand() % 2)?Puente::A:Puente::B;

    pthread_mutex_lock(puente->getMutex());
    puente->entrar(matricula, extremo);
    pthread_mutex_unlock(puente->getMutex());

    tim.tv_sec  = 0;
    tim.tv_nsec = rand()%500000000;  // 0.5 segundos en nanosegundos
    nanosleep(&tim , &tim2);

    pthread_mutex_lock(puente->getMutex());
    puente->salir(matricula);
    pthread_mutex_unlock(puente->getMutex());

    pthread_exit(NULL);
}

void *Vehiculo::creaVehiculo(void* object){
    Puente* puente = reinterpret_cast<Puente*>(object);
    Vehiculo vehiculo (Vehiculo::getRandMatricula(), puente);
}

string Vehiculo::getRandMatricula(){

    string str = "";
    for (int i=0; i<4; i++){
        char numMatricula = rand()%(58-48)+48;
        str += numMatricula;
    }
    str += " ";
    for (int i=0; i<3; i++){
        char letraMatricula = rand()%(91-65)+65;
        str += letraMatricula;
    }
    return str;
}
