#include "../header/ScrittaMenu.h"

ScrittaMenu::ScrittaMenu(string _immagine, int _x, int _y, int _scale):HitBox(_immagine,_x,_y,_scale){}




void ScrittaMenu::reazione(bool stato)
{
    distruggiLoad();
    immagine[9]=to_string(stato)[0];
    ricreaLoad();
}    