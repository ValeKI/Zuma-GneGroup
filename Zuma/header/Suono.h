#ifndef SUONO_H
#define SUONO_H

#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

class Suono
{
    private:
       // ALLEGRO_SAMPLE *exit;
        ALLEGRO_SAMPLE *pause;

        ALLEGRO_SAMPLE *menuSound;
        ALLEGRO_SAMPLE_ID IDMenuSound;

        ALLEGRO_SAMPLE *levelSound;
        ALLEGRO_SAMPLE_ID IDLevelSound;

        ALLEGRO_SAMPLE *gameover;
        ALLEGRO_SAMPLE *win;


    protected:
        bool startL = true;
        bool isMenu = false;

    public:
        Suono();
        ~Suono();

        bool getLivello();
        bool getMenu();

        void playPause();
        void playMenu();
        void playLevel();
        void playGameOver();
        void playWin();
        
        void stopMenu();
        void stopLevel();
        void stopWin();
};
#endif