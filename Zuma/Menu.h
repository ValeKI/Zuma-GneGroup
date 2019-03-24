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
    BUFFER buffer;
    bool key[6];

    public:
    Menu(){}

    void menu1()
    {
        buffer.setImmagine("image/Sfondo.jpg");

        scritte.push_back(new ScrittaMenu("image/0_Tempo.jpg",300,300,1));
        scritte.push_back(new ScrittaMenu("image/0_Classica.jpg",300,425,1));
        scritte.push_back( new ScrittaMenu("image/0_Mosse.jpg",300,560,1));

        while(888)
        {
            
        }


    }

};

#endif