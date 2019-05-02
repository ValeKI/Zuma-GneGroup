#ifndef PALLINARANA_H
#define PALLINARANA_H
#include "Pallina.h"
#include <cmath>

const int MODULO = 1;

class PallinaRana: public Pallina
{
    private: 
        int vx;
        int vy;
        pair<int, int> punto;
    public:
        PallinaRana(COLORE);
        void spara(int, int, int, int);
        void movimento();
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