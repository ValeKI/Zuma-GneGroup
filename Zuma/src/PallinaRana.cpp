#include "../header/PallinaRana.h"

extern int wGlobal;
extern int hGlobal;

PallinaRana::PallinaRana(COLORE c):Pallina(c){setVelocita(10);}

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

bool PallinaRana::nelloSchermo() const
{
    return 
    (
        getX()> ((displayW-(wGlobal * scale2))/2)
        &&
        getY()> ((displayH-(hGlobal * scale2))/2) 
        &&
        getX()+getLunghezza()<((displayW-(wGlobal * scale2))/2+1024) 
        &&
        getY()+getAltezza()<((displayH-(hGlobal * scale2))/2 +768)
    );
}