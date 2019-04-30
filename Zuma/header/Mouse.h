#ifndef MOUSE_H
#define MOUSE_H
#include "HitBox.h"

class Mouse
{
    private:
        int x;
        int y;
        int displayW;
        int displayH;
        int scale;

    public:
        Mouse();
        void setY(int);
        void setX(int);
        int getY();
        int getX();
        bool collisione(HitBox*);

};


#endif