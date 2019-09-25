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

// disegna una HitBox proporzionata al buffer se contr = true se no stampa sullo schermo
void HitBox::stampa(bool contr)
{
    double stampaX=x, stampaY=y, stampaL=lunghezza, stampaA=altezza;

    if(contr)
    {
        stampaX= getStampaX();
        stampaY= getStampaY();
        stampaL= getStampaL();
        stampaA= getStampaA();
    }

    al_draw_scaled_bitmap
    (
        load,
        0, 0,                                // source origin
        al_get_bitmap_width(load),           // source width
        al_get_bitmap_height(load),          // source height
        stampaX, stampaY,                    // target origin
        stampaL,
        stampaA,                             // target dimensions
        0                                    // flags
    );
}

// verifica se due hitbox si toccano
bool HitBox::collisione(HitBox* obj)
{
   return(load!=nullptr && 
   (
        (getStampaX() >= obj->getStampaX()) && (getStampaX() <= obj->getStampaX() + obj->getStampaL()) &&
        (getStampaY() >= obj->getStampaY()) && (getStampaY() <= obj->getStampaY() + obj->getStampaA())
        ||
        (getStampaX()+getStampaL() >= obj->getStampaX()) && (getStampaX()+getStampaL() <= obj->getStampaX() + obj->getStampaL()) &&
        (getStampaY() >= obj->getStampaY()) && (getStampaY() <= obj->getStampaY() + obj->getStampaA())
        ||
        (getStampaX()+getStampaL() >= obj->getStampaX()) && (getStampaX()+getStampaL() <= obj->getStampaX() + obj->getStampaL()) &&
        (getStampaY()+getStampaA() >= obj->getStampaY()) && (getStampaY()+getStampaA() <= obj->getStampaY() + obj->getStampaA())
        ||
        (getStampaX() >= obj->getStampaX()) && (getStampaX() <= obj->getStampaX() + obj->getStampaL()) &&
        (getStampaY()+getStampaA() >= obj->getStampaY()) && (getStampaY()+getStampaA() <= obj->getStampaY() + obj->getStampaA())
   )
   );

}

// distrugge l'immagine legata all'HitBox
void HitBox::distruggiLoad()
{
    if(load!=nullptr) 
    {
        al_destroy_bitmap(load); 
        load=nullptr;
    }
}

// crea l'immagine legata all'HitBox
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


string HitBox::getImmagine()  const
{
    return immagine;
}


int HitBox::getLunghezza()  const
{ 
    return lunghezza;
}


int HitBox::getAltezza()  const
{ 
    return altezza;
}


int HitBox::getY()  const
{
    return y;
}


int HitBox::getX()  const
{
    return x;
}

void HitBox::setStampaX(int a)
{
    x = a-((displayW-  (wGlobal * scale2) ) /2  ) ;
}

void HitBox::setStampaY(int a)
{
    y= a-( (displayH-(hGlobal * scale2))  /2 );
}


int HitBox::getStampaX() const
{
    return (x+(displayW-(wGlobal * scale2))/2 ); 
}


int HitBox::getStampaY()  const
{
    return (y+(displayH-(hGlobal * scale2))/2 ); 
}


int HitBox::getStampaL()  const
{
    return lunghezza*( (wGlobal*scale2)/1024.);
}


int HitBox::getStampaA() const
{
    return altezza*( (hGlobal*scale2)/768.);
}


ALLEGRO_BITMAP* HitBox::getLoad()  const
{
    return load;
}