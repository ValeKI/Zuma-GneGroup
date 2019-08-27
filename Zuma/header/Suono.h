#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

class Sound
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

        bool startL1;
        bool startL2;
        bool isMenu;

    public:
        Sound();
        ~Sound();
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

        bool stopClick();
        bool stopInvio();
        bool stopExit();
        bool stopMenu();
        bool stopLevel1();
        bool stopLevel2();
        bool stopGameOver();
        bool stopWin();
        bool stopCoin();
        bool stopTime();
};
#endif