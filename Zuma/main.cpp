/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma && ./Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "ScrittaMenu.h"
#include <string>
#include <allegro5/allegro5.h>

const float FPS = 60;
enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT,KEY_RIGHT};
int main()
{
    if(!al_init())
    {
        cerr << "Failed to initialite allegro - 1";
        return -1;
    }
    
    
    ALLEGRO_EVENT_QUEUE *events = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool key[4] = { false, false, false, false };
    
    if(!al_install_keyboard()) 
    {
        cerr << "failed to initialize the keyboard!\n";
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) 
    {
        cerr << "failed to create timer!\n";
        return -1;
    }
    
    if(!al_init_image_addon())
    {
        cerr << "Failed to initialite image addon - 2 ";
        return -1;
    }
    SFONDO lol; 
    BUFFER b(IMMAGINE_SFONDO);

    events = al_create_event_queue();
    if(!events) 
    {
        cerr << "Failed to create event queue - 7";
        return -1;
    }

    al_register_event_source(events, al_get_timer_event_source(timer));
    al_register_event_source(events, al_get_keyboard_event_source());

    bool ok=1, disegna=1;
    int x=0;
    al_start_timer(timer);
    while(ok)//&& x<=100)
    {
        //x++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(events, &ev);

        if(ev.type==ALLEGRO_EVENT_TIMER)
        {
            disegna=1;
        }


        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                key[KEY_UP]=1;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                key[KEY_UP]=0;
                break;

                case ALLEGRO_KEY_ESCAPE:
                al_destroy_timer(timer);
                return 0;
                break;
                
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }

        if(ok && disegna && al_is_event_queue_empty(events) )
        {
            disegna=0;
            b.stampaSfondo();
            b.aggiungiImmagine(  (   string("image/Classica_"+to_string(int(key[KEY_UP]))+".jpg")    ).c_str(),340,350,1);
            b.aggiungiImmagine((string("image/Tempo_"+to_string(0%2)+".jpg")).c_str(),340,450,1);
            b.aggiungiImmagine((string("image/Mosse_"+to_string(0%2)+".jpg")).c_str(),340,550,1);
            b.stampaBuffer();
            //al_rest(0.2);
            al_flip_display();
        }


    }


    
    return 0;
}