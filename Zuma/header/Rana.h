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
        Pallina* pallina;
        
        
    public:
        Rana(int a = 0,int b = 0);
        void stampa(int mx, int my);
        
};

#endif