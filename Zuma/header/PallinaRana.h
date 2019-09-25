#ifndef PALLINARANA_H
#define PALLINARANA_H
#include "Pallina.h"
#include <cmath>

const int MODULO = 20;

class PallinaRana: public Pallina
{

    private:
        // coordinata x di un vettore di direzione punto di pallina -> mouse 
        float vx;
        // coordinata x di un vettore di direzione punto di pallina -> mouse 
        float vy;
        // se moltiplicato col vettore di direzione, il modulo del vettore diventa MODULO
        float scalare;
        // punto centrale
        pair<int, int> punto;
    public:

        PallinaRana(const PallinaRana&);
        PallinaRana(COLORE);
        
        void setX(const int&);
        void setY(const int&);
        void setStampaX(const int&);
        void setStampaY(const int&);

        float getVx() const;
        float getVy() const;
        float getScalare() const;
        pair<int,int> getPunto() const;

        // e' calcolata la posizione della pallina, che dipende dalle coordinate del mouse
        void direziona(int, int, int, int);
        void movimento();
};
#endif