#include "../header/ScrittaMenu.h"

ScrittaMenu::ScrittaMenu(string _immagine, int _x, int _y, int _scale):HitBox(_immagine,_x,_y,_scale){}


void ScrittaMenu::reazione()
{
    if(immagine[9]=='0')
        immagine[9]='1';
    else
        immagine[9]='0';
}

void ScrittaMenu::reazione(bool stato)
{
    immagine[9]=to_string(stato)[0];
}    