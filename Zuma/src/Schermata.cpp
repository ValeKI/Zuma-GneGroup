#include "../header/Schermata.h"

// costruttori

Schermata::Schermata()
{
    b = nullptr;
    font = nullptr;
    al_init_font_addon();
    al_init_ttf_addon();
    event_queue.start();
}

// distruttore

Schermata::~Schermata()
{
    if(b!=nullptr)
        delete b;
    b = nullptr; 

    if(font!=nullptr)
        al_destroy_font(font);
    font = nullptr;

    event_queue.stop();
}
