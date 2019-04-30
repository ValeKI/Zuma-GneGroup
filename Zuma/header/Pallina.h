#ifndef PALLINA_H
#define PALLINA_H
#include "HitBox.h"
#include <utility>
#include <string>

enum DIREZIONE{AVANTI = 0, DIETRO, FERMO};

enum COLORE{ROSSO=0,BLU,VERDE,ARANCIONE,VIOLA,GIALLO};


class Pallina:public HitBox
{
    private:
        COLORE colore;
        bool  bonus;
        int posizione;
        DIREZIONE direzione;
        int displayW;    
        int displayH;
        int scale;

    public:
        Pallina(COLORE, int);
        ~Pallina();

        void avanza();
        void movimento(const pair<int, int>&);
        void stop();
        void inverti();

        COLORE getColore() const;
        bool getBonus() const;
        int getPosizione() const;
        DIREZIONE getDirezione() const;
        void setDirezione(DIREZIONE);
    
};

#endif