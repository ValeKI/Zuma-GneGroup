#ifndef PALLINA_H
#define PALLINA_H
#include "HitBox.h"
#include <utility>
#include <string>

const int VELOCITAPALLINE = 1;

enum DIREZIONE{AVANTI = 0, DIETRO, FERMO};
enum COLORE{ROSSO=0,BLU,VERDE,ARANCIONE,VIOLA,GIALLO};


class Pallina:public HitBox
{
    protected:
        COLORE colore;
        double posizione;
        DIREZIONE direzione;
        int velocita;

    public: 
        Pallina(COLORE, int = 0);
        //setter
        void setColore(const COLORE&);
        void setDirezione(const DIREZIONE&);
        void setPosizione(const double&);
        void setVelocita(const int&);
        // getter 
        COLORE getColore() const;
        DIREZIONE getDirezione() const;
        double getPosizione() const;
        int getVelocita() const;

        //metodi per la gestione del movimento della pallina
        void avanza();
        void invertiDirezione();
        void movimento(const pair<int, int>&);
        void stop();
};

#endif