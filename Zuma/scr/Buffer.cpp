#include "../header/Buffer.h"

extern int wGlobal;
extern int hGlobal;

BUFFER::~BUFFER()
{
    if(buffer!=nullptr)
        al_destroy_bitmap(buffer);
}

bool BUFFER::stampaSfondo()
{
    ALLEGRO_DISPLAY* display=al_get_current_display();
    
    if(!(buffer=al_create_bitmap(wGlobal ,hGlobal)   ) )
    {
        cerr << "Error to create buffer bitmap - 4";
        al_destroy_display(display);
        return 0;
    }           
    
    ricreaLoad();

    ALLEGRO_BITMAP* prev_target=al_get_target_bitmap();
    al_set_target_bitmap(buffer);

    al_draw_scaled_bitmap
    (
        getLoad(),
        0, 0,                                // source origin
        al_get_bitmap_width(getLoad()),           // source width
        al_get_bitmap_height(getLoad()),          // source height
        0, 0,                                // target origin
        wGlobal,
        hGlobal,                        // target dimensions
        0                                    // flags
    );

    al_set_target_bitmap(prev_target); 
    distruggiLoad();
    return 1;
}

void BUFFER::stampa(bool contr)
{
    ALLEGRO_DISPLAY* display=al_get_current_display();
    int displayW= al_get_display_width(display);
    int displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    int scale = min(sx,sy);
    setLunghezza(wGlobal * scale);
    setAltezza(hGlobal * scale);
    setX((displayW-getLunghezza())/2 );
    setY ( (displayH-getAltezza())/2 );


    load=buffer;
    HitBox::stampa(0);

    load=nullptr;
    
}


BUFFER::BUFFER(const char* immagine):HitBox(string(immagine), 0, 0, 1 )
{
    buffer=nullptr;
}

BUFFER::BUFFER(string immagine):HitBox(immagine, 0, 0, 1 )
{
   buffer=nullptr;
}

void BUFFER::aggiungiImmagine(HitBox* hit)
{
    ALLEGRO_BITMAP* prev_target=al_get_target_bitmap();
    al_set_target_bitmap(buffer);

    hit->ricreaLoad();

    hit->stampa(1);

    al_set_target_bitmap(prev_target); 
    hit->distruggiLoad();
}