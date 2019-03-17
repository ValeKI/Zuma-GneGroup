#ifndef HITBOX_H
#define HITBOX_H
#include "Buffer.h"
#include <string> 

class HitBox
{
    private:
        int x;
        int y;
        int altezza;
        int lunghezza;
        string immagine;

    public:

    HitBox(int _x, int _y, int _altezza, int _lunghezza, string _immagine)
        x(_x), y(_y), altezza(_altezza), immagine(_immagine) {}
    
    void setImmagine(string immagine) { this->immagine = immagine;  }
    void setLunghezza(int lunghezza) { this->lunghezza = lunghezza;  }
    void setAltezza(int altezza) {this->altezza = altezza;}
    void setY(int y) { this->y = y;   }
    void setX(int x) { this->x = x;}

    string getImmagine() {return immagine;}
    int getLunghezza() { return lunghezza;}
    int getAltezza() { return altezza;}
    int getY() {return y;}
    int getX() {return x;}
};

#endif