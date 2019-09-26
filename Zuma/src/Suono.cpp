#include "../header/Suono.h"

Suono::Suono()
{
    this->pause = al_load_sample("../Sounds/pause.wav");
    this->gameover = al_load_sample("../Sounds/gameover.wav");
    this->win = al_load_sample("../Sounds/win.wav");
    this->menuSound = al_load_sample("../Sounds/menu.wav");
    this->levelSound = al_load_sample("../Sounds/level.wav");

     if ( !exit || !pause || !gameover || !win || !time || !menuSound || !levelSound)
     {
      printf( "Audio clip sample not loaded!\n" ); 
     }
}

Suono::~Suono()
{
    al_reserve_samples(11);

    al_destroy_sample(pause);
    al_destroy_sample(menuSound);
    al_destroy_sample(levelSound);
    al_destroy_sample(gameover);
    al_destroy_sample(win);

}

bool Suono::getLivello()
{
    return startL;
}

bool Suono::getMenu()
{
    return isMenu;
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

void Suono::playLevel()//musica di sottofondo del livello
{
    if(startL)
    al_play_sample(this->levelSound, 0.3,0.0,1.0, ALLEGRO_PLAYMODE_LOOP, &IDLevelSound);
    startL = false;

}

void Suono::playGameOver()
{
    al_play_sample(this->gameover, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}


void Suono::playWin()
{
    al_play_sample(this->win, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}

void Suono::stopMenu()
{
    if(isMenu)
    al_stop_sample(&IDMenuSound);
    isMenu = false;
    
   
}

void Suono::stopLevel()
{
    if(!startL)
    al_stop_sample(&IDLevelSound);
    startL = true;
   
}

void Suono::stopWin()
{
    al_rest(3.0);
}
