#include "../header/Suono.h"

Suono::Suono()
{
    this->click = al_load_sample("../Sounds/click.wav");
    this->invio = al_load_sample("../Sounds/invio.wav");
    this->exit = al_load_sample("../Sounds/exit.wav");
    this->pause = al_load_sample("../Sounds/pause.wav");
    this->gameover = al_load_sample("../Sounds/gameover.wav");
    this->win = al_load_sample("../Sounds/win.wav");
    this->coin = al_load_sample("../Sounds/coin.wav");
    this->time = al_load_sample("../Sounds/time.wav");
    this->menuSound = al_load_sample("../Sounds/menu.ogg");
    this->level1Sound = al_load_sample("../Sounds/livello1.mp3");
    this->level2Sound = al_load_sample("../Sounds/livello2.mp3");
     
     if (!click || !invio|| !exit|| !pause|| !gameover|| !win|| !coin|| !time )
     {
      printf( "Audio clip sample not loaded!\n" ); 
     }
}

Suono::~Suono()
{
    al_destroy_sample(click);
    al_destroy_sample(invio);
    al_destroy_sample(exit);
    al_destroy_sample(pause);
    al_destroy_sample(menuSound);
    al_destroy_sample(level1Sound);
    al_destroy_sample(level2Sound);
    al_destroy_sample(gameover);
    al_destroy_sample(win);
    al_destroy_sample(coin);
    al_destroy_sample(time);

}


bool Suono::playClick()
{
    al_play_sample(click, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playInvio()
{
    al_play_sample(invio, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playExit()
{
    al_play_sample(exit, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playPause()
{
    al_play_sample(pause, 1, 0, 1, _ALLEGRO_PLAYMODE_STREAM_ONCE,0);
}
bool Suono::playMenu()
{
    if(isMenu)
    al_play_sample(menuSound, 1,0,1, _ALLEGRO_PLAYMODE_STREAM_ONCE, &IDMenuSound);
    startL1 = false;
    startL2 = false;
}


bool Suono::playLevel1()
{
    if(startL1)
    al_play_sample(level1Sound, 1,0,1, _ALLEGRO_PLAYMODE_STREAM_ONCE, &IDLevel1Sound);
   isMenu = false;
    startL2 = false;

}
bool Suono::playLevel2()
{
    if(startL2)
    al_play_sample(level2Sound, 1,0,1, _ALLEGRO_PLAYMODE_STREAM_ONCE, &IDLevel2Sound);
   isMenu = false;
    startL1 = false;

}

bool Suono::playGameOver()
{
    al_play_sample(gameover, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playWin()
{
    al_play_sample(win, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playCoin()
{
    al_play_sample(coin, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
}


bool Suono::playTime()
{
    al_play_sample(time, 1, 0,1,ALLEGRO_PLAYMODE_LOOP,0);
}


//void Suono::stopClick(){}
//void Suono::stopInvio(){}
//void Suono::stopExit(){}


void Suono::stopMenu()
{
    if(isMenu)
    al_stop_sample(&IDMenuSound);
    isMenu = false;
    startL1 = true;
    startL2 = true;
}


void Suono::stopLevel1()
{
    if(startL1)
    al_stop_sample(&IDLevel1Sound);
    startL1 = false;
    isMenu = true;
}


void Suono::stopLevel2()
{
    if(startL2)
    al_stop_sample(&IDLevel2Sound);
    startL2= false;
     isMenu = true;
}


//void stopGameOver(){}


void Suono::stopWin()
{
    al_rest(05.0);
}


//void stopCoin(){}


void Suono::stopTime()
{
    al_rest(10.0);
}
