#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;

Livello::Livello(){}

Livello::~Livello()
{
    for(int i=0; i<palline.size(); i++)
        delete palline[i];
            
    for(int i=0; i<coordinate.size(); i++)
        delete coordinate[i];
}

void Livello::generaPalline(int num, int tipi)
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

               
        pos-=palline[0]->getStampaL();
    } 
    
    palline.front()->movimento(*coordinate.at(palline.front()->getPosizione()));
}


void Livello::caricaCoordinate()
{
    ifstream in;
    string line;
    in.open("../Percorso/Percorso_0.txt");
    int i=0,n1,n2;

    ALLEGRO_DISPLAY* display=al_get_current_display();
    int displayW= al_get_display_width(display);
    int displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    int scale = min(sx,sy);


    while(getline(in,line))
    {
        string n;
        i=0;

        while(line[i]!='-')
        {
            n+=line[i++];
        }
        n1=atoi(n.c_str())*( (wGlobal*scale)/1024.);
        n="";
        i++;
        while(line[i]!='\0')
        {
            n+=line[i++];
        }
        n2=atoi(n.c_str())*( (hGlobal*scale)/768.);
        n="";

        coordinate.push_back(new pair<int,int>(n1,n2));
    }

    in.close();
}

void Livello::livello_base()
{
            
    bool redraw=0;
    BUFFER b("../image/Sfondo.jpg");
            
    Mouse m;
    Rana rana(512,384);
    generaPalline(100,6);
    event_queue.start(30);
    int flushh=0, sizeCoord=coordinate.size();
    int p; ALLEGRO_EVENT ev; bool ESCIPLS=0;
            
    b.stampaSfondo();
    while(palline[0]->getPosizione()<sizeCoord)
    {
                
        ev = event_queue.evento();

        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            m.setX(ev.mouse.x);
            m.setY(ev.mouse.y);           
        }

        if(redraw && event_queue.empty())
        {  
            redraw=0;
                    
            b.stampa(1);    

                           
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
            
            rana.stampa(m.getX(), m.getY());       
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