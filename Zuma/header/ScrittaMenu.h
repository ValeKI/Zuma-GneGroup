#ifndef SCRITTAMENU_H
#define SCRITTAMENU_H
#include "HitBox.h"
#include <string>


class ScrittaMenu : public HitBox
{
    public:
        ScrittaMenu(string _immagine, int _x, int _y, int _scale);
 
        void reazione(bool stato);
};
#endif