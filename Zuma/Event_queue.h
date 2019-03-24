#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <string>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <iostream>
#include <cstdlib>


class Event_queue
{
    private:
    float FPS; //= 60;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    

    public:
    Event_queue(float fps=60)
    {
        if(!al_install_keyboard()) 
        {
            cerr << "failed to initialize the keyboard!\n";
            exit(-1);
        }

        if(!al_install_mouse()) 
        {
            cerr << "failed to initialize the mouse!\n";
            exit(-1);
        }

        
    }

    void start()
    {
        timer = al_create_timer(1.0 / FPS);
        if(!timer)
        { 
            cerr << "failed to create timer!\n";
            exit(-1);
        }

        event_queue = al_create_event_queue();

        if(!event_queue) 
        {
            cerr << "failed to create event_queue!\n";
            exit(-1);
        }

        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());

        al_start_timer(timer);
    }

    void stop()
    {
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
    }


    ALLEGRO_EVENT evento()
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_flush_event_queue(event_queue);
        return ev;
    }
};

#endif