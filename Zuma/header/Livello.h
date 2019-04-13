#ifndef LIVELLO_H
#define LIVELLO_H
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Pallina.h"
#include "Event_queue.h"
#include "Buffer.h"
#include "Mouse.h"
class Livello 
{
    private:
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;
        Event_queue event_queue;
    public:
        Livello(){}

        ~Livello()
        {
            for(int i=0; i<palline.size(); i++)
                delete palline[i];
            
            for(int i=0; i<coordinate.size(); i++)
                delete coordinate[i];
        }

        void generaPalline(int num, int tipi)
        {
            caricaCoordinate();
            srand(time(0));
            int pos=0;
            
            for(int i=0; i<num; i++)
            {
                int x=rand()%tipi;
                //cout << "il rand " << x << endl;
                switch (x)
                {
                case 0:
                    palline.push_back(new Pallina(ROSSO,pos));
                break;


                case 1:
                    palline.push_back(new Pallina(BLU,pos));
                break;


                case 2:
                    palline.push_back(new Pallina(VERDE,pos));
                break;


                case 3:
                    palline.push_back(new Pallina(ARANCIONE,pos));
                break;

                case 4:
                    palline.push_back(new Pallina(GIALLO,pos));
                break;

                case 5:
                    palline.push_back(new Pallina(VIOLA,pos));
                break;
                
                default:
                    break;
                }

               
                pos-=3;
            } 
            palline.front()->movimento(*coordinate.at(palline.front()->getPosizione()));
        }

        void caricaCoordinate();

        void livello_base()
        {
            
            bool redraw=0;
            BUFFER b("../image/Sfondo.jpg");
            
            Mouse m;
            generaPalline(100,6);
            event_queue.start(200);
            int flushh=0, sizeCoord=coordinate.size();
            int p; ALLEGRO_EVENT ev; bool ESCIPLS=0;
            
            HitBox ciao("../image/0_Classica.jpg",0,0,0.2);

            b.stampaSfondo();
            while(palline[0]->getPosizione()<sizeCoord)
            {
                
                ev = event_queue.evento();

                if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
                {
                    m.setX(ev.mouse.x);
                    m.setY(ev.mouse.y);
                    ciao.setX(m.getX());
                    ciao.setY(m.getY());
                }

                if(redraw && event_queue.empty())
                {  
                    redraw=0;
                    
                    b.stampa(1);    

                    ciao.distruggiLoad();
                    if(m.collisione(palline[0])!=0)
                        ciao.setImmagine("../image/1_Classica.jpg");
                    else
                         ciao.setImmagine("../image/0_Classica.jpg");
                    ciao.ricreaLoad();

                    ciao.stampa(1);
                    
                   // cout << palline.at(0)->getPosizione() << " " << coordinate.size() << endl;
                    
                    for(auto i:palline)
                    {
                        i->avanza();
                        p=i->getPosizione();
                        
                        if(p>=0 && p<sizeCoord)
                        {
                            i->movimento(*coordinate[p]);
                            i->stampa(1);
                        }

                    }       
                    al_flip_display();
                    al_clear_to_color(al_map_rgb(0,0,0));
                } 
                if (ev.type == ALLEGRO_EVENT_KEY_UP)
                {
                    switch(ev.keyboard.keycode)
                    {
                     case ALLEGRO_KEY_ESCAPE:
                     event_queue.stop();
                     exit(0);
                     break;
                    }
                }
                if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                    redraw=1;
                }
                if((flushh++)%400==0)
                    event_queue.flusha();
                
                 
               
            }

            event_queue.stop();
        }
        
        
};

#endif