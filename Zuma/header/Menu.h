#ifndef MENU_H
#define MENU_H
#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "ScrittaMenu.h"
#include "Event_queue.h"
#include "Buffer.h"
#include "Schermata.h"


class Menu : public Schermata // pero' devi leggerlo in inglese
{
    private:
        vector<string> scelte;
    public:
        void caricaFont() override;
        bool collideText(const int& mx, const int& my, string& s, const int& px, const int& py);
        Menu();
        ~Menu();
        int menu1();
};

#endif