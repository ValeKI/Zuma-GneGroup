#ifndef SCHERMATA_H
#define SCHERMATA_H
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include "Event_queue.h"
#include "Buffer.h"
#include "Mouse.h"

enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ESC, KEY_SPACE};

class Schermata
{
    protected:
    Event_queue event_queue;
    ALLEGRO_FONT* font = nullptr;
    BUFFER* b = nullptr;
    Mouse m;
    const int numKey = 6;
    bool key[6]= {false,false,false,false,false,false};
    
    public:
    virtual void caricaFont() = 0;
    Schermata();
    ~Schermata();
};

#endif