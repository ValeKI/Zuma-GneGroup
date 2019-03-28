#include "../header/Menu.h"
#include "../header/Mouse.h"

Menu::Menu(){}

Menu::~Menu()
{
    distruggiScritte();
}

void Menu::menu1()
{
    bool redraw=0;
    BUFFER b("../image/Sfondo.jpg");

    scritte.push_back(new ScrittaMenu("../image/0_Classica.jpg",300,300,1));
    scritte.push_back(new ScrittaMenu("../image/0_Tempo.jpg"   ,300,450,1));
    scritte.push_back(new ScrittaMenu("../image/0_Mosse.jpg"   ,300,560,1));
    Mouse m;
    HitBox GNE("../image/0_Classica.jpg",m.getX(),m.getY(),0.3);
    event_queue.start(12);
    int pos=0, scelta=0;
    // 1 classica    2 tempo    3 mosse

    b.stampaSfondo();
    while(888)
    {
        ALLEGRO_EVENT ev = event_queue.evento();
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(key[KEY_UP])
            {
                if(pos == 0)
                    pos = 1;
                    
                pos=(pos+1)%3+1;

                if(pos == 0)
                    pos = 3;
            }
            else if (key[KEY_DOWN])
            {
                pos=(pos+1)%3;

                if(pos == 0)
                    pos = 3;
            }
            else if(key[KEY_SPACE] && pos!=0)
            {
                scelta=pos;
                break;
            }


            redraw=1;
            event_queue.flusha();
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP]=1;
                break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN]=1;
                break;

                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE]=1;
                break;

                case ALLEGRO_KEY_ENTER:
                    key[KEY_SPACE]=1;
                break;
            }

        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    exit(0);
                break;

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                break;

                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE]=false;
                break;

                case ALLEGRO_KEY_START:
                    key[KEY_SPACE]=false;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            m.setX(ev.mouse.x);
            m.setY(ev.mouse.y);
            GNE.setX(m.getX());
            GNE.setY(m.getY());
            if(m.collisione(scritte[0]) == true)
            {
                key[KEY_UP]=true;
                cout << "lol\n";
            }
            else
            {
                key[KEY_UP]=false;
               // cout << "lol2\n";
            }
        }
        if(redraw && event_queue.empty())
        {
            b.stampaSfondo();
            redraw=0;
            for(int i=0; i<3; i++)
                scritte[i]->reazione(0);

            if(pos>0)
                scritte[pos-1]->reazione(1);

            b.aggiungiImmagine(&GNE);

            for(int i=0; i<3; i++)
                b.aggiungiImmagine(scritte[i]);
            
            b.stampa(1);
                al_flip_display();
        }
    }
    event_queue.stop(); // si puo stoppare prima del gioco
    distruggiScritte();

}

void Menu::distruggiScritte()
{
    for (unsigned i = 0; i != scritte.size(); i++)
        delete scritte[i];
    scritte.clear();
}