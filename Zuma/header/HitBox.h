#ifndef HITBOX_H
#define HITBOX_H
#include <string>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/* 
    !!!!!!!!!!!!
        COSTRUTTORE VUOTO
 */

using namespace std;

extern int wGlobal;
extern int hGlobal;

enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ESC, KEY_SPACE};

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

        virtual void stampa(bool contr);
        int collisione(HitBox* obj);

        void distruggiLoad();
        void ricreaLoad();

        void setImmagine(string);
        void setLunghezza(int);
        void setAltezza(int);
        virtual void setY(int);
        virtual void setX(int);
    
        string getImmagine() const;
        int getLunghezza() const;
        int getAltezza() const;
        int getY() const;
        int getX() const;
        int getStampaX() const;
        int getStampaY() const;
        int getStampaL() const;
        int getStampaA() const;
        ALLEGRO_BITMAP* getLoad() const;
};

#endif