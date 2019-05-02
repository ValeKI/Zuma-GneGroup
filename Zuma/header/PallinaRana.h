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

};
#endif