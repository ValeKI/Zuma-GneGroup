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

        void caricaCoordinate()
        {
            ifstream in;
            string line;
            in.open("../Percorso/Percorso_0.txt");
            int ml=0;
            int i=0,n1,n2;

            while(getline(in,line))
            {
                if(ml%5==0)
                {
                    string n;
                    i=0;

                    while(line[i]!='-')
                    {
                        n+=line[i++];
                    }
                    n1=atoi(n.c_str());
                    n="";
                    i++;

                    while(line[i]!='\0')
                    {
                        n+=line[i++];
                    }
                    n2=atoi(n.c_str());
                    n="";

                    coordinate.push_back(new pair<int,int>(n1,n2));
                }

                ml++;
            }

            in.close();
        }

        void livello_base()
        {
            
            bool redraw=0;
            BUFFER b("../image/Moon.jpg");
            Mouse m;
            generaPalline(200,6);
            event_queue.start(30);
            int flushh=0, sizeCoord=coordinate.size();
            int p; ALLEGRO_EVENT ev; bool ESCIPLS=0;
            while(888)
            {
                ev = event_queue.evento();

                if(redraw && event_queue.empty())
                {
                    b.stampaSfondo();   
                    redraw=0;
                   // cout << palline.at(0)->getPosizione() << " " << coordinate.size() << endl;
                    ESCIPLS=false;
                    for(auto i:palline)
                    {
                        i->avanza();

                        if ( palline.at(0)->getPosizione()>=sizeCoord )
                        {
                            ESCIPLS=true;
                            break;
                        }    
                        p=i->getPosizione();
                        if(p>=0 && p<sizeCoord)
                        {
                            i->movimento(*coordinate[p]);
                            b.aggiungiImmagine2(i);
                        }
                    }
                    if(ESCIPLS)
                    {
                        event_queue.stop();
                        exit(0);
                    }
                    b.stampa(1);
                    al_flip_display();
                
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
                if(flushh++%300==0)
                    event_queue.flusha();

                if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
                    event_queue.flusha(); 
                 
               
            }

            event_queue.stop();
        }
        
        
};

#endif