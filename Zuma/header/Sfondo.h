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
    SFONDO()
    {

        ALLEGRO_DISPLAY_MODE mode;

        al_get_display_mode(al_get_num_display_modes()-1, &mode);
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

        if( !(display = al_create_display(mode.width, mode.height)) )
        {
            cerr << "Error to create the display - 3";
            exit(-1);
        }
        
    }

    ~SFONDO()
    {
        al_destroy_display(display); 
    }

    ALLEGRO_DISPLAY* getDisplay() {return display;}

    protected:
    ALLEGRO_DISPLAY* display;

};



#endif