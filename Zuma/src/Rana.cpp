#include "../header/Rana.h"
#include <unistd.h>

//"../image/Rana.png"
extern int wGlobal;
extern int hGlobal;

Rana::Rana(int a,int b):HitBox("../image/Rana.png", a, b, 1 ), scale(0.6)
{
    srand(time(0));
    cx = a*( (wGlobal*scale2)/1024.); 
    cy = b*( (hGlobal*scale2)/768.);
    palline = new PallinaRana*[2];
    palline[0] = new PallinaRana(COLORE(rand()%6));
    palline[1] = new PallinaRana(COLORE(rand()%6));
}

void Rana::stampa(int mx, int my)
{
    if(tempo%10!=0)
        tempo++;
    double stampaX=cx, stampaY=cy;

    stampaX= stampaX+(displayW-(wGlobal * scale2))/2 ;
    stampaY= stampaY+(displayH-(hGlobal * scale2))/2 ;

    seno = stampaY - my;
    if ((stampaX-mx) != 0)
        coseno = stampaX - mx;
        
    double segno = M_PI/2;
    
    if(seno <= 0 && coseno < 0 || coseno < 0 && seno >= 0)
        segno = M_PI/2 + M_PI;

    palline[0]->setX(cx);
    palline[0]->setY(cy);

    palline[0]->stampa(1);
    
    al_draw_scaled_rotated_bitmap
    (
        load,
        146, 58,
        stampaX, stampaY,
        ( (wGlobal*scale2)/1024.)*scale,
        ( (hGlobal*scale2)/768.)*scale,
        (atan(seno/coseno) + segno)    ,
        0
    );
 
    palline[1]->direziona(stampaX, stampaY,mx,my);
    
    //out << "DisplayW " << displayW << endl;
        
    palline[1]->setPosizione(143 * (            (wGlobal*hGlobal)/(1024.*768.)            ) *scale);
    
   // cout << palline[1]->getPosizione() << endl;
    
    palline[1]->movimento();
    palline[1]->stampa(1);

}

PallinaRana* Rana::getPallina()
{
    PallinaRana* p = nullptr;
    if(tempo%10==0)
    {
        p = palline[1];
    
        palline[1] = palline[0];
        palline[0] = new PallinaRana(COLORE(rand()%6));
    }
    tempo++;
    return p;
}

Rana::~Rana()
{
    for(int i=0; i<2; i++)
        delete palline[i];
    delete[] palline;
}
