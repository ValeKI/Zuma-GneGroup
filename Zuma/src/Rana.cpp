#include "../header/Rana.h"

//"../image/Rana.png"
extern int wGlobal;
extern int hGlobal;

Rana::Rana(int a,int b):HitBox("../image/Rana.png", a, b, 1 ), scale(0.4)
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
    double stampaX=cx, stampaY=cy;

    stampaX= stampaX+(displayW-(wGlobal * scale2))/2 ;
    stampaY= stampaY+(displayH-(hGlobal * scale2))/2 ;

    seno = stampaY - my;
    if ((stampaX-mx) != 0)
        coseno = stampaX - mx;
        
    double segno = M_PI/2;
    
    if(seno <= 0 && coseno < 0 || coseno < 0 && seno >= 0)
        segno = M_PI/2 + M_PI;

    palline[0]->Pallina::movimento(pair<int, int>(cx,cy) );
    cout << "Pallina " << palline[0]->getStampaX() << " " << palline[0]->getStampaX() << endl;
    cout << "Centro: " << cx << " " << cy << endl << endl;    
    

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
}

Rana::~Rana()
{
    for(int i=0; i<2; i++)
        delete palline[i];
    delete[] palline;
}