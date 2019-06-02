#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <fstream>
#include <vector>

class Serpente
{
    private:
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;
        int distanzaPalline;

    public:
        int getPosizionePrimaPallina();
        void caricaCoordinate();
        void generaPalline(int num, int tipi);
        void stampa();
        ~Serpente();
        int getSizeCoordinate();
        bool toccaSparo(Pallina* sparo);
        void gestisciMovimento();
        int cambiaDirezioneDa(int,DIREZIONE);
        int cambiaDirezioneFinoA(int, DIREZIONE);


};


#endif