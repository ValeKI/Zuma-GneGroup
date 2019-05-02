#ifndef PALLINARANA_H
#define PALLINARANA_H
#include "Pallina.h"

class PallinaRana: public Pallina
{
    private: 
        int vx;
        int vy;
        pair<int,int> punto;
    public:
        void spara(int, int, int, int);
        

};
#endif