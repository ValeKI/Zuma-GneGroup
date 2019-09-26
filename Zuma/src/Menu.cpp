#include "../header/Menu.h"
#include <cmath>

// costruttori

Menu::Menu():Schermata()
{
    caricaFont();
}

// distruttore

Menu::~Menu()
{

}

// funzioni protected

// menu di tipo uno, nel quale e's possibile effettuare una scelta
int Menu::menu1()
{
    bool redraw=0;
    b = new BUFFER("../image/Sfondo.jpg");
   
    scelte.push_back("Esci dal gioco");
    event_queue.stop();
    event_queue.start(10);
    int pos=0;
    // 1 classica    2 tempo    3 mosse

    b->stampaSfondo();

    int scelta=-1;

    
    while(scelta==-1)
    {
       
        ALLEGRO_EVENT ev = event_queue.evento();
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            key[KEY_SPACE]=1;  
        }
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(key[KEY_UP])
            {
                if(pos == 0)
                    pos = 1;
                else
                {
                    pos=(pos-1)%scelte.size();
            
                    if(pos == 0)
                        pos = scelte.size();
                }
               
            }
            else if (key[KEY_DOWN])
            {
               
                pos=(pos+1)%scelte.size();

                if(pos == 0)
                    pos = scelte.size();
                    
            }
            else if(key[KEY_SPACE] && pos>0)
            { 
                
                if(pos == scelte.size())
                    exit(0);
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
                  {  key[KEY_UP]=1;}
                break;

                case ALLEGRO_KEY_DOWN:
                 {   key[KEY_DOWN]=1; }
                break;

                case ALLEGRO_KEY_SPACE:
                 {  key[KEY_SPACE]=1; }
                break;

                case ALLEGRO_KEY_ENTER:
                 {   key[KEY_SPACE]=1; }
                break;
            }
           
        }
        if (ev.type == ALLEGRO_EVENT_KEY_UP)
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
        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
           
            for(int i=0; i<scelte.size(); i++)
            {
                if(collideText(ev.mouse.x, ev.mouse.y, scelte[i], b->getX()+500*wGlobal/1024., b->getY()+(110+100*(i+1))*hGlobal/768.) )
                 {   pos = i+1;}
            }
          
            // collide con mouse
        }
        if(redraw && event_queue.empty())
        {
            redraw = 0;
            b->stampa(1);

            for(int i=0; i<scelte.size(); i++)
            {
                if(pos-1 == i)
                    al_draw_text(font, al_map_rgb(96,63,25), b->getX()+500*wGlobal/1024., b->getY()+(110+100*(i+1))*hGlobal/768., ALLEGRO_ALIGN_CENTER, scelte[i].c_str());
                else
                    al_draw_text(font, al_map_rgb(255,255,255), b->getX()+500*wGlobal/1024., b->getY()+(110+100*(i+1))*hGlobal/768., ALLEGRO_ALIGN_CENTER, scelte[i].c_str());
            }
            //stampa scritte
          
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
       
    }
    scelte.clear();

    for(int i=0; i<numKey; i++)
        key[i]=0;

    event_queue.stop(); // si puo stoppare prima del gioco

    return scelta;

}

// menu tipo due, e' schermata che toccando un tasto scompare
void Menu::menu2(string nomeImm, int tasto)
{
    b = new BUFFER("../image/" + nomeImm);
    event_queue.stop();
    event_queue.start(10);
    ALLEGRO_EVENT ev = event_queue.evento();

    b->stampaSfondo();
    b->stampa(1);
    al_flip_display();

    while(!(ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == tasto))
        ev = event_queue.evento();
}

// funzioni public

void Menu::caricaFont()
{
    font = al_load_font("../ttf/ani.ttf", 100*wGlobal/1024., ALLEGRO_KEEP_BITMAP_FORMAT);
}

// schermata tutorial
void Menu::tutorial()
{
    menu2("guide.png", ALLEGRO_KEY_ESCAPE);
}

// schermata iniziale
void Menu::zuma()
{
    menu2("zuma.png", ALLEGRO_KEY_ENTER);
}

// stampa il menu di pausa
int Menu::menuPausa(Suono* music )
{
    if(!music->getLivello())
    {
        music->stopLevel();
        music->playPause();
        al_rest(0.8);
        music->playMenu();
    }
    
    scelte.push_back("Torna al gioco");
    scelte.push_back("Torna al menu");
    return menu1();
}

// stampa il menu principale
int Menu::menuPricipale( Suono* music)
{
    
    if(!music->getMenu()&& music->getLivello())
    { 
        al_rest(1.0);
        music->playMenu();
    }
    scelte.push_back("Classica");
    scelte.push_back("A Mosse");
    scelte.push_back("A Tempo");
    scelte.push_back("Guida");
    return menu1();
}

// stampa il menu dove puoi scegliere i livelli
int Menu::menuLivelli()
{
    scelte.push_back("Livello 1");
    scelte.push_back("Livello 2");
    scelte.push_back("Torna Indietro");
    return menu1( );
}

// verifica se il mouse tocca un testo
bool Menu::collideText(const int& mx, const int& my, string& s, const int& px, const int& py)
{
    int tx=0, ty=0, th=0, tw=0;
    al_get_text_dimensions(font, s.c_str(), &tx, &ty, &tw, &th);

    tx = tx - tw/2;

    tx+=px;
    ty+=py;
    
    return
    (
        (mx >= tx && mx <= tx + tw)
        &&
        (my >= ty && my <= ty + th)
    );
}
