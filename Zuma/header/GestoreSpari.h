#ifndef GESTORESPARI_H
#define GESTORESPARI_H
#include "PallinaRana.h"
#include "Buffer.h"
#include "Serpente.h"
#include <string>
#include <vector>

class GestoreSpari
{
    private:
        vector<PallinaRana*> spari;
    public:
        ~GestoreSpari();
        
        PallinaRana* getPallinaRana(int i);

        void inserisciSparo(PallinaRana* sparo);
        
        Pallina* rimuoviPallina(int i);
        
        // se uno sparo esce dallo schermo viene eliminato
        void nelloSchermo(BUFFER&);
        void stampa();
        
        // se la pallina ha lo spazio per essere inserita viene rimossa dagli spari
        bool collisioneSparo(Serpente& serpy);
        
};

#endif