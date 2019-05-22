#include "../header/PallinaRana.h"

extern int wGlobal;
extern int hGlobal;

PallinaRana::PallinaRana(COLORE c):Pallina(c,0){setVelocita(10);}

void PallinaRana::direziona(int a, int b, int mx, int my)
{
    //mx=my=0;
    posizione=1;
    vx = mx - a;
    vy = my - b;
    float scalare = MODULO/sqrt(pow(vx, 2) + pow(vy, 2));
    vx = float(vx*scalare);
    vy = float(vy*scalare);
    punto.first = a;
    punto.second = b;
}

/*  int PallinaRana::getStampaX() const
{
    return getX();
}

int PallinaRana::getStampaY() const
{
    return getY();
}

int PallinaRana::getStampaL() const
{
    return getLunghezza();
}


int PallinaRana::getStampaA() const
{
    return getAltezza();
} 
 */

void PallinaRana::setStampaX(int a)
{
    HitBox::setStampaX(a-lunghezza/2);
}
        
void PallinaRana::setStampaY(int a)
{
    HitBox::setStampaY(a-altezza/2);
}


void PallinaRana::movimento()
{
    posizione+=velocita;
    setStampaX( (vx * posizione/MODULO) + punto.first);
    setStampaY( (vy * posizione/MODULO) + punto.second);   
}

bool PallinaRana::nonNelloSchermo() const
{
   
     return 
    (
        getStampaX()-getStampaL()/3.< ((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2)
        ||
        getStampaX()+getStampaL()+getStampaL()/3.>=((al_get_display_width(al_get_current_display())-(wGlobal * scale2))/2+wGlobal) 
        
        ||
        
        getStampaY()-getStampaA()/3.< ((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2) 
        ||
        getStampaY()+getAltezza()+getStampaA()/3.>=((al_get_display_height(al_get_current_display())-(hGlobal * scale2))/2 +hGlobal) 
    ); 

}