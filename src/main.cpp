#include <vehiculo.h>
int main()
{


    Puente puente(20);
    for (int i=0; i<100; i++){
        pthread_t tid;
        pthread_create(&tid, NULL,Vehiculo::creaVehiculo, &puente);
    }
    pthread_exit(NULL);
    return 0;
}


