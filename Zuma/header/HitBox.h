#ifndef HITBOX_H
#define HITBOX_H
#include <string>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

using namespace std;

extern int wGlobal;
extern int hGlobal;

class HitBox
{
    protected: 
        int x;
        int y;
        int altezza;
        int lunghezza;
        int displayW;    
        int displayH;
        int scale2;
        string immagine;
        ALLEGRO_BITMAP *load;

    public:

        HitBox(string _immagine, int _x, int _y, float scale);
        ~HitBox();

        void setImmagine(string);
        void setLunghezza(int);
        void setAltezza(int);
        void setY(int);
        void setX(int);
        virtual void setStampaY(int);
        virtual void setStampaX(int);
    
        string getImmagine() const;
        int getLunghezza() const;
        int getAltezza() const;
        int getY() const;
        int getX() const;
        virtual int getStampaX() const;
        virtual int getStampaY() const;
        virtual int getStampaL() const;
        virtual int getStampaA() const;
        ALLEGRO_BITMAP* getLoad() const;

        // disegna una HitBox proporzionata al buffer se contr = true se no stampa sullo schermo
        virtual void stampa(bool contr);

        // verifica se due hitbox si toccano
        virtual bool collisione(const HitBox* obj) const;

        // distrugge l'immagine legata all'HitBox
        void distruggiLoad();

        // crea l'immagine legata all'HitBox
        void ricreaLoad();

};

#endif