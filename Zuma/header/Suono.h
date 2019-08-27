#ifndef SUONO_H
#define SUONO_H

#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

class Suono
{
    private:
        ALLEGRO_SAMPLE *click;
        ALLEGRO_SAMPLE *invio;
        ALLEGRO_SAMPLE *exit;

        ALLEGRO_SAMPLE *menuSound;
        ALLEGRO_SAMPLE_ID IDMenuSound;

    
        ALLEGRO_SAMPLE *level1Sound;
        ALLEGRO_SAMPLE_ID IDLevel1Sound;

        ALLEGRO_SAMPLE *level2Sound;
        ALLEGRO_SAMPLE_ID IDLevel2Sound;

        ALLEGRO_SAMPLE *gameover;
        ALLEGRO_SAMPLE *win;
        ALLEGRO_SAMPLE *coin;
        ALLEGRO_SAMPLE *time;

        bool startL1 = false;
        bool startL2 = false;
        bool isMenu = true;

    public:
        Suono();
        ~Suono();
        bool playClick();
        bool playInvio();
        bool playExit();
        bool playMenu();
        bool playLevel1();
        bool playLevel2();
        bool playGameOver();
        bool playWin();
        bool playCoin();
        bool playTime();

        //void stopClick();
        //void stopInvio();
        //void stopExit();
        void stopMenu();
        void stopLevel1();
        void stopLevel2();
        //void stopGameOver();
        void stopWin();
        //void stopCoin();
        void stopTime();
};
#endif