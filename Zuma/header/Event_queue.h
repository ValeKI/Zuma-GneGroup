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
    Event_queue(float fps=60);
    ~Event_queue();
    void start(float fps=60);
    void stop();
    ALLEGRO_EVENT evento();
    bool empty();
    void flusha();
};

#endif