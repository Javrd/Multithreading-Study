#include <puente.h>
#include <iostream>

Puente::Puente(int max)
{
    maxVehiculos = max;
    nVehiculos = 0;
    extremoAbierto = -1; // -1 indica que ambos extremos estan abiertos, 0 indica que el extremo A esta abierto y 1 que el extremo B esta abierto.
    consecutivos = 0;
    esperandoEnA = 0;
    esperandoEnB = 0;
}

void Puente::entrar (string matricula, int extremo)
{

    int esperandoEnExtremoOpuesto = extremo?esperandoEnA:esperandoEnB;
    string strExtremo = extremo?"B":"A";
    string strExtremoOpuesto = extremo?"A":"B";
    extremo? esperandoEnB++ : esperandoEnA++;

    while ((extremoAbierto != extremo && extremoAbierto != -1) || (consecutivos >= maxVehiculos && esperandoEnExtremoOpuesto))
    {
        cout << "El vehículo con la matrícula \"" << matricula << "\" espera en el extremo " << strExtremo << endl;
        pthread_cond_wait(extremo?&sentido_B_threshold_cv:&sentido_A_threshold_cv, &sentido_mutex);

    }

    if (extremoAbierto == -1)
    {
        cout << "** Extremo "<< strExtremoOpuesto << " cerrado. Sentido "<< strExtremo << " -> " << strExtremoOpuesto << " **" << endl;
        extremoAbierto = extremo;
    }

    consecutivos++;
    nVehiculos++;
    extremo? esperandoEnB-- : esperandoEnA--;

    cout << "El vehículo con la matrícula \"" << matricula << "\" entra por el extremo " << strExtremo <<
            ". Hay " << nVehiculos << " coche";
    if(nVehiculos != 1)
         cout << "s";
    cout << " en el puente." << endl;


}

void Puente::salir (string matricula)
{
    string strExtremoOpuesto = extremoAbierto?"A":"B";
    nVehiculos --;
    cout << "El vehículo con la matrícula \"" << matricula << "\" sale por el extremo " << strExtremoOpuesto <<
            ". Hay " << nVehiculos << " coche";
    if(nVehiculos != 1)
        cout << "s";
    cout << " en el puente." << endl;
    int maxBroadcast;
    if (nVehiculos == 0)
    {
        if (extremoAbierto == A && esperandoEnB)
        {
            maxBroadcast = (esperandoEnB<maxVehiculos || !esperandoEnA) ? esperandoEnB : maxVehiculos;
            for (int i = 0; i < maxBroadcast; i++)
                pthread_cond_signal(&sentido_B_threshold_cv);
        }

        else if (esperandoEnA)
        {
            maxBroadcast = (esperandoEnA<maxVehiculos || !esperandoEnB)? esperandoEnA : maxVehiculos;
            for (int i = 0; i < maxBroadcast; i++)
                pthread_cond_signal(&sentido_A_threshold_cv);
        }

        extremoAbierto = -1;
        consecutivos = 0;
        cout << "** Puente vacío, extremos abiertos. **" << endl;
    }
}

pthread_mutex_t* Puente::getMutex()
{
    return &sentido_mutex;
}
