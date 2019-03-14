/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma && ./Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "Buffer.h"
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
    bool redraw = true;
    
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
        cerr <<"failed to create event_queue!\n";
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(events, al_get_timer_event_source(timer));
    al_register_event_source(events, al_get_keyboard_event_source());
    al_start_timer(timer);

    for(int x=0;x<10; x++)
    {
        ALLEGRO_EVENT ev;
        
        al_wait_for_event(events, &ev);

        /*if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            key[3]=key[2]=key[1]=key[0]=false;
        }*/
         if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            cout << "lallah";
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                key[KEY_UP]=true;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN]=true;
                break;
                
                case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;
                
                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;
            }
        }
        int gh=0;
        if (key[KEY_UP])
          {  gh=1; }

        b.stampaSfondo();
        b.aggiungiImmagine(  (   string("image/Classica_"+to_string(gh)+".jpg")    ).c_str(),340,350,1);
        b.aggiungiImmagine((string("image/Tempo_"+to_string(0%2)+".jpg")).c_str(),340,450,1);
        b.aggiungiImmagine((string("image/Mosse_"+to_string(0%2)+".jpg")).c_str(),340,550,1);
        b.stampaBuffer();
        al_flip_display();
        al_rest(0.2);
    }




    return 0;
}