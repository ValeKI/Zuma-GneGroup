#include "../header/Buffer.h"
#include <allegro5/allegro.h>
extern int wGlobal;
extern int hGlobal;

bool BUFFER::collisione(HitBox* obj)
{
   
    return 
    (
        obj->getStampaX()-obj->getStampaL()/3.> ((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2)
        &&
        obj->getStampaX()+obj->getStampaL()+obj->getStampaL()/3.<=((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2+wGlobal*scale2) 
        
        &&
        
        obj->getStampaY()-obj->getStampaA()/3. > ((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2) 
        &&
        obj->getStampaY()+obj->getStampaA()+obj->getStampaA()/3.<=((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2 +hGlobal*scale2) 
    );
}


BUFFER::BUFFER(const char* immagine):HitBox(string(immagine), 0, 0, 1 )
{
    buffer=nullptr;
}

BUFFER::BUFFER(string immagine):HitBox(immagine, 0, 0, 1 )
{
   buffer=nullptr;
}


BUFFER::~BUFFER()
{
    if(buffer!=nullptr)
        al_destroy_bitmap(buffer);
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
        load,
        0, 0,                                // source origin
        al_get_bitmap_width(load),           // source width
        al_get_bitmap_height(load),          // source height
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
   
    setLunghezza(wGlobal * scale2);
    setAltezza(hGlobal * scale2);
    setX((displayW-getLunghezza())/2 );
    setY ( (displayH-getAltezza())/2 );

   // cout << getX() << endl;

    load=buffer;
    HitBox::stampa(0);

    load=nullptr;
    
}

