#ifndef MENU_H
#define MENU_H
#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Event_queue.h"
#include "Buffer.h"
#include "Schermata.h"
#include "Suono.h"


class Menu : public Schermata // pero' devi leggerlo in inglese
{
    private:
        vector<string> scelte;
    protected:
        int menu1();
        void menu2(string nomeImm, int tasto);
    public:
        void caricaFont() override;
        void tutorial();
        void zuma();
        int menuPausa(Suono*);
        int menuPricipale(Suono* );
        int menuLivelli();
        bool collideText(const int& mx, const int& my, string& s, const int& px, const int& py);
        Menu();
        ~Menu();
};

#endif