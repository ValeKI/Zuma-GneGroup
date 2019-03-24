#ifndef HITBOX_H
#define HITBOX_H
#include <string>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

using namespace std;

extern int wGlobal;
extern int hGlobal;

enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ESC, KEY_SPACE};

class HitBox
{
    private:
        int x;
        int y;
        int altezza;
        int lunghezza;
        
        protected:  
        string immagine;
        ALLEGRO_BITMAP *load;

    public:

    HitBox(string _immagine, int _x, int _y, float scale);
    ~HitBox();
    virtual void stampa(bool contr);


    void distruggiLoad();
    void ricreaLoad();

    void setImmagine(string immagine) { this->immagine = immagine;  }
    void setLunghezza(int lunghezza) { this->lunghezza = lunghezza;  }
    void setAltezza(int altezza) {this->altezza = altezza;}
    void setY(int y) { this->y = y;}
    void setX(int x) { this->x = x;}

    string getImmagine() {return immagine;}
    int getLunghezza() { return lunghezza;}
    int getAltezza() { return altezza;}
    int getY() {return y;}
    int getX() {return x;}
    ALLEGRO_BITMAP* getLoad() {return load;}
};

#endif