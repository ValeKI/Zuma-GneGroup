#include "../header/PallinaRana.h"

PallinaRana::PallinaRana(COLORE c):Pallina(c){}

void PallinaRana::spara(int a, int b, int mx, int my)
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
    posizione++;
    cout << x << " " << y << endl;
    setX( (vx * posizione/MODULO) + punto.first);
    setY( (vy * posizione/MODULO) + punto.second);
    
}