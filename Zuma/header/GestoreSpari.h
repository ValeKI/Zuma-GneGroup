#ifndef GESTORESPARI_H
#define GESTORESPARI_H
#include "PallinaRana.h"
#include "GestoreSpari.h"
#include <string>
#include <vector>

class GestoreSpari
{
    private:
        vector<PallinaRana*> spari;
    public:
        void inserisciSparo(PallinaRana* sparo);
        void collisioneSparo(Serpente& serpy);
        void nelloSchermo(BUFFER&);
        void stampa();
}

#endif