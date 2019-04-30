#ifndef SFONDO_H
#define SFONDO_H

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;


class SFONDO
{
    public:
        SFONDO();

        ~SFONDO();

        ALLEGRO_DISPLAY* getDisplay();

    protected:
        ALLEGRO_DISPLAY* display;

};



#endif