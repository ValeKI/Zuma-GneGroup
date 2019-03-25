#include "HitBox.h"

extern int wGlobal;
extern int hGlobal;

HitBox::HitBox(string _immagine, int _x, int _y, float scale) 
{
    x=_x; y=_y; immagine=_immagine; load=nullptr;
    ricreaLoad();
    if(load!=nullptr)
    {
        
        lunghezza = al_get_bitmap_width (load)*scale;
        altezza   = al_get_bitmap_height(load)*scale;
        x         = x;
        y         = y;
    }
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
            ( obj->x                    >= x && obj->x               <= (x+lunghezza/2) )
            ||
            ( (obj->x+obj->lunghezza)      >= x && (obj->x+obj->lunghezza) <= (x+lunghezza/2) )    
        )

            return -1; // sinistra

        if
        (
            ( obj->x                    > (x+lunghezza/2) && obj->x               < (x+lunghezza) )
            ||
            ( obj->x+obj->lunghezza      > (x+lunghezza/2) && obj->x+obj->lunghezza < (x+lunghezza) )    
        )

            return 1; // destra
    }
    return 0;
}


HitBox::~HitBox()
{
    distruggiLoad();
}

    


void HitBox::stampa(bool contr)
{
   // cout << endl << immagine << x << " " << y << " " << altezza << " " << lunghezza << endl;

    int stampaX=x, stampaY=y, stampaL=lunghezza, stampaA=altezza;

    if(contr)
    {
        stampaX*=(wGlobal/1024.);
        stampaY*=(hGlobal/768.);
        stampaL*=(wGlobal/1024.);
        stampaA*=(hGlobal/768.);
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


void HitBox::distruggiLoad(){if(load!=nullptr) {al_destroy_bitmap(load); load=nullptr;}}
void HitBox::ricreaLoad()
{
    if((load==nullptr) && !(load=al_load_bitmap(immagine.c_str())   ))
    {
        cerr << "Error to load an image - 62"<< immagine <<"uff" << x << " " << y << endl;
        exit(-1);
    }
}