#ifndef RANA_H
#define RANA_H
#include "PallinaRana.h"

const int DISTANZA_PALLINA_CENTRO = 143;
const int IMMAGINEX = 146;
const int IMMAGINEY = 58;

class Rana: public HitBox
{
    private:
        int tempo = 0;
        int cx;
        int cy;
        double scale;
        double seno;
        double coseno;
        PallinaRana** palline;

    public:
    
        // si occupa di posizionare la rana al centro e di generare le due palline
        Rana(const int& a,const int& b, const int& n);
        ~Rana();

        // stampa la rana, dipende dalle coordinate del mouse l'angolo sul quale e' inclinata
        void stampa(int, int);

        // restituisce la pallina della lingua e genera la nuova
        PallinaRana* getPallina(bool coloriDisponibili[],const int& n);
        
        
};

#endif