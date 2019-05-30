#ifndef RANA_H
#define RANA_H
#include "PallinaRana.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

class Rana: public HitBox
{
    private:
        int cx;
        int cy;
        double scale;
        double seno;
        double coseno;
        PallinaRana** palline;
        
        
    public:
        Rana(int,int);
        void stampa(int, int);
        PallinaRana* getPallina();
        ~Rana();
        
};

#endif