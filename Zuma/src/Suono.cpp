#include "../header/Suono.h"

Suono::Suono()
{
    
    this->exit = al_load_sample("../Sounds/exit.wav");
    this->pause = al_load_sample("../Sounds/pause.wav");
    this->gameover = al_load_sample("../Sounds/gameover.wav");
    this->win = al_load_sample("../Sounds/win.wav");
    this->coin = al_load_sample("../Sounds/coin.wav");
    this->time = al_load_sample("../Sounds/time.wav");
    this->menuSound = al_load_sample("../Sounds/menu.wav");
    this->level1Sound = al_load_sample("../Sounds/level1.wav");

     if ( !exit || !pause || !gameover || !win || !coin || !time || !menuSound || !level1Sound)
     {
      printf( "Audio clip sample not loaded!\n" ); 
     }
}

Suono::~Suono()
{
    al_reserve_samples(11);

    al_destroy_sample(exit);
    al_destroy_sample(pause);
    al_destroy_sample(menuSound);
    al_destroy_sample(level1Sound);
    al_destroy_sample(gameover);
    al_destroy_sample(win);
    al_destroy_sample(coin);
    al_destroy_sample(time);

}

bool Suono::getLivello(){return startL1;}
bool Suono::getMenu(){return isMenu;}

void Suono::playExit()
{
    al_play_sample(exit, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}


void Suono::playPause()
{
    al_play_sample(pause, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
}
void Suono::playMenu()
{
    if(!isMenu)
    al_play_sample(this->menuSound, 0.3,0.0,1.0, ALLEGRO_PLAYMODE_LOOP, &IDMenuSound);
    isMenu = true;
}


void Suono::playLevel1()
{
    if(startL1)
    al_play_sample(this->level1Sound, 0.3,0.0,1.0, ALLEGRO_PLAYMODE_LOOP, &IDLevel1Sound);
    startL1 = false;

}

void Suono::playGameOver()
{
    al_play_sample(this->gameover, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}


void Suono::playWin()
{
    al_play_sample(this->win, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}


void Suono::playCoin()
{
    al_play_sample(this->coin, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}


void Suono::playTime()
{
    al_play_sample(this->time, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,0);
}





void Suono::stopMenu()
{
    if(isMenu)
    al_stop_sample(&IDMenuSound);
    isMenu = false;
    
   
}


void Suono::stopLevel1()
{
    if(!startL1)
    al_stop_sample(&IDLevel1Sound);
    startL1 = true;
   
}



//void stopGameOver(){}


void Suono::stopWin()
{
    al_rest(3.0);
}


//void stopCoin(){}


void Suono::stopTime()
{
    al_rest(10.0);
}
