#ifndef GESTORESPARI_H
#define GESTORESPARI_H
#include "PallinaRana.h"
#include "GestoreSpari.h"
#include "Buffer.h"
#include "Serpente.h"
#include <string>
#include <vector>

class GestoreSpari
{
    private:
        vector<PallinaRana*> spari;
    public:
        void inserisciSparo(PallinaRana* sparo);
        bool collisioneSparo(Serpente& serpy);
        void nelloSchermo(BUFFER&);
        void stampa();
        ~GestoreSpari();
};

#endif