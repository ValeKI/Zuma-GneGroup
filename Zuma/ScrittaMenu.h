#ifndef SCRITTAMENU_H
#define SCRITTAMENU_H
#include "HitBox.h"


class ScrittaMenu : public HitBox
{
    ScrittaMenu(int _x, int _y, int _altezza, int _lunghezza, string _immagine):HitBox(_x,_y,_altezza,_lunghezza,_immagine){}


    void reazione()
    {
        if(immagine[0]=='0')
            immagine[0]='1';
        else
            immagine[0]='0';
        
    }    
};
#endif