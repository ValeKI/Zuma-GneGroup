#ifndef MENU_H
#define MENU_H
#include <vector>
#include "ScrittaMenu.h"
#include "Event_queue.h"
#include "Buffer.h"

class Menu // pero' devi leggerlo in inglese
{
    private:
        vector<ScrittaMenu*> scritte;
        Event_queue event_queue;
        bool key[6]= {false,false,false,false,false,false};

    public:
        Menu();
        ~Menu();
        void menu1();
        void distruggiScritte();
    
};

#endif