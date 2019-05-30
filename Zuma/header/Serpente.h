#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <vector>

class Serpente
{
    private:
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;

    public:
        void caricaCoordinate();
        void generaPalline(int num, int tipi);
        void stampa();
        ~Serpente();
        int getSizeCoordinate();
        void toccaSparo(Pallina* sparo);



}


#endif