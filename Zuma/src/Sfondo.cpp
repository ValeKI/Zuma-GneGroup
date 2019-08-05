#include "../header/Sfondo.h"


extern int wGlobal;
extern int hGlobal;

SFONDO::SFONDO()
{
    ALLEGRO_DISPLAY_MODE mode;

    al_get_display_mode(al_get_num_display_modes()-1, &mode);
    al_set_new_display_flags(ALLEGRO_WINDOWED);

    

    if( !(display = al_create_display(mode.width, mode.height)) )
    {
        cerr << "Error to create the display - 3";
        exit(-1);
    }

    ::wGlobal = (3*al_get_display_width( al_get_current_display() ))/4;
    ::hGlobal = (768*::wGlobal)/1024;

}

SFONDO::~SFONDO()
{
    al_destroy_display(display); 
}

ALLEGRO_DISPLAY* SFONDO::getDisplay() 
{
    return display;
}
