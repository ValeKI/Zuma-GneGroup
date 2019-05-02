#include "../header/HitBox.h"

extern int wGlobal;
extern int hGlobal;

HitBox::HitBox(string _immagine, int _x, int _y, float scale) 
{
    ALLEGRO_DISPLAY* display=al_get_current_display();
    displayW= al_get_display_width(display);
    displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    scale2 = min(sx,sy);

    x=_x; y=_y; immagine=_immagine; load=nullptr;
    ricreaLoad();
    if(load!=nullptr)
    {
        lunghezza = al_get_bitmap_width (load)*scale;
        altezza   = al_get_bitmap_height(load)*scale;
    }
}

HitBox::~HitBox()
{
    distruggiLoad();
}


void HitBox::stampa(bool contr)
{
   // cout << endl << immagine << x << " " << y << " " << altezza << " " << lunghezza << endl;

    double stampaX=x, stampaY=y, stampaL=lunghezza, stampaA=altezza;

    if(contr)
    {
        stampaX= (stampaX+(displayW-(wGlobal * scale2))/2 );
        stampaY= (stampaY+((displayH-(hGlobal * scale2))/2 ));
        stampaL= stampaL*( (wGlobal*scale2)/1024.);
        stampaA= stampaA*( (hGlobal*scale2)/768.);

      //  cout << (displayW-(wGlobal * scale2))/2  << endl ;
    }

    al_draw_scaled_bitmap
    (
        load,
        0, 0,                                // source origin
        al_get_bitmap_width(load),           // source width
        al_get_bitmap_height(load),          // source height
        stampaX, stampaY,                                // target origin
        stampaL,
        stampaA,    // target dimensions
        0                                    // flags
    );
}


int HitBox::collisione(HitBox* obj)
{
    if
        (load!=nullptr &&
        (
            (obj->y             >= y && obj->y             <= (y + altezza))
            ||
            (obj->y+obj->altezza >= y && obj->y+obj->altezza <= (y+altezza) )
        )
        )
    {
        if
        (
            ( obj->x                       >= x && obj->x                  <= (x+lunghezza/2) )
            ||
            ( (obj->x+obj->lunghezza)      >= x && (obj->x+obj->lunghezza) <= (x+lunghezza/2) )    
        )

            return -1; // sinistra

        if
        (
            ( obj->x                     >= (x+lunghezza/2) && obj->x                <= (x+lunghezza) )
            ||
            ( obj->x+obj->lunghezza      >= (x+lunghezza/2) && obj->x+obj->lunghezza <= (x+lunghezza) )    
        )

            return 1; // destra
    }
    return 0;
}


void HitBox::distruggiLoad()
{
    if(load!=nullptr) 
    {
        al_destroy_bitmap(load); 
        load=nullptr;
    }
}

void HitBox::ricreaLoad()
{
    if((load==nullptr) && !(load=al_load_bitmap(immagine.c_str())   ))
    {
        cerr << "Error to load an image "<< immagine << " " << x << " " << endl;
        exit(-1);
    }
}

void HitBox::setImmagine(string immagine) 
{ 
    this->immagine = immagine;  
}


void HitBox::setLunghezza(int lunghezza) 
{ 
    this->lunghezza = lunghezza;  
}


void HitBox::setAltezza(int altezza) 
{
    this->altezza = altezza;
}


void HitBox::setY(int y) 
{
    this->y = y;
}


void HitBox::setX(int x) 
{ 
    this->x = x;
}


string HitBox::getImmagine() 
{
    return immagine;
}


int HitBox::getLunghezza() 
{ 
    return lunghezza;
}


int HitBox::getAltezza() 
{ 
    return altezza;
}


int HitBox::getY() 
{
    return y;
}


int HitBox::getX() 
{
    return x;
}


int HitBox::getStampaX()
{
    return (x+(displayW-(wGlobal * scale2))/2 ); 
}


int HitBox::getStampaY()
{
    return (y+(displayH-(hGlobal * scale2))/2 ); 
}


int HitBox::getStampaL()
{
    return lunghezza*( (wGlobal*scale2)/1024.);
}


int HitBox::getStampaA()
{
    return altezza*( (hGlobal*scale2)/768.);
}


ALLEGRO_BITMAP* HitBox::getLoad() 
{
    return load;
}