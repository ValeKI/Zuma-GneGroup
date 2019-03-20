#ifndef SCRITTAMENU_H
#define SCRITTAMENU_H
#include "HitBox.h"


class ScrittaMenu : public HitBox
{
    ScrittaMenu(int _x, int _y, string _immagine, int _scale):HitBox(_immagine,_x,_y,_scale){}


    void reazione()
    {
        if(immagine[0]=='0')
            immagine[0]='1';
        else
            immagine[0]='0';
        
    }    
};
#endif