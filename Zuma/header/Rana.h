#ifndef RANA_H
#define RANA_H
#include "Pallina.h"

class Rana: public HitBox
{
    private:
        int cx;
        int cy;
        double scale;
        double seno;
        double coseno;
        Pallina** pallina;
        
        
    public:
        Rana(int,int);
        void stampa(int, int);
        
};

#endif