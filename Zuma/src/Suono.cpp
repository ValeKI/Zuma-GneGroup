#include "../header/Suono.h"

Suono::Suono()
{
    this->click = al_load_sample("../Sounds/click.mav");
    this->invio = al_load_sample("../Sounds/invio.mav");
    this->exit = al_load_sample("../Sounds/exit.mav");
    this->gameover = al_load_sample("../Sounds/gameover.mav");
    this->win = al_load_sample("../Sounds/win.mav");
    this->coin = al_load_sample("../Sounds/coin.mav");
    this->time = al_load_sample("../Sounds/time.mav");
    //this->menuSound = al_load_sample("../Sounds/menu.mav");
    //this->level1Sound = al_load_sample("../Sounds/l1Sound.mav");
    //this->level2Sound = al_load_sample("../Sounds/l2Sound.mav");
     
}

Suono::~Suono()
{
    al_destroy_sample(click);
    al_destroy_sample(invio);
    al_destroy_sample(exit);
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
bool Suono::playMenu(){}
bool Suono::playLevel1(){}
bool Suono::playLevel2(){}

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
    al_play_sample(time, 1, 0,1,ALLEGRO_PLAYMODE_ONCE,0);
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
}
//void stopGameOver(){}
void Suono::stopWin()
{
    al_rest(5.);
}
//void stopCoin(){}
void Suono::stopTime()
{
    al_rest(10.);
}
