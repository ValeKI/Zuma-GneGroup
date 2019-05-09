#ifndef PALLINA_H
#define PALLINA_H
#include "HitBox.h"
#include <utility>
#include <string>

enum DIREZIONE{AVANTI = 0, DIETRO, FERMO};

enum COLORE{ROSSO=0,BLU,VERDE,ARANCIONE,VIOLA,GIALLO};


class Pallina:public HitBox
{
    protected:
        COLORE colore;
        int posizione;
        DIREZIONE direzione;
        int displayW;    
        int displayH;
        int scale;
        int velocita;

    public:
        Pallina(COLORE, int = 0);
        ~Pallina();

        void avanza();
        void movimento(const pair<int, int>&);
        void stop();
        void inverti();

        COLORE getColore() const;
        int getPosizione() const;
        DIREZIONE getDirezione() const;
        void setPosizione(int );
        void setDirezione(DIREZIONE);
        void setVelocita(int);
    
};

#endif