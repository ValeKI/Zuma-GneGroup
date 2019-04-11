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
            for(auto i:palline)
                delete i;
            
            for(auto i:coordinate)
                delete i;
        }

        void generaPalline(int num, int tipi)
        {
            caricaCoordinate();
            srand(time(0));
            int pos=0;
            
            for(int i=0; i<num; i++)
            {
                int x=rand()%tipi;
                cout << "il rand " << x << endl;
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
                    palline.push_back(new Pallina(VIOLA,pos));
                break;
                
                default:
                    break;
                }

                palline.back()->movimento(*coordinate.at(palline.back()->getPosizione()));
                pos+=4;
            }
        }

        void caricaCoordinate()
        {
            ifstream in;
            string line;
            in.open("../Percorso/Percorso_0.txt");

            while(getline(in,line))
            {
                string n;
                int i=0,n1,n2;

                while(line[i]!='-')
                {
                    n+=line[i++];
                }
                n1=atoi(n.c_str());
                n="";

                 while(line[i]!='\0')
                {
                    n+=line[i++];
                }
                n2=atoi(n.c_str());
                n="";

                coordinate.push_back(new pair<int,int>(n1,n2));
            }

            in.close();
        }

        void livello_base()
        {
            bool redraw=0;
            BUFFER b("../image/Moon.jpg");
            Mouse m;
            generaPalline(20,3);
            event_queue.start(120);



            while(palline.at(0)->getPosizione()!=coordinate.size())
            {
                ALLEGRO_EVENT ev = event_queue.evento();
                if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                    redraw=1;
                }
               
                if(redraw && event_queue.empty())
                {
                    b.stampaSfondo();   
                    redraw=0;
                    
                    for(auto i:palline)
                    {
                        i->avanza();
                        i->movimento(*coordinate.at(palline.back()->getPosizione()));
                        i->stampa(1);
                    }
            
                    b.stampa(1);
                    al_flip_display();
                
                }
            }
        }
        
        
};

#endif