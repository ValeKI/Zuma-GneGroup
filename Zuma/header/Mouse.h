#ifndef MOUSE_H
#define MOUSE_H
#include "HitBox.h"

// rappresenta il punto del mouse e gestisce la collisione
class Mouse
{
    private:
        int x = 0;
        int y = 0;

    public:
        void setY(const int&);
        void setX(const int&);
        int getY() const;
        int getX() const;
        bool collisione(HitBox*);

};


#endif