#include "../header/Schermata.h"

Schermata::Schermata()
{
    al_init_font_addon();
    al_init_ttf_addon();
}

Schermata::~Schermata()
{
    if(b!=nullptr)
        delete b;

    al_destroy_font(font);
}