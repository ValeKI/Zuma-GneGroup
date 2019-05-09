#include "../header/PallinaRana.h"

extern int wGlobal;
extern int hGlobal;

PallinaRana::PallinaRana(COLORE c):Pallina(c,0){setVelocita(10);}

void PallinaRana::direziona(int a, int b, int mx, int my)
{
    posizione=1;
    vx = mx - a;
    vy = my - b;
    float scalare = MODULO/sqrt(pow(vx, 2) + pow(vy, 2));
    vx = float(vx*scalare);
    vy = float(vy*scalare);
    punto.first = a;
    punto.second = b;
} 



void PallinaRana::movimento()
{
    posizione+=velocita;
    setX( (vx * posizione/MODULO) + punto.first);
    setY( (vy * posizione/MODULO) + punto.second);   
}

bool PallinaRana::nonNelloSchermo() const
{
    cout << "X della pallina " << getX() << endl;
    cout << "X dello schermo" << al_get_display_width(al_get_current_display()) << endl << endl;
    return 
    (
        getX()-9< ((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2)
        ||
        getX()+getStampaL()+9>=((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2+wGlobal) 
        
        ||
        
        getY()-9< ((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2) 
        ||
        getY()+getAltezza()+9>=((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2 +hGlobal) 
    );
}