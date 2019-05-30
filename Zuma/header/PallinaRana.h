#ifndef PALLINARANA_H
#define PALLINARANA_H
#include "Pallina.h"
#include <cmath>

const int MODULO = 20;

class PallinaRana: public Pallina
{

    private: 
        float vx;
        float vy;
        float scalare;
        pair<int, int> punto;
    public:

        float getVx() const;
        float getVy() const;
        float getScalare() const;
        pair<int,int> getPunto() const;



        PallinaRana(const PallinaRana&);
        PallinaRana(COLORE);
        void direziona(int, int, int, int);
        void movimento();
        bool nonNelloSchermo() const;

        void setStampaX(int);
        void setStampaY(int);

        void setX(int a)
        {
            x=a-lunghezza/2;
        }
        void setY(int a)
        {
            y=a-altezza/2;
        }

};
#endif