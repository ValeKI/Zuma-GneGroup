#include "../header/Rana.h"
#include <unistd.h>
#include <vector>

//"../image/Rana.png"
extern int wGlobal;
extern int hGlobal;
// costruttori

// si occupa di posizionare la rana al centro e di generare le due palline
Rana::Rana(const int& a,const int& b, const int& n):HitBox("../image/Rana.png", a, b, 1 ), scale(0.6)
{
    srand(time(0));
    cx = a*( (wGlobal*scale2)/1024.); 
    cy = b*( (hGlobal*scale2)/768.);
    palline = new PallinaRana*[2];
    palline[0] = new PallinaRana(COLORE(rand()%n));
    palline[1] = new PallinaRana(COLORE(rand()%n));
}

// distruttore

Rana::~Rana()
{
    for(int i=0; i<2; i++)
        delete palline[i];
    delete[] palline;
}

// funzioni

// stampa la rana, dipende dalle coordinate del mouse l'angolo sul quale e' inclinata
void Rana::stampa(int mx, int my)
{
    // serve per non permettere di sparare continuamente
    if(tempo%10!=0)
        tempo++;

    // dipende da dove è stampata veramente la rana, non dalle sue coordinate 'logiche'
    int stampaX=getStampaX(), stampaY=getStampaY();
    seno = cy - my;
    if ((cx-mx) != 0)
        coseno = cx - mx;

    // quadrante destro    
    double segno = M_PI/2;
    
    // quadrante sinistro
    if(seno <= 0 && coseno < 0 || coseno < 0 && seno >= 0)
        segno = M_PI/2 + M_PI;

    palline[0]->setStampaX(cx);
    palline[0]->setStampaY(cy);

    palline[0]->stampa(1);
    
    al_draw_scaled_rotated_bitmap
    (
        load,
        IMMAGINEX, IMMAGINEY,
        cx, cy,
        ((wGlobal*scale2)/1024.)*scale,
        ((hGlobal*scale2)/768.)*scale,
        (atan(seno/coseno)+segno)    ,
        0
    );
 
    palline[1]->direziona(cx,cy,mx,my);
        
    palline[1]->setPosizione(DISTANZA_PALLINA_CENTRO*((wGlobal*hGlobal)/(1024.*768.))*scale);
    
    palline[1]->movimento();
    palline[1]->stampa(1);
}

// restituisce la pallina della lingua e genera la nuova
PallinaRana* Rana::getPallina(bool coloriDisponibili[],const int& n)
{
    PallinaRana* p = nullptr;
    if(tempo%10==0)
    {
        p = palline[1];
        palline[1] = palline[0];

        if(n>0)
        {
            COLORE c = COLORE(rand()%NUMCOLORI);
            while(!coloriDisponibili[c])
            {    c = COLORE(rand()%NUMCOLORI);}
            palline[0] = new PallinaRana(c);
        }
        else 
            palline[0] = new PallinaRana(GIALLO);
    }
    tempo++;
    return p;
}
