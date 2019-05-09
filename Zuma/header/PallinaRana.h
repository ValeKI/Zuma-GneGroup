#ifndef PALLINARANA_H
#define PALLINARANA_H
#include "Pallina.h"
#include <cmath>

const int MODULO = 20;

class PallinaRana: public Pallina
{
    /*
    il bordo 
    
    palline[0]->getX()> ((displayW-(wGlobal * scale2))/2)
        &&
        palline[0]->getY()> ((displayH-(hGlobal * scale2))/2) 
        &&
        palline[0]->getX()+palline[0]->getLunghezza()<((displayW-(wGlobal * scale2))/2+1024) 
        &&
        palline[0]->getY()+palline[0]->getAltezza()<((displayH-(hGlobal * scale2))/2 +768) */

    private: 
        float vx;
        float vy;
        float scalare;
        pair<int, int> punto;
    public:
        PallinaRana(COLORE);
        void direziona(int, int, int, int);
        void movimento();
        bool nonNelloSchermo() const;
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